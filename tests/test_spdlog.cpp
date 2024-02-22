#include "test_spdlog1.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <string>


#include "test_spdlog2.h"


std::shared_ptr<spdlog::logger> g_logger;


int main()
{
    g_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
    spdlog::set_level(spdlog::level::debug);

    hello();

    g_logger->info("Hello, {}!", "world");
    g_logger->warn("Hello, {}!", "world");
    g_logger->error("Hello, {}!", "world");
    g_logger->critical("Hello, {}!", "world");
}