#ifndef __PCV_H__
#define __PCV_H__

#include <spdlog/spdlog.h>

namespace pcv {

extern std::shared_ptr<spdlog::logger> GLOBAL_LOGGER;

class PCV
{
public:
    enum DataSourceType
    {
        Las,
        Bin,
    };

    enum DataItemType
    {
        Unknown,
        PointCloud,
        Mesh,
        Label3D,
        Label2D
    };
};

}// namespace pcv

#endif//__PCV_H__