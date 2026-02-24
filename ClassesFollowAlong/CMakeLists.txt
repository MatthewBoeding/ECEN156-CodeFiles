cmake_minimum_required(VERSION 3.14)
project(ClassesClassesClasses)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add debug symbols for debugging
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_BUILD_TYPE Debug)

#Find paths
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Create test executable
add_executable(classes_son ${SRC_DIR}/week5_classes_followalong.cpp)
