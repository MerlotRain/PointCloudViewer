#ifndef __PCV_H__
#define __PCV_H__

#include <QObject>
#include <spdlog/spdlog.h>

namespace pcv {

extern std::shared_ptr<spdlog::logger> GLOBAL_LOGGER;

class PCV : public QObject
{
    Q_GADGET
public:
    enum DataSourceType
    {
        Las,
        Bin,
    };
    Q_ENUM(DataSourceType)

    enum DataItemType
    {
        Unknown,
        PointCloud,
        Mesh,
        Label3D,
        Label2D
    };
    Q_ENUM(DataItemType)

    enum DataRole
    {
        HoverRole = Qt::UserRole + 1,
    };
    Q_ENUM(DataRole)
};

}// namespace pcv

#endif//__PCV_H__