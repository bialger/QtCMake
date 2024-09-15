find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

message(STATUS "Qt6 directory: $ENV{QTDIR}")
set(QT_BIN_DIR "$ENV{QTDIR}/bin")

add_executable(${PROJECT_NAME}
        main.cpp
)

if (WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND "${QT_BIN_DIR}/windeployqt.exe"
            ARGS "${CMAKE_BINARY_DIR}/bin"
    )
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE qt)