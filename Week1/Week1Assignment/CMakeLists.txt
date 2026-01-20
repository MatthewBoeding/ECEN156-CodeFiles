cmake_minimum_required(VERSION 3.14)
project(ArrayFunctionsAssignment)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add debug symbols for debugging
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_BUILD_TYPE Debug)

# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Enable testing
enable_testing()

#Find paths
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Create library from your implementation
add_library(array_functions ${SRC_DIR}/array_functions.cpp)
target_include_directories(array_functions PUBLIC ${SRC_DIR})

# Create test executable
add_executable(array_functions_tests ${TEST_DIR}/array_functions_test.cpp)
target_link_libraries(array_functions_tests array_functions GTest::GTest GTest::Main)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(array_functions_tests)
