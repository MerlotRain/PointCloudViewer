#ifndef __PCV_LINEEDIT_H__
#define __PCV_LINEEDIT_H__

#include <QLineEdit>

namespace pcv {

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEdit(QWidget *parent = nullptr);
    explicit LineEdit(const QString &, QWidget *parent = nullptr);
    explicit LineEdit(const QString &, const QString &, QWidget *parent = nullptr);
    ~LineEdit();

    using QLineEdit::setText;
    void setText(const QString &);

private:
    Q_DISABLE_COPY(LineEdit)
    QString mHoverText;
};

}// namespace pcv

#endif//__PCV_LINEEDIT_H__