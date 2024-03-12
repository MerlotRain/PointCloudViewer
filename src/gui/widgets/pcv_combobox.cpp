#include "pcv_combobox.h"
#include "pcv_combobox_p.h"

namespace pcv {

/* ----------------------------- ComboBoxPrivate ---------------------------- */

ComboBoxPrivate::ComboBoxPrivate() {}

void ComboBoxPrivate::addItems(const QStringList &items) {}

/* -------------------------------- ComboBox -------------------------------- */

ComboBox::ComboBox(QWidget *parent) : ComboBox(QStringList(), parent) {}

ComboBox::ComboBox(const QStringList &items, QWidget *parent)
    : QWidget(*new ComboBoxPrivate, parent, Qt::WindowFlags())
{
    Q_D(ComboBox);
    d->addItems(items);
}

ComboBox::~ComboBox() {}

}// namespace pcv