#include "pcv_pointclouditem.h"

namespace pcv {
PointCloudItem::PointCloudItem(PointCloud *pc, DataItem *parent, const QString &name)
    : DataItem(parent, name)
{
}


PointCloudItem::~PointCloudItem() {}

}// namespace pcv