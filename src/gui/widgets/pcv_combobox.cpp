#include "pcv_combobox.h"

namespace pcv {

class ComboBoxPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(ComboBox)

public:
    ComboBoxPrivate(ComboBox *q) : q_ptr(q) {}

private:
    ComboBox *const q_ptr;
};


ComboBox::ComboBox(QWidget *parent) : QWidget(parent), d_ptr(new ComboBoxPrivate(this)) {}

ComboBox::~ComboBox() {}

}// namespace pcv