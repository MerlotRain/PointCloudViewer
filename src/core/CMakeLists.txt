set(CORE_HEADERS 
    pcv_object.h)

set(CORE_SOURCES 
    pcv_object.cpp)

find_package(Qt6 COMPONENTS Core Widgets Gui Xml REQUIRED)

add_library(pcv_core SHARED ${CORE_SOURCES} ${CORE_HEADERS})

target_link_libraries(pcv_core Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Xml)