cmake_minimum_required(VERSION 3.14)
project(PointersPointersPointers)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add debug symbols for debugging
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_BUILD_TYPE Debug)

#Find paths
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Create test executable
add_executable(advanced_pointers_practice ${SRC_DIR}/advanced_pointers_practice.cpp)

