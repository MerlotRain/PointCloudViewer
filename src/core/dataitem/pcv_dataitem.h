#ifndef __PCV_DATAITEM_H__
#define __PCV_DATAITEM_H__

#include <QObject>
#include <pcv_core_global.h>
#include <pcv_metadata.h>

namespace pcv {

class CORE_EXPORT DataItem : public QObject
{
    Q_OBJECT
public:
    DataItem(DataItem *parent, const QString &name);
    virtual ~DataItem();

    QString name() const;
    QString aliasName() const;
    void setName(const QString &name);
    void setAliasName(const QString &name);

    DataItem *parent() const;
    void addChild(DataItem *child);
    void removeChild(DataItem *child);
    void clear();

    QList<DataItem *> &children();
    QList<DataItem *> &virtualChildren();

    void addVirtualChild(DataItem *child);
    void removeVirtualChild(DataItem *child);
    void clearVirtualChildren();

    MetaData *handle();


protected:
    QList<DataItem *> m_children;
    QList<DataItem *> m_virtualChildren;
    QString m_name;
    QString m_aliasName;
    DataItem *m_parent;
};

}// namespace pcv

#endif//__PCV_DATAITEM_H__