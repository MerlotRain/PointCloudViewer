#include "pcv_app.h"
#include "pcv_appprivate.h"

namespace pcv {

Q_GLOBAL_STATIC(App, gApp)
static MainWindowBase *gBaseApp = nullptr;

App::App(MainWindowBase *window) : d_ptr(AppPrivate::init(this)) { gBaseApp = window; }

App::~App()
{
    delete d_ptr;
    delete gBaseApp;
}

App *App::singleApp() { return gApp; }

MainWindowBase *App::baseApp() { return gBaseApp; }

void App::setMainWindowBase(MainWindowBase *window) { gBaseApp = window; }

}// namespace pcv