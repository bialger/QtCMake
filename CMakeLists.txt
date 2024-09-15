cmake_minimum_required(VERSION 3.16)

project(
        QtCMake
        VERSION 0.1.0
        DESCRIPTION "CMake project for easy Qt connection to other CMake projects"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

message(STATUS "Building ${PROJECT_DESCRIPTION} ${PROJECT_NAME}, version ${PROJECT_VERSION}")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

if (WIN32)
    set(USER_HOME_DIRECTORY $ENV{USERPROFILE})
else ()
    set(USER_HOME_DIRECTORY $ENV{HOME})
endif ()

message(STATUS "User home directory: ${USER_HOME_DIRECTORY}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_DEBUG "/MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
else ()
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif ()

add_subdirectory(lib)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    add_subdirectory(bin)
endif ()
