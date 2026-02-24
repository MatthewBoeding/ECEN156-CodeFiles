// ============================================================================
// Hotel Management System - Week 7 Test Suite  
// Tests for: Reservation (polymorphic Room* and Payment*)
//            Hotel (manages polymorphic collections)
//            Polymorphism demonstrations and virtual functions
//            Complete system integration
// 
// Build: g++ -std=c++17 base_classes.cpp hotel_classes.cpp system_classes.cpp hotel_test_week7.cpp -lgtest -lgtest_main -pthread -o hotel_test_week7
// Run: ./hotel_test_week7
// ============================================================================

#include <gtest/gtest.h>
#include <cstring>
#include <cmath>
#include "system_classes.h"  // Includes hotel_classes.h and base_classes.h

// Helper for floating point comparison
#define EXPECT_NEAR_PRICE(val1, val2) EXPECT_NEAR(val1, val2, 0.01)

// RESERVATION TESTS
// ============================================================================

class ReservationTest : public ::testing::Test {
protected:
    Guest guest{1, "Test Guest", "555-0000", "test@test.com", 5000};  // Gold tier
    StandardRoom room{101, 1, 1, false};  // $89/night
    
    void SetUp() override {}
};

TEST_F(ReservationTest, DefaultConstructor) {
    Reservation res;
    EXPECT_EQ(res.getReservationId(), 0);
    EXPECT_EQ(res.getGuest(), nullptr);
    EXPECT_EQ(res.getRoom(), nullptr);
    EXPECT_FALSE(res.getIsActive());
}

TEST_F(ReservationTest, ParameterizedConstructor) {
    Reservation res(1001, &guest, &room, 3, "2024-06-01");
    
    EXPECT_EQ(res.getReservationId(), 1001);
    EXPECT_EQ(res.getGuest(), &guest);
    EXPECT_EQ(res.getRoom(), &room);
    EXPECT_EQ(res.getNights(), 3);
    EXPECT_STREQ(res.getCheckInDate(), "2024-06-01");
    EXPECT_TRUE(res.getIsActive());
    EXPECT_FALSE(res.getIsCheckedIn());
}

TEST_F(ReservationTest, CalculateTotalCostWithDiscount) {
    // Guest is Gold tier (10% discount), room is $89/night, 3 nights
    Reservation res(1001, &guest, &room, 3, "2024-06-01");
    
    double expected = 89.0 * 3 * 0.9;  // 240.30
    EXPECT_NEAR_PRICE(res.calculateTotalCost(), expected);
}

TEST_F(ReservationTest, CalculateTotalCostNoDiscount) {
    Guest bronzeGuest(2, "Bronze", "555-1111", "bronze@test.com", 0);
    Reservation res(1001, &bronzeGuest, &room, 3, "2024-06-01");
    
    double expected = 89.0 * 3;  // 267.0, no discount
    EXPECT_NEAR_PRICE(res.calculateTotalCost(), expected);
}

TEST_F(ReservationTest, CancelReservation) {
    Reservation res(1001, &guest, &room, 3, "2024-06-01");
    EXPECT_TRUE(res.getIsActive());
    
    bool result = res.cancelReservation();
    
    EXPECT_TRUE(result);
    EXPECT_FALSE(res.getIsActive());
}

TEST_F(ReservationTest, CancelReservationAlreadyInactive) {
    Reservation res(1001, &guest, &room, 3, "2024-06-01");
    res.cancelReservation();
    
    bool result = res.cancelReservation();  // Try again
    EXPECT_FALSE(result);
}

TEST_F(ReservationTest, AttachPayment) {
    Reservation res(1001, &guest, &room, 3, "2024-06-01");
    CashPayment payment(1, res.calculateTotalCost(), 300.0);
    
    bool result = res.attachPayment(&payment);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(res.getPayment(), &payment);
}

TEST_F(ReservationTest, CheckInWithPayment) {
    Reservation res(1001, &guest, &room, 3, "2024-06-01");
    CashPayment payment(1, res.calculateTotalCost(), 300.0);
    
    res.attachPayment(&payment);
    payment.processPayment();
    
    bool result = res.checkIn();
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(res.getIsCheckedIn());
    EXPECT_FALSE(room.isVacant());
}

TEST_F(ReservationTest, CheckInWithoutPayment) {
    Reservation res(1001, &guest, &room, 3, "2024-06-01");
    
    bool result = res.checkIn();
    
    EXPECT_FALSE(result);
    EXPECT_FALSE(res.getIsCheckedIn());
}

TEST_F(ReservationTest, CheckOut) {
    Reservation res(1001, &guest, &room, 3, "2024-06-01");
    CashPayment payment(1, res.calculateTotalCost(), 300.0);
    
    res.attachPayment(&payment);
    payment.processPayment();
    res.checkIn();
    
    int staysBefore = guest.getTotalStays();
    bool result = res.checkOut();
    
    EXPECT_TRUE(result);
    EXPECT_FALSE(res.getIsCheckedIn());
    EXPECT_FALSE(res.getIsActive());
    EXPECT_TRUE(room.isVacant());
    EXPECT_EQ(guest.getTotalStays(), staysBefore + 1);
}

