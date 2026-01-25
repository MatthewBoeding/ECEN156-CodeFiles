cmake_minimum_required(VERSION 3.14)
project(GuestManagementSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force Debug build for better debugging experience
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
add_library(guest_management ${SRC_DIR}/guest_management.cpp)
target_include_directories(guest_management PUBLIC ${SRC_DIR})

# Create test executable
add_executable(run_tests ${TEST_DIR}/guest_management_test.cpp)
target_link_libraries(run_tests guest_management GTest::GTest GTest::Main)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(run_tests)
