cmake_minimum_required(VERSION 3.16)

project(EasyGCS VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Quick SerialPort)

qt_standard_project_setup(REQUIRES 6.5)

set(CMAKE_AUTORCC ON)
qt_add_executable(appEasyGCS
    main.cpp
)

qt_add_qml_module(appEasyGCS
    URI EasyGCS
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES serialhandler.h serialhandler.cpp
        RESOURCES resource.qrc
        SOURCES
        SOURCES serialhandleradaptor.h serialhandleradaptor.cpp
        SOURCES mavlinkparser.h mavlinkparser.cpp
        SOURCES mavlinkcontroller.h mavlinkcontroller.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appEasyGCS PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appEasyGCS
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appEasyGCS
    PRIVATE Qt6::Quick
    Qt6::Core
    Qt6::SerialPort

)

include(GNUInstallDirs)
install(TARGETS appEasyGCS
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include_directories(${CMAKE_SOURCE_DIR}/c_library_v2)

