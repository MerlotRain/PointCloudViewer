cmake_minimum_required(VERSION 3.15)
project(PointCloudViewer)

include(GenerateExportHeader)

find_package(Boost REQUIRED COMPONENTS program_options)

add_subdirectory(src)