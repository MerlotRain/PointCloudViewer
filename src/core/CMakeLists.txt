set(CORE_HEADERS 
    data/pcv_metadata.h
    data/pcv_pointcloud.h

    dataitem/pcv_dataitem.h
    dataitem/pcv_folderitem.h
    dataitem/pcv_pointclouditem.h

    pcv.h
    pcv_matrix.h
    pcv_configure.h
    pcv_animatedicon.h
    pcv_videodecode.h

    progress/pcv_progresstaskmanager.h
    progress/pcv_progressitem.h
    progress/pcv_progresstask.h)

set(CORE_SOURCES 
    data/pcv_pointcloud.cpp

    dataitem/pcv_dataitem.cpp
    dataitem/pcv_folderitem.cpp
    dataitem/pcv_pointclouditem.cpp

    pcv_matrix.cpp
    pcv_configure.cpp
    pcv_animatedicon.cpp
    pcv_videodecode.cpp
    
    progress/pcv_progresstaskmanager.cpp)


add_library(pcv_core SHARED ${CORE_SOURCES} ${CORE_HEADERS})

GENERATE_EXPORT_HEADER(
    pcv_core
    BASE_NAME CORE
    EXPORT_FILE_NAME pcv_core_global.h
)

target_include_directories(pcv_core PUBLIC 
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    data
    dataitem
    )

target_link_libraries(pcv_core 
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Widgets
    spdlog::spdlog
    avcodec
    avfilter
    avformat
    swscale
    avutil
    swresample
    avdevice
    )