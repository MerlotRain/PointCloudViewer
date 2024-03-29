#include "pcv_animatedicon.h"

namespace pcv {

QgsAnimatedIcon::QgsAnimatedIcon(const QString &iconPath, QObject *parent)
    : QObject(parent), mMovie(new QMovie(this))
{
    if (!iconPath.isEmpty()) { mMovie->setFileName(iconPath); }
    mMovie->setCacheMode(QMovie::CacheAll);
    connect(mMovie, &QMovie::frameChanged, this, &QgsAnimatedIcon::onFrameChanged);
}

QString QgsAnimatedIcon::iconPath() const { return mMovie->fileName(); }

void QgsAnimatedIcon::setIconPath(const QString &iconPath) { mMovie->setFileName(iconPath); }

QIcon QgsAnimatedIcon::icon() const { return mIcon; }

bool QgsAnimatedIcon::connectFrameChanged(const QObject *receiver, const char *method)
{
    if (connect(this, SIGNAL(frameChanged()), receiver, method))
    {
        mMovie->setPaused(false);
        return true;
    }
    else
        return false;
}

bool QgsAnimatedIcon::disconnectFrameChanged(const QObject *receiver, const char *method)
{
    return disconnect(this, SIGNAL(frameChanged()), receiver, method);
}

int QgsAnimatedIcon::width() const { return mMovie->currentPixmap().width(); }

int QgsAnimatedIcon::height() const { return mMovie->currentPixmap().height(); }
void QgsAnimatedIcon::onFrameChanged()
{
    if (!isSignalConnected(QMetaMethod::fromSignal(&QgsAnimatedIcon::frameChanged)))
        mMovie->setPaused(true);

    mIcon = QIcon(mMovie->currentPixmap());
    emit frameChanged();
}

}// namespace pcv