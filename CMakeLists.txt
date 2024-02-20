cmake_minimum_required(VERSION 3.15)
project(PointCloudViewer)

include(GenerateExportHeader)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(Boost REQUIRED COMPONENTS program_options)


add_subdirectory(3dparty/CCCoreLib)
add_subdirectory(src)