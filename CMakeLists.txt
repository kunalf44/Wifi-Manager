cmake_minimum_required(VERSION 3.16)

project(delete_networksettings VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick NetworkSettings Qml Core)
find_package(Qt6 COMPONENTS WebEngineQuick REQUIRED)
qt_standard_project_setup()

qt_add_executable(appdelete_networksettings
    main.cpp
)

qt_add_qml_module(appdelete_networksettings
    URI delete_networksettings
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES connection.h connection.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appdelete_networksettings PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appdelete_networksettings
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appdelete_networksettings
    PRIVATE Qt6::Quick
    Qt6::NetworkSettings
    Qt6::Qml
    Qt6::Core
    Qt6::WebEngineQuick
)

include(GNUInstallDirs)
install(TARGETS appdelete_networksettings
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# set(INSTALL_DESTDIR "/opt")
# install(TARGETS appdelete_networksettings
# RUNTIME DESTINATION "${INSTALL_DESTDIR}"
# BUNDLE DESTINATION "${INSTALL_DESTDIR}"
# LIBRARY DESTINATION "${INSTALL_DESTDIR}"
# )
