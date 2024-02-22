#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include <QGlobalStatic>

#include "pcv_app.h"

namespace pcv {
std::shared_ptr<spdlog::logger> GLOBAL_LOGGER;
}// namespace pcv


using namespace pcv;

int main()
{
    GLOBAL_LOGGER = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
    GLOBAL_LOGGER->info("Hello, {}!", "world");
    return 0;
}