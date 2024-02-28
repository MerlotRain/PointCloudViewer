#ifndef __PCV_APP_H__
#define __PCV_APP_H__

#include "pcv_mainwindowbase.h"
#include <QObject>
#include <pcv_app_global.h>
namespace pcv {

class AppPrivate;
class APP_EXPORT App : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(App)
public:
    explicit App(MainWindowBase *window = nullptr);
    ~App();
    static App *singleApp();
    static MainWindowBase *baseApp();
    void setMainWindowBase(MainWindowBase *window);

private:
    AppPrivate *const d_ptr;
};

}// namespace pcv

#endif//__PCV_APP_H__