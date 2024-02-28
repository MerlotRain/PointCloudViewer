#ifndef __PCV_POINTCLOUDITEM_H__
#define __PCV_POINTCLOUDITEM_H__

#include "pcv_dataitem.h"
#include <pcv_pointcloud.h>

namespace pcv {

class PointCloudItem : public DataItem
{
    Q_OBJECT
public:
    PointCloudItem(PointCloud *pc, DataItem *parent, const QString &name);
    virtual ~PointCloudItem();
};

}// namespace pcv

#endif//__PCV_POINTCLOUDITEM_H__