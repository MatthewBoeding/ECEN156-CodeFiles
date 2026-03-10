cmake_minimum_required(VERSION 3.14)
project(HotelManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define directory paths
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/solution)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Find GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add pthread for Linux
find_package(Threads REQUIRED)

# Include header directory
include_directories(${HEADER_DIR})

# Source files for the project
set(BASE_SOURCES
    ${SRC_DIR}/base_classes.cpp
)

set(HOTEL_SOURCES
    ${SRC_DIR}/hotel_classes.cpp
)

set(SYSTEM_SOURCES
    ${SRC_DIR}/system_classes.cpp
)

set(LIST_SOURCES
    ${SRC_DIR}/reservation_list.cpp)

set(ALL_SOURCES
    ${BASE_SOURCES}
    ${HOTEL_SOURCES}
    ${SYSTEM_SOURCES}
    ${LIST_SOURCES}
)

# ============================================================================
# Week 5 Test Executable - Base Classes
# Tests: Person (base), Room (base), Payment (base)
# ============================================================================
add_executable(hotel_test_week5
    ${ALL_SOURCES}
    ${TEST_DIR}/hotel_test_week5.cpp
)

target_include_directories(hotel_test_week5 PUBLIC ${HEADER_DIR})

target_link_libraries(hotel_test_week5
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    Threads::Threads
)

# ============================================================================
# Week 6 Test Executable - Derived Classes & Inheritance
# Tests: Guest, Employee, StandardRoom, DeluxeRoom, Suite,
#        CashPayment, CreditCardPayment, LoyaltyPointsPayment
# ============================================================================
add_executable(hotel_test_week6
    ${ALL_SOURCES}
    ${TEST_DIR}/hotel_test_week6.cpp
)

target_include_directories(hotel_test_week6 PUBLIC ${HEADER_DIR})

target_link_libraries(hotel_test_week6
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    Threads::Threads
)

# ============================================================================
# Week 7 Test Executable - Polymorphism & System Integration
# Tests: Reservation, Hotel, Polymorphism demonstrations
# ============================================================================
add_executable(hotel_test_week7
    ${ALL_SOURCES}
    ${TEST_DIR}/hotel_test_week7.cpp
)

target_include_directories(hotel_test_week7 PUBLIC ${HEADER_DIR})

target_link_libraries(hotel_test_week7
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    Threads::Threads
)

# ============================================================================
# Full Test Suite (All Three Weeks)
# ============================================================================
add_executable(hotel_test_all
    ${ALL_SOURCES}
    ${TEST_DIR}/hotel_test_week5.cpp
    ${TEST_DIR}/hotel_test_week6.cpp
    ${TEST_DIR}/hotel_test_week7.cpp
)

target_include_directories(hotel_test_all PUBLIC ${HEADER_DIR})

target_link_libraries(hotel_test_all
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    Threads::Threads
)

# ============================================================================
# Week 8 Test Executable - Linked Lists!
# Just making a reservation linked list
# ============================================================================
add_executable(linked_list_test
    ${ALL_SOURCES}
    ${TEST_DIR}/reservation_list_test.cpp
)

target_include_directories(linked_list_test PUBLIC ${HEADER_DIR})

target_link_libraries(linked_list_test
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    Threads::Threads
)