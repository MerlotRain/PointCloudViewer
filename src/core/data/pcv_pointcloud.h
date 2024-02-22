#ifndef __PCV_POINTCLOUD_H__
#define __PCV_POINTCLOUD_H__

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

namespace pcv {

class PointCloud
{
public:
    typedef std::shared_ptr<PointCloud> ptr;

    PointCloud() = default;
    virtual ~PointCloud() = default;

protected:
    pcl::PointCloud<pcl::PointXYZI>::Ptr m_pointCloud;
};

}// namespace pcv

#endif//__PCV_POINTCLOUD_H__