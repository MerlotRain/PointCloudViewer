#ifndef __PCV_APP_H__
#define __PCV_APP_H__

#include <QObject>
#include <pcv_app_global.h>

namespace pcv {

class AppPrivate;
class APP_EXPORT App : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(App)
public:
    explicit App(QObject *parent = nullptr);
    ~App();
    static App *singleton();

private:
    AppPrivate *const d_ptr;
};

}// namespace pcv

#endif//__PCV_APP_H__