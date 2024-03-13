#ifndef __PCV_TIPLABEL_H__
#define __PCV_TIPLABEL_H__

#include <QWidget>
#include <delegate.h>

#include "pcv_gui_global.h"

namespace pcv {

class GUI_EXPORT TipLabel : public QWidget
{
    Q_OBJECT
public:
    explicit TipLabel(QWidget *parent = nullptr);
    ~TipLabel();

    void setText(const QString &);

    Delegate<void(QString &)> onDataTransform;

protected:
    void enterEvent(QEnterEvent *e) override;
    void leaveEvent(QEvent *e) override;

private:
    Q_DISABLE_COPY(TipLabel)
    QString mDataText;
    QString mText;
};

}// namespace pcv

#endif//__PCV_TIPLABEL_H__