// ============================================================================
// HOTEL CLASS TESTS
// ============================================================================

class HotelTest : public ::testing::Test {
protected:
    Hotel* hotel;
    
    void SetUp() override {
        hotel = new Hotel("Test Hotel", "123 Test Street");
    }
    
    void TearDown() override {
        delete hotel;
    }
};

TEST_F(HotelTest, Constructor) {
    EXPECT_STREQ(hotel->getName(), "Test Hotel");
    EXPECT_STREQ(hotel->getAddress(), "123 Test Street");
    EXPECT_EQ(hotel->getRoomCount(), 0);
    EXPECT_EQ(hotel->getGuestCount(), 0);
}

TEST_F(HotelTest, AddRoom) {
    StandardRoom* room = new StandardRoom(101, 1, 1, true);
    bool result = hotel->addRoom(room);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(hotel->getRoomCount(), 1);
}

TEST_F(HotelTest, AddMultipleRoomTypes) {
    hotel->addRoom(new StandardRoom(101, 1, 1, true));
    hotel->addRoom(new DeluxeRoom(201, 2, 1, true, "Ocean"));
    hotel->addRoom(new Suite(301, 3, 2, 800, true, true));
    
    EXPECT_EQ(hotel->getRoomCount(), 3);
}

TEST_F(HotelTest, FindRoomByNumber) {
    StandardRoom* room = new StandardRoom(101, 1, 1, true);
    hotel->addRoom(room);
    
    Room* found = hotel->findRoomByNumber(101);
    
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->getRoomNumber(), 101);
}

TEST_F(HotelTest, FindRoomByNumberNotFound) {
    hotel->addRoom(new StandardRoom(101, 1, 1, true));
    
    Room* found = hotel->findRoomByNumber(999);
    
    EXPECT_EQ(found, nullptr);
}

TEST_F(HotelTest, AddGuest) {
    Guest* guest = new Guest(1, "John", "555-0000", "john@test.com");
    bool result = hotel->addGuest(guest);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(hotel->getGuestCount(), 1);
}

TEST_F(HotelTest, FindGuestById) {
    Guest* guest = new Guest(42, "Jane", "555-1111", "jane@test.com");
    hotel->addGuest(guest);
    
    Guest* found = hotel->findGuestById(42);
    
    EXPECT_NE(found, nullptr);
    EXPECT_STREQ(found->getName(), "Jane");
}

TEST_F(HotelTest, FindGuestByName) {
    Guest* guest = new Guest(1, "Alice Smith", "555-2222", "alice@test.com");
    hotel->addGuest(guest);
    
    Guest* found = hotel->findGuestByName("Alice Smith");
    
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->getId(), 1);
}

TEST_F(HotelTest, GetAvailableRooms) {
    hotel->addRoom(new StandardRoom(101, 1, 1, true));
    hotel->addRoom(new StandardRoom(102, 1, 1, true));
    hotel->addRoom(new StandardRoom(103, 1, 1, true));
    
    // Check one guest into room 102
    Guest* guest = new Guest(1, "Test", "555-0000", "test@test.com");
    hotel->addGuest(guest);
    Room* room102 = hotel->findRoomByNumber(102);
    room102->checkIn(guest);
    
    Room* available[10];
    int count = hotel->getAvailableRooms(available, 10);
    
    EXPECT_EQ(count, 2);  // 101 and 103
}

TEST_F(HotelTest, GetRoomsByType) {
    hotel->addRoom(new StandardRoom(101, 1, 1, true));
    hotel->addRoom(new StandardRoom(102, 1, 2, true));
    hotel->addRoom(new DeluxeRoom(201, 2, 1, true, "Ocean"));
    hotel->addRoom(new Suite(301, 3, 1, 600, true, true));
    
    Room* standards[10];
    int count = hotel->getRoomsByType("Standard", standards, 10);
    
    EXPECT_EQ(count, 2);
    
    Room* deluxes[10];
    count = hotel->getRoomsByType("Deluxe", deluxes, 10);
    
    EXPECT_EQ(count, 1);
}

TEST_F(HotelTest, FindCheapestAvailable) {
    hotel->addRoom(new Suite(301, 3, 1, 600, false, false));      // $299
    hotel->addRoom(new DeluxeRoom(201, 2, 1, false, "City"));     // $149
    hotel->addRoom(new StandardRoom(101, 1, 1, false));           // $89
    
    Room* cheapest = hotel->findCheapestAvailable();
    
    EXPECT_NE(cheapest, nullptr);
    EXPECT_EQ(cheapest->getRoomNumber(), 101);
    EXPECT_NEAR_PRICE(cheapest->getBasePrice(), 89.0);
}

