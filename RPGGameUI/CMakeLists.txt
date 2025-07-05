cmake_minimum_required(VERSION 3.16)

project(RPGGameUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt bileşenlerini bul
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

# Dil dosyası
set(TS_FILES RPGGameUI_en_US.ts)

# include klasörünü Qt Creator'a tanıt
include_directories(${CMAKE_SOURCE_DIR}/include)

# Proje kaynakları
set(PROJECT_SOURCES
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${CMAKE_SOURCE_DIR}/mainwindow.ui

    src/ConsoleManager.cpp
    src/GameManager.cpp
    src/Entity.cpp
    src/Mob.cpp
    src/Player.cpp
    src/Utility.cpp
    src/mainwindow.cpp

    include/ConsoleManager.h
    include/GameManager.h
    include/Entity.h
    include/Mob.h
    include/Player.h
    include/Utility.h
    include/mainwindow.h

    ${TS_FILES}
)

# Qt build kısmı
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RPGGameUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(RPGGameUI SHARED ${PROJECT_SOURCES})
    else()
        add_executable(RPGGameUI ${PROJECT_SOURCES})
    endif()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(RPGGameUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# macOS ayarları
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.RPGGameUI)
endif()
set_target_properties(RPGGameUI PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Kurulum için
include(GNUInstallDirs)
install(TARGETS RPGGameUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Qt6 için finalize
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RPGGameUI)
endif()
