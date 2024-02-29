#ifndef __PCV_COMBOBOX_H__
#define __PCV_COMBOBOX_H__

#include <QWidget>

namespace pcv {

class ComboBoxPrivate;
class ComboBox : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ComboBox)

public:
    ComboBox(QWidget *parent = nullptr);
    ~ComboBox();

private:
    ComboBoxPrivate *const d_ptr;
};

}// namespace pcv

#endif//__PCV_COMBOBOX_H__