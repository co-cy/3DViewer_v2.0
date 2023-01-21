cmake_minimum_required(VERSION 3.24)
project(3DViewer VERSION 2.0 LANGUAGES CXX)

# Компилятор по умолчанию и флагов
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

# Стандарт c++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Сборка UI файлов
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(src src/Object3D)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(GTest)

set(OBJ3D_SOURCES
    src/Object3D/Object3D.cpp
    src/Object3D/Object3D.h)
set(OBJ3D_TEST
    src/Object3D/tests/FromFile.cpp)

set(PROJECT_SOURCES
    ${OBJ3D_SOURCES})

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(3DViewer
      MANUAL_FINALIZATION
      ${PROJECT_SOURCES}
      )
  # Define target properties for Android with Qt 6 as:
  #    set_property(TARGET 3DViewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
  #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
  # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
  if (ANDROID)
    add_library(3DViewer SHARED
        ${PROJECT_SOURCES}
        )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else ()
    add_executable(3DViewer
        ${PROJECT_SOURCES}
        )
  endif ()
endif ()

target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Core)

set_target_properties(3DViewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    )

if (QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(3DViewer)
endif ()

add_executable(obj3d_test
    ${OBJ3D_SOURCES}
    ${OBJ3D_TEST})
target_link_libraries(obj3d_test Qt${QT_VERSION_MAJOR}::Core GTest::GTest GTest::Main)