#include "pcv_videodecode.h"
#include <QDateTime>
#include <QDebug>
#include <QEventLoop>
#include <QImage>
#include <QMutex>
#include <QTimer>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

namespace pcv {

#define ERROR_LEN 1024

VideoDecode::VideoDecode() { m_error = new char[ERROR_LEN]; }

VideoDecode::~VideoDecode() { close(); }

void VideoDecode::initFFmpeg()
{
    static bool isFirst = true;
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    if (isFirst)
    {
        avformat_network_init();
        isFirst = false;
    }
}

bool VideoDecode::open(const QString &url)
{
    if (url.isNull()) return false;

    AVDictionary *dict = nullptr;
    av_dict_set(&dict, "rtsp_transport", "tcp", 0);
    av_dict_set(&dict, "max_delay", "3", 0);
    av_dict_set(&dict, "timeout", "1000000", 0);
    int ret = avformat_open_input(&m_formatContext, url.toStdString().data(), nullptr, &dict);
    if (dict) { av_dict_free(&dict); }
    if (ret < 0)
    {
        showError(ret);
        free();
        return false;
    }

    ret = avformat_find_stream_info(m_formatContext, nullptr);
    if (ret < 0)
    {
        showError(ret);
        free();
        return false;
    }
    m_totalTime = m_formatContext->duration / (AV_TIME_BASE / 1000);

    qDebug() << QString("video total time: %1 ms, [%2]")
                        .arg(m_totalTime)
                        .arg(QTime::fromMSecsSinceStartOfDay(int(m_totalTime))
                                     .toString("HH:mm:ss zzz"));

    m_videoIndex = av_find_best_stream(m_formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    if (m_videoIndex < 0)
    {
        showError(m_videoIndex);
        free();
        return false;
    }

    AVStream *videoStream = m_formatContext->streams[m_videoIndex];

    m_size.setWidth(videoStream->codecpar->width);
    m_size.setHeight(videoStream->codecpar->height);
    m_frameRate = rationalToDouble(&videoStream->avg_frame_rate);

    const AVCodec *codec = avcodec_find_decoder(videoStream->codecpar->codec_id);
    m_totalFrames = videoStream->nb_frames;

    qDebug() << QString("分辨率：[w:%1,h:%2] 帧率：%3  总帧数：%4  解码器：%5")
                        .arg(m_size.width())
                        .arg(m_size.height())
                        .arg(m_frameRate)
                        .arg(m_totalFrames)
                        .arg(codec->name);
    m_codecContext = avcodec_alloc_context3(codec);
    if (!m_codecContext)
    {
        qWarning() << "创建视频解码器上下文失败!";
        free();
        return false;
    }

    ret = avcodec_parameters_to_context(m_codecContext, videoStream->codecpar);
    if (ret < 0)
    {
        showError(ret);
        free();
        return false;
    }

    m_codecContext->flags2 |= AV_CODEC_FLAG2_FAST;
    m_codecContext->thread_count = 8;

    ret = avcodec_open2(m_codecContext, nullptr, nullptr);
    if (ret < 0)
    {
        showError(ret);
        free();
        return false;
    }

    m_packet = av_packet_alloc();
    if (!m_packet)
    {
#if PRINT_LOG
        qWarning() << "av_packet_alloc() Error!";
#endif
        free();
        return false;
    }
    m_frame = av_frame_alloc();
    if (!m_frame)
    {
#if PRINT_LOG
        qWarning() << "av_frame_alloc() Error!";
#endif
        free();
        return false;
    }

    int size = av_image_get_buffer_size(AV_PIX_FMT_RGBA, m_size.width(), m_size.height(), 4);
    m_buffer = new uchar[size + 1000];
    m_end = false;
    return true;
}

QImage VideoDecode::read()
{
    if (!m_formatContext) { return QImage(); }
    int readRet = av_read_frame(m_formatContext, m_packet);
    if (readRet < 0) { avcodec_send_packet(m_codecContext, m_packet); }
    else
    {
        if (m_packet->stream_index == m_videoIndex)
        {
            m_packet->pts = qRound64(
                    m_packet->pts *
                    (1000 * rationalToDouble(&m_formatContext->streams[m_videoIndex]->time_base)));
            m_packet->dts = qRound64(
                    m_packet->dts *
                    (1000 * rationalToDouble(&m_formatContext->streams[m_videoIndex]->time_base)));
            int ret = avcodec_send_packet(m_codecContext, m_packet);
            if (ret < 0) { showError(ret); }
        }
    }
    av_packet_unref(m_packet);

    int ret = avcodec_receive_frame(m_codecContext, m_frame);
    if (ret < 0)
    {
        av_frame_unref(m_frame);
        if (readRet < 0) { m_end = true; }
        return QImage();
    }

    m_pts = m_frame->pts;
    if (!m_swsContext)
    {
        m_swsContext = sws_getCachedContext(m_swsContext, m_frame->width, m_frame->height,
                                            (AVPixelFormat) m_frame->format, m_size.width(),
                                            m_size.height(), AV_PIX_FMT_RGBA, SWS_BILINEAR, nullptr,
                                            nullptr, nullptr);
        if (!m_swsContext)
        {
            qWarning() << "sws_getCachedContext() Error!";
            free();
            return QImage();
        }
    }

    uchar *data[] = {m_buffer};
    int lines[4];
    av_image_fill_linesizes(lines, AV_PIX_FMT_RGBA, m_frame->width);
    ret = sws_scale(m_swsContext, m_frame->data, m_frame->linesize, 0, m_frame->height, data,
                    lines);
    QImage image(m_buffer, m_frame->width, m_frame->height, QImage::Format_RGBA8888);
    av_frame_unref(m_frame);

    return image;
}

void VideoDecode::close()
{
    clear();
    free();

    m_totalTime = 0;
    m_videoIndex = 0;
    m_totalFrames = 0;
    m_obtainFrames = 0;
    m_pts = 0;
    m_frameRate = 0;
    m_size = QSize(0, 0);
}

bool VideoDecode::isEnd() { return m_end; }

const qint64 &VideoDecode::pts() { return m_pts; }

void VideoDecode::showError(int err)
{
    memset(m_error, 0, ERROR_LEN);// 将数组置零
    av_strerror(err, m_error, ERROR_LEN);
    qWarning() << "DecodeVideo Error:" << m_error;
}

qreal VideoDecode::rationalToDouble(AVRational *rational)
{
    qreal frameRate = (rational->den == 0) ? 0 : (qreal(rational->num) / rational->den);
    return frameRate;
}

void VideoDecode::clear()
{
    if (m_formatContext && m_formatContext->pb) { avio_flush(m_formatContext->pb); }
    if (m_formatContext) { avformat_flush(m_formatContext); }
}

void VideoDecode::free()
{
    if (m_swsContext)
    {
        sws_freeContext(m_swsContext);
        m_swsContext = nullptr;
    }
    if (m_codecContext) { avcodec_free_context(&m_codecContext); }
    if (m_formatContext) { avformat_close_input(&m_formatContext); }
    if (m_packet) { av_packet_free(&m_packet); }
    if (m_frame) { av_frame_free(&m_frame); }
    if (m_buffer)
    {
        delete[] m_buffer;
        m_buffer = nullptr;
    }
}

VideoThread::VideoThread(QObject *parent) : QThread(parent)
{
    m_videoDecode = new VideoDecode();

    qRegisterMetaType<PlayState>("PlayState");
}

VideoThread::~VideoThread()
{
    if (m_videoDecode) { delete m_videoDecode; }
}

void VideoThread::open(const QString &url)
{
    if (!this->isRunning())
    {
        m_url = url;
        emit this->start();
    }
}

void VideoThread::pause(bool flag) { m_pause = flag; }

void VideoThread::close()
{
    m_play = false;
    m_pause = false;
}

const QString &VideoThread::url() { return m_url; }

void sleepMsec(int msec)
{
    if (msec <= 0) return;
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

void VideoThread::run()
{
    bool ret = m_videoDecode->open(m_url);
    if (ret)
    {
        m_play = true;
        m_etime.start();
        emit playState(Play);
    }
    else { qWarning() << "打开失败!"; }
    while (m_play)
    {
        while (m_pause) { sleepMsec(200); }

        QImage image = m_videoDecode->read();
        if (!image.isNull())
        {
            sleepMsec(int(m_videoDecode->pts() - m_etime.elapsed()));
            emit updateImage(image.copy());
        }
        else
        {
            if (m_videoDecode->isEnd()) { break; }
            sleepMsec(1);
        }
    }

    qDebug() << "播放结束!";
    m_videoDecode->close();
    emit playState(End);
}

}// namespace pcv
