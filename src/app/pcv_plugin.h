#ifndef __PCV_PLUGIN_H__
#define __PCV_PLUGIN_H__

#include <QObject>

namespace pcv {

class Plugin : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString name READ name)
    //Q_PROPERTY(QString aliasName READ aliasName)
    //Q_PROPERTY(QString version READ version)
    //Q_PROPERTY(QString description READ description)
    //Q_PROPERTY(QString author READ author)
    //Q_PROPERTY(QString authorEmail READ authorEmail)
    //Q_PROPERTY(QString authorUrl READ authorUrl)
public:

    Plugin();
    virtual ~Plugin();
};

}// namespace pcv

#endif//__PCV_PLUGIN_H__