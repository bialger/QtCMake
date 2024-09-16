find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

message(STATUS "Qt6 directory: $ENV{QTDIR}")
set(QT_BIN_DIR "$ENV{QTDIR}/bin")

if (WIN32)
    add_executable(${PROJECT_NAME} WIN32
            main.cpp
    )
else ()
    add_executable(${PROJECT_NAME}
            main.cpp
    )
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE qt)
