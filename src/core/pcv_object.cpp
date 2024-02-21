#include "pcv_object.h"

namespace pcv {
Object::Object(Object *parent) : m_parent(parent) {}

Object::~Object() {}

Object *Object::parent() const { return m_parent; }

void Object::addChild(Object *child) { m_realChildren.push_back(child); }

void Object::addVirtualChild(Object *child) { m_virtualChildren.push_back(child); }

void Object::removeChild(Object *child) {}

void Object::removeVirtualChild(Object *child) {}

const std::vector<Object *> &Object::children() const { return m_realChildren; }

const std::vector<Object *> &Object::virtualChildren() const { return m_virtualChildren; }

const QString &Object::name() const { return m_name; }

void Object::setName(const QString &name) { m_name = name; }

const QVariantMap &Object::metaData() const { return m_metaData; }

void Object::setMetaData(const QVariantMap &metaData) { m_metaData = metaData; }

void Object::setMetaData(const QString &key, const QVariant &value) { m_metaData[key] = value; }

bool Object::hasMetaData(const QString &key) { return m_metaData.contains(key); }

QVariant Object::getMetaData(const QString &key) { return m_metaData[key]; }

}// namespace pcv
