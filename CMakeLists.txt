cmake_minimum_required(VERSION 3.16)

project(CanvasExperiment VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt's automoc, autorcc, and autouic
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core Gui Widgets Multimedia)

qt_standard_project_setup()

# Set Qt policies for QML
qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

# Define source files
set(PROJECT_SOURCES
    src/main.cpp
    src/videoplayer.cpp
    src/videoplayer.h
    src/backgroundmanager.cpp
    src/backgroundmanager.h
    resources.qrc
)

qt_add_executable(CanvasExperiment
    ${PROJECT_SOURCES}
)

qt_add_qml_module(CanvasExperiment
    URI CanvasExperiment
    VERSION 1.0
    QML_FILES
        qml/main.qml
)

target_link_libraries(CanvasExperiment
    PRIVATE
    Qt6::Quick
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
)

set_target_properties(CanvasExperiment PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS CanvasExperiment
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
