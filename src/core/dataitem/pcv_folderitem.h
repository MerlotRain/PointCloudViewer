#ifndef __PCV_FOLDERITEM_H__
#define __PCV_FOLDERITEM_H__

#include "pcv_dataitem.h"

namespace pcv {

class FolderItem : public DataItem
{
    Q_OBJECT
public:
    FolderItem(DataItem *parent, const QString &name);
    ~FolderItem();
};

}// namespace pcv


#endif//__PCV_FOLDERITEM_H__