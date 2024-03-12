#ifndef __PCV_COMBOBOX_H__
#define __PCV_COMBOBOX_H__

#include <QWidget>

namespace pcv {

class ComboBoxPrivate;
class ComboBox : public QWidget
{
    Q_OBJECT
public:
    explicit ComboBox(QWidget *parent = nullptr);
    explicit ComboBox(const QStringList &items, QWidget *parent = nullptr);
    ~ComboBox();

private:
    Q_DISABLE_COPY(ComboBox)
    Q_DECLARE_PRIVATE(ComboBox)
};

}// namespace pcv

#endif//__PCV_COMBOBOX_H__