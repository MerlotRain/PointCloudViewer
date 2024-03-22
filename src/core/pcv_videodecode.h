#ifndef __PCV_VIDEODECODE_H__
#define __PCV_VIDEODECODE_H__

#include <QElapsedTimer>
#include <QSize>
#include <QString>
#include <QThread>

#include "pcv_core_global.h"


struct AVFormatContext;
struct AVCodecContext;
struct AVRational;
struct AVPacket;
struct AVFrame;
struct SwsContext;
struct AVBufferRef;
class QImage;

namespace pcv {

class CORE_EXPORT VideoDecode
{
public:
    VideoDecode();
    ~VideoDecode();

    bool open(const QString &url = QString());
    QImage read();
    void close();
    bool isEnd();
    const qint64 &pts();

private:
    void initFFmpeg();
    void showError(int err);
    qreal rationalToDouble(AVRational *rational);
    void clear();
    void free();

private:
    AVFormatContext *m_formatContext = nullptr;
    AVCodecContext *m_codecContext = nullptr;
    SwsContext *m_swsContext = nullptr;
    AVPacket *m_packet = nullptr;
    AVFrame *m_frame = nullptr;
    int m_videoIndex = 0;
    qint64 m_totalTime = 0;
    qint64 m_totalFrames = 0;
    qint64 m_obtainFrames = 0;
    qint64 m_pts = 0;
    qreal m_frameRate = 0;
    QSize m_size;
    char *m_error = nullptr;
    bool m_end = false;
    uchar *m_buffer = nullptr;
};

class CORE_EXPORT VideoThread : public QThread
{
    Q_OBJECT
public:
    enum PlayState
    {
        Play,
        End
    };

public:
    explicit VideoThread(QObject *parent = nullptr);
    ~VideoThread() override;

    void open(const QString &url = QString());
    void pause(bool flag);
    void close();
    const QString &url();

protected:
    void run() override;

signals:
    void updateImage(const QImage &image);
    void playState(PlayState state);

private:
    VideoDecode *m_videoDecode = nullptr;
    QString m_url;
    bool m_play = false;
    bool m_pause = false;
    QElapsedTimer m_etime;
};


}// namespace pcv

#endif//__PCV_VIDEODECODE_H__