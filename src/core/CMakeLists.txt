set(CORE_HEADERS 
    data/pcv_dataitem.h
    data/pcv_pointcloud.h
    pcv_configure.h)

set(CORE_SOURCES 
    data/pcv_dataitem.cpp
    data/pcv_pointcloud.cpp
    pcv_configure.cpp)


add_library(pcv_core SHARED ${CORE_SOURCES} ${CORE_HEADERS})

GENERATE_EXPORT_HEADER(
    pcv_core
    BASE_NAME CORE
    EXPORT_FILE_NAME pcv_core_global.h
)

target_include_directories(pcv_core PUBLIC 
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_link_libraries(pcv_core Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Xml)