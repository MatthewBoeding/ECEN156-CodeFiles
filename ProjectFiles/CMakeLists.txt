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

set(ALL_SOURCES
    ${BASE_SOURCES}
    ${HOTEL_SOURCES}
    ${SYSTEM_SOURCES}
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
# Custom target to run all tests
# ============================================================================
add_custom_target(run_tests
    COMMAND hotel_test_week5
    COMMAND hotel_test_week6
    COMMAND hotel_test_week7
    DEPENDS hotel_test_week5 hotel_test_week6 hotel_test_week7
    COMMENT "Running all Hotel Management tests..."
)

# ============================================================================
# WEEK 5 - Base Classes Test Targets
# ============================================================================

add_custom_target(test_person
    COMMAND hotel_test_week5 --gtest_filter=PersonTest.* 
    DEPENDS hotel_test_week5
    COMMENT "Running Person base class tests..."
)

add_custom_target(test_room_base
    COMMAND hotel_test_week5 --gtest_filter=RoomBaseTest.*
    DEPENDS hotel_test_week5
    COMMENT "Running Room base class tests..."
)

add_custom_target(test_payment_base
    COMMAND hotel_test_week5 --gtest_filter=PaymentBaseTest.*
    DEPENDS hotel_test_week5
    COMMENT "Running Payment base class tests..."
)

# ============================================================================
# WEEK 6 - Derived Classes & Inheritance Test Targets
# ============================================================================

add_custom_target(test_guest
    COMMAND hotel_test_week6 --gtest_filter=GuestTest.*
    DEPENDS hotel_test_week6
    COMMENT "Running Guest class tests..."
)

add_custom_target(test_employee
    COMMAND hotel_test_week6 --gtest_filter=EmployeeTest.*
    DEPENDS hotel_test_week6
    COMMENT "Running Employee class tests..."
)

add_custom_target(test_standard_room
    COMMAND hotel_test_week6 --gtest_filter=StandardRoomTest.*
    DEPENDS hotel_test_week6
    COMMENT "Running StandardRoom tests..."
)

add_custom_target(test_deluxe_room
    COMMAND hotel_test_week6 --gtest_filter=DeluxeRoomTest.*
    DEPENDS hotel_test_week6
    COMMENT "Running DeluxeRoom tests..."
)

add_custom_target(test_suite
    COMMAND hotel_test_week6 --gtest_filter=SuiteTest.*
    DEPENDS hotel_test_week6
    COMMENT "Running Suite tests..."
)

add_custom_target(test_cash_payment
    COMMAND hotel_test_week6 --gtest_filter=CashPaymentTest.*
    DEPENDS hotel_test_week6
    COMMENT "Running CashPayment tests..."
)

add_custom_target(test_credit_payment
    COMMAND hotel_test_week6 --gtest_filter=CreditCardPaymentTest.*
    DEPENDS hotel_test_week6
    COMMENT "Running CreditCardPayment tests..."
)

add_custom_target(test_loyalty_payment
    COMMAND hotel_test_week6 --gtest_filter=LoyaltyPointsPaymentTest.*
    DEPENDS hotel_test_week6
    COMMENT "Running LoyaltyPointsPayment tests..."
)

add_custom_target(test_inheritance
    COMMAND hotel_test_week6 --gtest_filter=InheritanceTest.*
    DEPENDS hotel_test_week6
    COMMENT "Running Inheritance concept tests..."
)

# ============================================================================
# WEEK 7 - Polymorphism & System Integration Test Targets
# ============================================================================

add_custom_target(test_reservation
    COMMAND hotel_test_week7 --gtest_filter=ReservationTest.*
    DEPENDS hotel_test_week7
    COMMENT "Running Reservation tests..."
)

add_custom_target(test_hotel
    COMMAND hotel_test_week7 --gtest_filter=HotelTest.*
    DEPENDS hotel_test_week7
    COMMENT "Running Hotel class tests..."
)

add_custom_target(test_polymorphism
    COMMAND hotel_test_week7 --gtest_filter=PolymorphismTest.*
    DEPENDS hotel_test_week7
    COMMENT "Running Polymorphism tests..."
)

add_custom_target(test_integration
    COMMAND hotel_test_week7 --gtest_filter=IntegrationTest.*
    DEPENDS hotel_test_week7
    COMMENT "Running System Integration tests..."
)

# ============================================================================
# Convenience targets to run tests by week
# ============================================================================

add_custom_target(test_week5
    COMMAND hotel_test_week5
    DEPENDS hotel_test_week5
    COMMENT "Running Week 5 tests (Base Classes: Person, Room, Payment)..."
)

add_custom_target(test_week6
    COMMAND hotel_test_week6
    DEPENDS hotel_test_week6
    COMMENT "Running Week 6 tests (Derived Classes & Inheritance)..."
)

add_custom_target(test_week7
    COMMAND hotel_test_week7
    DEPENDS hotel_test_week7
    COMMENT "Running Week 7 tests (Polymorphism & System Integration)..."
)

# ============================================================================
# Installation (outputs to build directory)
# ============================================================================
install(TARGETS hotel_test_week5 hotel_test_week6 hotel_test_week7 
        DESTINATION ${CMAKE_BINARY_DIR})