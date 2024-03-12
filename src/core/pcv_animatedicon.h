#ifndef __PCV_ANIMATEDICON_H__
#define __PCV_ANIMATEDICON_H__

#include <QIcon>
#include <QMetaMethod>
#include <QMovie>
#include <QObject>

#include "pcv_core_global.h"

namespace pcv {

class CORE_EXPORT QgsAnimatedIcon : public QObject
{
    Q_OBJECT
public:
    QgsAnimatedIcon(const QString &iconPath = QString(), QObject *parent = nullptr);
    QString iconPath() const;
    void setIconPath(const QString &iconPath);
    QIcon icon() const;

    template<typename Func1>
    bool connectFrameChanged(const typename QtPrivate::FunctionPointer<Func1>::Object *receiver,
                             Func1 slot)
    {
        if (connect(this, &QgsAnimatedIcon::frameChanged, receiver, slot))
        {
            mMovie->setPaused(false);
            return true;
        }
        else
            return false;
    }
    template<typename Func1>
    bool disconnectFrameChanged(const typename QtPrivate::FunctionPointer<Func1>::Object *receiver,
                                Func1 slot)
    {
        return disconnect(this, &QgsAnimatedIcon::frameChanged, receiver, slot);
    }

    bool connectFrameChanged(const QObject *receiver, const char *method);
    bool disconnectFrameChanged(const QObject *receiver, const char *method);
    int width() const;
    int height() const;

signals:
    void frameChanged();

private slots:
    void onFrameChanged();

private:
    QMovie *mMovie = nullptr;
    QIcon mIcon;
};

}// namespace pcv

#endif// __PCV_ANIMATEDICON_H__
