cmake_minimum_required(VERSION 3.16)

project(Traffic_light VERSION 0.1 LANGUAGES CXX)

set(QT_USE_MAINTENANCE_TOOL OFF CACHE BOOL "" FORCE)
set(QT_NO_PACKAGE_INSTALLER ON)
set(QT_NO_PACKAGE_VERSION_CHECK ON)

find_package(Qt6 REQUIRED COMPONENTS
    Quick
    Core
    Qml
    Network
    Mqtt
)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appsemaphore
    TrafficLightModel.cpp
)

qt_add_qml_module(appsemaphore
    URI semaphore
    VERSION 1.0
    QML_FILES
    TrafficLightView.qml
    SOURCES
        MqttHandler.cpp
        MqttHandler.h
        SOURCES IMessageBus.h
        SOURCES RPMsgHandler.h
        SOURCES RPMsgHandler.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appsemaphore PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appsemaphore
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appsemaphore PRIVATE
    Qt6::Quick
    Qt6::Core
    Qt6::Qml
    Qt6::Network
    Qt6::Mqtt
)

install(TARGETS appsemaphore
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
