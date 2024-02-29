cmake_minimum_required(VERSION 3.15)
project(PointCloudViewer)

include(GenerateExportHeader)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(VTK REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(PCL REQUIRED)
find_package(spdlog REQUIRED)

######################################################################
# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS 
    Core 
    Gui 
    Widgets 
    Xml 
    OpenGL 
    REQUIRED
)

message("QT_VERSION_MAJOR=${QT_VERSION_MAJOR}")


include_directories(${EIGEN3_INCLUDE_DIRS})
include_directories(${PCL_INCLUDE_DIRS})
include_directories(${PCL_BINARY_DIRS})
include_directories(${VTK_INCLUDE_DIRS})

add_subdirectory(src)
# add_subdirectory(tests)
