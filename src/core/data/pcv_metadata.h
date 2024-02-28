#ifndef __PCV_METADATA_H__
#define __PCV_METADATA_H__

#include <QVariant>

namespace pcv {

class MetaData
{
public:
    MetaData() = default;
    virtual ~MetaData() = default;

    QVariantMap metadata() const;
    void setMetadata(const QVariantMap &map);
    QVariant metadata(const QString &key) const;
    void setMetadata(const QString &key, const QVariant &value);

protected:
    QVariantMap mMetadata;
};

}// namespace pcv

#endif//__PCV_METADATA_H__