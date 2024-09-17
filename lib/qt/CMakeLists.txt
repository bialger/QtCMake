# Error if building out of a build directory
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if (EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with "
            "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
            "remove CMakeCache.txt and CMakeFiles.")
endif ()

if (WIN32)
    set(PATH_DELIMITER ";")
else ()
    set(PATH_DELIMITER ":")
endif ()

# Set necessary environment variables to use Qt
set(QT_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/qt-build")
set(QT_INCLUDE_DIR "${QT_BUILD_DIR}/include")
set(QT_BIN_DIR "${QT_BUILD_DIR}/bin")
set(Qt6_DIR "${QT_BUILD_DIR}/lib/cmake/Qt6")
set(ENV{QTDIR} ${QT_BUILD_DIR})
set(ENV{PATH} "${QT_BIN_DIR}${PATH_DELIMITER}$ENV{PATH}")

# Fetch the package
find_package(Qt6 COMPONENTS Core Gui Widgets QUIET)

if (NOT Qt6_FOUND)
    # Set Ninja for compilation
    set(CMAKE_GENERATOR "Ninja" CACHE STRING "CMake generator" FORCE)
    # Initial message
    message(STATUS "Qt 6 not found. Downloading and configuring Qt...")

    # Download and extract archive of Qt 6.7.2
    set(QT_VERSION "6.7.2")
    set(QT_ARCHIVE_URL "https://github.com/qt/qtbase/archive/refs/tags/v${QT_VERSION}.tar.gz")
    set(QT_ARCHIVE_FILE "${CMAKE_CURRENT_BINARY_DIR}/qtbase-${QT_VERSION}.tar.gz")
    set(QT_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/qtbase-${QT_VERSION}")
    message(STATUS "Downloading the package from the github mirror...")
    file(DOWNLOAD ${QT_ARCHIVE_URL} ${QT_ARCHIVE_FILE}
            SHOW_PROGRESS)
    message(STATUS "Unpacking the release...")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvf ${QT_ARCHIVE_FILE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            OUTPUT_QUIET
    )

    # Configure Qt (skip building of useless modules)
    set(QT_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/qt-build")
    file(MAKE_DIRECTORY ${QT_BUILD_DIR})
    message(STATUS "Configuring...")

    if (WIN32)
        execute_process(COMMAND "${QT_SOURCE_DIR}/configure.bat" -static -c++std c++20 -skip qtzlib -prefix ${QT_BUILD_DIR}
                WORKING_DIRECTORY ${QT_BUILD_DIR})
    else ()
        execute_process(COMMAND "${QT_SOURCE_DIR}/configure" -static -c++std c++20 -prefix ${QT_BUILD_DIR}
                WORKING_DIRECTORY ${QT_BUILD_DIR})
    endif ()

    # Build Qt
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            WORKING_DIRECTORY ${QT_BUILD_DIR})

    find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
else ()
    message(STATUS "Qt 6 found in the system.")
endif ()

qt_standard_project_setup()

add_library(qt INTERFACE QtCMake.hpp)

target_include_directories(qt INTERFACE "${QtCMake_SOURCE_DIR}/lib/qt")
target_include_directories(qt INTERFACE "${qt_cmake_SOURCE_DIR}/lib/qt")
target_include_directories(qt INTERFACE "${qtcmake_SOURCE_DIR}/lib/qt")
target_include_directories(qt INTERFACE "${QT_INCLUDE_DIR}")

target_link_libraries(qt INTERFACE Qt6::Core Qt6::Gui Qt6::Widgets)
