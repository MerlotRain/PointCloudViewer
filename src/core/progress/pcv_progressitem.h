#ifndef __PCV_PROGRESSITEM_H__
#define __PCV_PROGRESSITEM_H__

#include <QSharedPointer>
#include <QWidget>

namespace pcv {

class ProgressTask;
class ProgressItem
{
public:
    virtual QWidget *configure(QWidget *parent = nullptr) = 0;

    virtual QWidget *paremeter(QWidget *parent = nullptr) = 0;

    virtual const QString &name() const = 0;

    virtual void configureFinish() = 0;

    virtual QList<ProgressTask *> tasks(const QList<QWidget *> &) const = 0;
};

}// namespace pcv

#endif// __PCV_PROGRESSITEM_H__