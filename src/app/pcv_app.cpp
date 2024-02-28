#include "pcv_app.h"
#include "pcv_appprivate.h"

namespace pcv {

Q_GLOBAL_STATIC(App, gApp)

App::App(QObject *parent) : QObject(parent), d_ptr(AppPrivate::init(this)) {}

App::~App() { delete d_ptr; }

App *App::singleton() { return gApp; }

}// namespace pcv