cmake_minimum_required(VERSION 3.21)
project(HW3_1)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.0
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 20)
set(TEST_NAME ${PROJECT_NAME}_tests)
add_executable(HW3_1 main.cpp Functional/FolderTerrorist.cpp Functional/FolderTerrorist.h Helper.cpp)
add_executable(${TEST_NAME} Tests.cpp Functional/FolderTerrorist.cpp Functional/FolderTerrorist.h Helper.cpp)
target_link_libraries(${TEST_NAME} gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
