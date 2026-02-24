cmake_minimum_required(VERSION 3.14)
project(ArrayStatsTDD)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Enable testing
enable_testing()

#Find paths
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Create library from source files
add_library(array_stats ${SRC_DIR}/array_stats.cpp)
target_include_directories(array_stats PUBLIC ${SRC_DIR})

# Create test executable
add_executable(array_stats_tests ${TEST_DIR}/array_stats_test.cpp)
target_link_libraries(array_stats_tests array_stats GTest::GTest GTest::Main)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(array_stats_tests)
