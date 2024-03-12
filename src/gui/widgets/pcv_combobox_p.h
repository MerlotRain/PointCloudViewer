#ifndef __PCV_COMBOBOX_P_H__
#define __PCV_COMBOBOX_P_H__

#include "pcv_combobox.h"
#include <private/qwidget_p.h>

namespace pcv {

class ComboBoxPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(ComboBox)

public:
    ComboBoxPrivate();
    void addItems(const QStringList &items);

    
};

}// namespace pcv

#endif//__PCV_COMBOBOX_P_H__