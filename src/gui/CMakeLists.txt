set(gui_sources 
    widgets/pcv_combobox.cpp
    widgets/pcv_lineedit.cpp
)

set(gui_headers
    widgets/pcv_combobox.h
    widgets/pcv_lineedit.h
)

set(gui_private
    widgets/pcv_combobox_p.h
)

add_library(pcv_gui SHARED ${gui_sources} ${gui_headers} ${gui_private})

GENERATE_EXPORT_HEADER(
    pcv_gui
    BASE_NAME GUI
    EXPORT_FILE_NAME pcv_gui_global.h
)

target_include_directories(pcv_gui PUBLIC 
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(pcv_gui 
    pcv_core)

target_link_libraries(pcv_gui 
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(pcv_gui PRIVATE 
    ${Qt6Widgets_PRIVATE_INCLUDE_DIRS}
)