#ifndef __PCV_LINEEDIT_H__
#define __PCV_LINEEDIT_H__

#include <QLineEdit>
#include <delegate.h>

#include "pcv_gui_global.h"

namespace pcv {

class GUI_EXPORT LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEdit(QWidget *parent = nullptr);
    ~LineEdit();

    using QLineEdit::setText;
    void setText(const QString &);
    QString dataText() const;

    Delegate<void(QString &)> onDataTransform;

protected:
    void enterEvent(QEnterEvent *e) override;
    void leaveEvent(QEvent *e) override;

private:
    Q_DISABLE_COPY(LineEdit)
    QString mDataText;
    QString mText;
};

}// namespace pcv

#endif//__PCV_LINEEDIT_H__