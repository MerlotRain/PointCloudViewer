#include "pcv_lineedit.h"

namespace pcv {
LineEdit::LineEdit(QWidget *parent) {}

LineEdit::~LineEdit() {}

void LineEdit::setText(const QString &text)
{
    mDataText = text;
    onDataTransform(const_cast<QString &>(text));
    mText = text;
    QLineEdit::setText(text);
}

QString LineEdit::dataText() const { return mDataText; }

void LineEdit::enterEvent(QEnterEvent *e) { QLineEdit::setText(mDataText); }

void LineEdit::leaveEvent(QEvent *e) { QLineEdit::setText(mText); }

}// namespace pcv