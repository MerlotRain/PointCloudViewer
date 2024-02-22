add_executable(PCV main.cpp)
target_link_libraries(PCV 
    pcv_core
    spdlog::spdlog
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::Xml
    ${PCL_LIBRARIES})
    