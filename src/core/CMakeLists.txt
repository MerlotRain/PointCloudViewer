set(CORE_HEADERS 
    data/pcv_dataitem.h
    data/pcv_pointcloud.h
    pcv_object.h
    pcv_configure.h)

set(CORE_SOURCES 
    data/pcv_dataitem.cpp
    data/pcv_pointcloud.cpp
    pcv_object.cpp
    pcv_configure.cpp)


add_library(pcv_core SHARED ${CORE_SOURCES} ${CORE_HEADERS})

target_link_libraries(pcv_core Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Xml)