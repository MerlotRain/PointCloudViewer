set(app_sources 
    pcv_app.cpp 
    pcv_appprivate.cpp
    pcv_mainwindow.cpp)

set(app_headers 
    pcv_app.h
    pcv_appprivate.h
    pcv_mainwindow.h)
    
add_library(pcv_app SHARED ${app_sources} ${app_headers})

GENERATE_EXPORT_HEADER(
    pcv_app
    BASE_NAME APP
    EXPORT_FILE_NAME pcv_app_global.h
)

target_include_directories(pcv_app PUBLIC 
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_link_libraries(pcv_app 
    pcv_core
    spdlog::spdlog
    ${PCL_LIBRARIES})

add_executable(PCV main.cpp)

target_link_libraries(PCV 
    pcv_app)
    