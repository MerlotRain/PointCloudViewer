#include "pcv_dataitem.h"

namespace pcv {


DataItem::DataItem(DataItem *parent, const QString &name) {}

DataItem::~DataItem() {}

QString DataItem::name() const { return QString(); }

QString DataItem::aliasName() const { return QString(); }

void DataItem::setName(const QString &name) {}

void DataItem::setAliasName(const QString &name) {}

DataItem *DataItem::parent() const { return nullptr; }

void DataItem::addChild(DataItem *child) {}

void DataItem::removeChild(DataItem *child) {}

void DataItem::clear() {}

QList<DataItem *> &DataItem::children() { return m_children; }

QList<DataItem *> &DataItem::virtualChildren() { return m_virtualChildren; }

void DataItem::addVirtualChild(DataItem *child) {}

void DataItem::removeVirtualChild(DataItem *child) {}

void DataItem::clearVirtualChildren() {}

MetaData *DataItem::handle() { return nullptr; }

}// namespace pcv