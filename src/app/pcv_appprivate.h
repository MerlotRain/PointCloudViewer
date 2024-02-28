#ifndef __PCV_APPPRIVATE_H__
#define __PCV_APPPRIVATE_H__

#include <QMainWindow>
#include <QObject>
#include <pcv_app_global.h>

namespace pcv {

class App;
class APP_EXPORT AppPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(App)
public:
    AppPrivate(App *p);
    ~AppPrivate();

private:
    static AppPrivate *init(App *p);

private:
    App *const q_ptr;
};

}// namespace pcv


#endif//__PCV_APPPRIVATE_H__