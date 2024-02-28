#include "pcv_appprivate.h"

namespace pcv {

static AppPrivate *g_appPrivate = nullptr;

AppPrivate::AppPrivate(App *p) : q_ptr(p) {}

AppPrivate::~AppPrivate() {}

AppPrivate *AppPrivate::init(App *p)
{
    if (!g_appPrivate) g_appPrivate = new AppPrivate(p);
    return g_appPrivate;
}

}// namespace pcv
