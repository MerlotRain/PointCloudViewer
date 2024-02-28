
add_executable(application 
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(application 
    pcv_core
    pcv_app)