TEST_F(HotelTest, CreateReservation) {
    hotel->addRoom(new StandardRoom(101, 1, 1, true));
    hotel->addGuest(new Guest(1, "Test", "555-0000", "test@test.com"));
    
    Guest* guest = hotel->findGuestById(1);
    Room* room = hotel->findRoomByNumber(101);
    
    Reservation* res = hotel->createReservation(guest, room, 3, "2024-06-01");
    
    EXPECT_NE(res, nullptr);
    EXPECT_EQ(hotel->getReservationCount(), 1);
    EXPECT_EQ(res->getGuest(), guest);
    EXPECT_EQ(res->getRoom(), room);
}

TEST_F(HotelTest, GetOccupancyRate) {
    hotel->addRoom(new StandardRoom(101, 1, 1, true));
    hotel->addRoom(new StandardRoom(102, 1, 1, true));
    hotel->addRoom(new StandardRoom(103, 1, 1, true));
    hotel->addRoom(new StandardRoom(104, 1, 1, true));
    
    // Check in 2 of 4 rooms
    Guest* g1 = new Guest(1, "G1", "555-0000", "g1@test.com");
    Guest* g2 = new Guest(2, "G2", "555-1111", "g2@test.com");
    hotel->addGuest(g1);
    hotel->addGuest(g2);
    
    hotel->findRoomByNumber(101)->checkIn(g1);
    hotel->findRoomByNumber(103)->checkIn(g2);
    
    double rate = hotel->getOccupancyRate();
    
    EXPECT_NEAR_PRICE(rate, 50.0);  // 2/4 = 50%
}

TEST_F(HotelTest, AddEmployee) {
    Employee* emp = new Employee(1, "Worker", "555-0000", "work@test.com", "Manager", 25.0);
    bool result = hotel->addEmployee(emp);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(hotel->getEmployeeCount(), 1);
}

TEST_F(HotelTest, CalculateTotalPayroll) {
    Employee* e1 = new Employee(1, "E1", "555-0000", "e1@test.com", "Clerk", 15.0);
    Employee* e2 = new Employee(2, "E2", "555-1111", "e2@test.com", "Manager", 25.0);
    
    hotel->addEmployee(e1);
    hotel->addEmployee(e2);
    
    e1->addHoursWorked(40);
    e2->addHoursWorked(45);
    
    double payroll = hotel->calculateTotalPayroll();
    
    EXPECT_NEAR_PRICE(payroll, 1787.5);  // 15*40 + 25*45 = 600 + 1125
}

TEST_F(HotelTest, GetGuestsByTier) {
    hotel->addGuest(new Guest(1, "Bronze1", "555-0000", "b1@test.com", 500));
    hotel->addGuest(new Guest(2, "Silver1", "555-1111", "s1@test.com", 2000));
    hotel->addGuest(new Guest(3, "Gold1", "555-2222", "g1@test.com", 7000));
    hotel->addGuest(new Guest(4, "Silver2", "555-3333", "s2@test.com", 3000));
    
    Guest* silvers[10];
    int count = hotel->getGuestsByTier("Silver", silvers, 10);
    
    EXPECT_EQ(count, 2);
}

// ============================================================================
// DISPLAY TESTS (Check they don't crash)
// ============================================================================

TEST_F(HotelTest, DisplayMethodsDoNotCrash) {
    hotel->addRoom(new StandardRoom(101, 1, 1, true));
    hotel->addRoom(new DeluxeRoom(201, 2, 1, true, "Ocean"));
    hotel->addRoom(new Suite(301, 3, 2, 800, true, true));
    hotel->addGuest(new Guest(1, "Test", "555-0000", "test@test.com", 5000));
    hotel->addEmployee(new Employee(1, "Worker", "555-1111", "work@test.com", "Manager", 25.0));
    
    EXPECT_NO_THROW(hotel->displayAllRooms());
    EXPECT_NO_THROW(hotel->displayAvailableRooms());
    EXPECT_NO_THROW(hotel->displayAllGuests());
    EXPECT_NO_THROW(hotel->displayActiveReservations());
    EXPECT_NO_THROW(hotel->displayFinancialSummary());
}

TEST(RoomDisplayTest, AllRoomTypesDisplay) {
    StandardRoom standard(101, 1, 2, true);
    DeluxeRoom deluxe(201, 2, 1, true, "Ocean");
    Suite suite(301, 3, 2, 800, true, true);
    
    EXPECT_NO_THROW(standard.display());
    EXPECT_NO_THROW(deluxe.display());
    EXPECT_NO_THROW(suite.display());
}

TEST(PaymentDisplayTest, AllPaymentTypesDisplay) {
    Guest guest(1, "Test", "555-0000", "test@test.com", 10000);
    
    CashPayment cash(1, 100.0, 120.0);
    CreditCardPayment card(2, 100.0, "1234", "Test", "12/25");
    LoyaltyPointsPayment loyalty(3, 50.0, &guest);
    
    EXPECT_NO_THROW(cash.display());
    EXPECT_NO_THROW(card.display());
    EXPECT_NO_THROW(loyalty.display());
}