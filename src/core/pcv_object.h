#ifndef __PCV_OBJECT_H__
#define __PCV_OBJECT_H__

#include <QString>
#include <QVariant>

namespace pcv {

class Object
{
public:
    typedef std::shared_ptr<Object> ptr;
    
    Object(Object *parent = nullptr);
    virtual ~Object();
    Object *parent() const;

    void addChild(Object *child);
    void addVirtualChild(Object *child);
    void removeChild(Object *child);
    void removeVirtualChild(Object *child);

    const std::vector<Object *> &children() const;
    const std::vector<Object *> &virtualChildren() const;
    const QString &name() const;
    void setName(const QString &name);

    const QVariantMap &metaData() const;
    void setMetaData(const QVariantMap &metaData);
    void setMetaData(const QString &key, const QVariant &value);
    bool hasMetaData(const QString &key);
    QVariant getMetaData(const QString &key);


private:
    Object *m_parent = nullptr;
    std::vector<Object *> m_realChildren;
    std::vector<Object *> m_virtualChildren;
    QString m_name;
    QVariantMap m_metaData;
};

}// namespace pcv

#endif//__PCV_OBJECT_H__
