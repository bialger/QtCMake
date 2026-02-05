include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        ${PROJECT_NAME}_tests
        test_suites/ProjectIntegrationTestSuite.cpp
        main_tests.cpp
)

target_link_libraries(
        ${PROJECT_NAME}_tests
        GTest::gtest_main
)

target_include_directories(${PROJECT_NAME}_tests PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)

gtest_discover_tests(${PROJECT_NAME}_tests)
