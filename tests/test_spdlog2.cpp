#include "test_spdlog2.h"
#include "test_spdlog1.h"

int hello()
{
    g_logger->debug("extern g_logger hello");
    return 0;
}