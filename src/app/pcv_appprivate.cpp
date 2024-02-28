#include "pcv_appprivate.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

namespace pcv {


std::shared_ptr<spdlog::logger> GLOBAL_LOGGER;
static AppPrivate *g_appPrivate = nullptr;

AppPrivate::AppPrivate(App *p) : q_ptr(p)
{
    GLOBAL_LOGGER = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
}

AppPrivate::~AppPrivate() {}

AppPrivate *AppPrivate::init(App *p)
{
    if (!g_appPrivate) g_appPrivate = new AppPrivate(p);
    return g_appPrivate;
}

}// namespace pcv
