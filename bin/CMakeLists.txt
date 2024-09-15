find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

message(STATUS "Qt6 directory: $ENV{QTDIR}")
set(QT_BIN_DIR "$ENV{QTDIR}/bin")

add_executable(${PROJECT_NAME}
        main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE qt)
