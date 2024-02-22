add_executable(test_spdlog test_spdlog.cpp test_spdlog2.cpp)

target_link_libraries(test_spdlog spdlog::spdlog)