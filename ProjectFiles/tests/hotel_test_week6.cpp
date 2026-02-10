// ============================================================================
// Hotel Management System - Week 6 Test Suite
// Tests for: Guest, Employee (derived from Person)
//            StandardRoom, DeluxeRoom, Suite (derived from Room)
//            CashPayment, CreditCardPayment, LoyaltyPointsPayment (derived from Payment)
// Focus: Inheritance, constructor chaining, implementing pure virtual functions
// 
// Build: g++ -std=c++17 base_classes.cpp hotel_classes.cpp system_classes.cpp hotel_test_week6.cpp -lgtest -lgtest_main -pthread -o hotel_test_week6
// Run: ./hotel_test_week6
// ============================================================================

#include <gtest/gtest.h>
#include <cstring>
#include <cmath>
#include "hotel_classes.h"  // Includes base_classes.h

// Helper for floating point comparison
#define EXPECT_NEAR_PRICE(val1, val2) EXPECT_NEAR(val1, val2, 0.01)

// ============================================================================
// GUEST CLASS TESTS
// ============================================================================

class GuestTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }
};

// --- Constructor Tests ---

TEST_F(GuestTest, DefaultConstructor) {
    Guest g;
    EXPECT_EQ(g.getId(), 0);
    EXPECT_STREQ(g.getName(), "");
    EXPECT_EQ(g.getLoyaltyPoints(), 0);
    EXPECT_FALSE(g.getIsCheckedIn());
    EXPECT_EQ(g.getTotalStays(), 0);
}

TEST_F(GuestTest, ParameterizedConstructorWithDefaultPoints) {
    Guest g(201, "Jane Doe", "555-2222", "jane@hotel.com");
    EXPECT_EQ(g.getId(), 201);
    EXPECT_STREQ(g.getName(), "Jane Doe");
    EXPECT_STREQ(g.getPhone(), "555-2222");
    EXPECT_STREQ(g.getEmail(), "jane@hotel.com");
    EXPECT_EQ(g.getLoyaltyPoints(), 0);
    EXPECT_FALSE(g.getIsCheckedIn());
    EXPECT_EQ(g.getTotalStays(), 0);
}

TEST_F(GuestTest, ParameterizedConstructorWithPoints) {
    Guest g(202, "Bob Smith", "555-3333", "bob@hotel.com", 500);
    EXPECT_EQ(g.getId(), 202);
    EXPECT_STREQ(g.getName(), "Bob Smith");
    EXPECT_EQ(g.getLoyaltyPoints(), 500);
    EXPECT_FALSE(g.getIsCheckedIn());
}

// --- Inheritance Tests ---

TEST_F(GuestTest, InheritsFromPerson) {
    Guest g(100, "Test Guest", "555-0000", "guest@test.com", 100);
    
    // Should be able to use Person methods
    EXPECT_EQ(g.getId(), 100);
    EXPECT_STREQ(g.getName(), "Test Guest");
    
    // Can use setters from Person
    g.setEmail("new@email.com");
    EXPECT_STREQ(g.getEmail(), "new@email.com");
}

// --- Loyalty Points Tests ---

TEST_F(GuestTest, AddLoyaltyPointsPositive) {
    Guest g(1, "Test", "555-0000", "test@test.com", 100);
    g.addLoyaltyPoints(50);
    EXPECT_EQ(g.getLoyaltyPoints(), 150);
}

TEST_F(GuestTest, AddLoyaltyPointsMultiple) {
    Guest g(1, "Test", "555-0000", "test@test.com", 0);
    g.addLoyaltyPoints(100);
    g.addLoyaltyPoints(200);
    g.addLoyaltyPoints(50);
    EXPECT_EQ(g.getLoyaltyPoints(), 350);
}

TEST_F(GuestTest, AddLoyaltyPointsZeroOrNegative) {
    Guest g(1, "Test", "555-0000", "test@test.com", 100);
    g.addLoyaltyPoints(0);
    EXPECT_EQ(g.getLoyaltyPoints(), 100);  // Unchanged
    g.addLoyaltyPoints(-50);
    EXPECT_EQ(g.getLoyaltyPoints(), 100);  // Still unchanged
}

TEST_F(GuestTest, RedeemPointsSuccess) {
    Guest g(1, "Test", "555-0000", "test@test.com", 500);
    bool result = g.redeemPoints(200);
    EXPECT_TRUE(result);
    EXPECT_EQ(g.getLoyaltyPoints(), 300);
}

TEST_F(GuestTest, RedeemPointsExactAmount) {
    Guest g(1, "Test", "555-0000", "test@test.com", 500);
    bool result = g.redeemPoints(500);
    EXPECT_TRUE(result);
    EXPECT_EQ(g.getLoyaltyPoints(), 0);
}

TEST_F(GuestTest, RedeemPointsInsufficientFunds) {
    Guest g(1, "Test", "555-0000", "test@test.com", 100);
    bool result = g.redeemPoints(200);
    EXPECT_FALSE(result);
    EXPECT_EQ(g.getLoyaltyPoints(), 100);  // Unchanged
}

TEST_F(GuestTest, RedeemPointsZeroOrNegative) {
    Guest g(1, "Test", "555-0000", "test@test.com", 100);
    bool result = g.redeemPoints(0);
    EXPECT_FALSE(result);
    result = g.redeemPoints(-50);
    EXPECT_FALSE(result);
    EXPECT_EQ(g.getLoyaltyPoints(), 100);  // Unchanged
}

// --- Loyalty Tier Tests ---

TEST_F(GuestTest, LoyaltyTierBronze) {
    Guest g1(1, "Test", "555-0000", "test@test.com", 0);
    Guest g2(2, "Test", "555-0000", "test@test.com", 500);
    Guest g3(3, "Test", "555-0000", "test@test.com", 999);
    
    EXPECT_STREQ(g1.getLoyaltyTier(), "Bronze");
    EXPECT_STREQ(g2.getLoyaltyTier(), "Bronze");
    EXPECT_STREQ(g3.getLoyaltyTier(), "Bronze");
}

TEST_F(GuestTest, LoyaltyTierSilver) {
    Guest g1(1, "Test", "555-0000", "test@test.com", 1000);
    Guest g2(2, "Test", "555-0000", "test@test.com", 3000);
    Guest g3(3, "Test", "555-0000", "test@test.com", 4999);
    
    EXPECT_STREQ(g1.getLoyaltyTier(), "Silver");
    EXPECT_STREQ(g2.getLoyaltyTier(), "Silver");
    EXPECT_STREQ(g3.getLoyaltyTier(), "Silver");
}

TEST_F(GuestTest, LoyaltyTierGold) {
    Guest g1(1, "Test", "555-0000", "test@test.com", 5000);
    Guest g2(2, "Test", "555-0000", "test@test.com", 7500);
    Guest g3(3, "Test", "555-0000", "test@test.com", 9999);
    
    EXPECT_STREQ(g1.getLoyaltyTier(), "Gold");
    EXPECT_STREQ(g2.getLoyaltyTier(), "Gold");
    EXPECT_STREQ(g3.getLoyaltyTier(), "Gold");
}

TEST_F(GuestTest, LoyaltyTierPlatinum) {
    Guest g1(1, "Test", "555-0000", "test@test.com", 10000);
    Guest g2(2, "Test", "555-0000", "test@test.com", 50000);
    
    EXPECT_STREQ(g1.getLoyaltyTier(), "Platinum");
    EXPECT_STREQ(g2.getLoyaltyTier(), "Platinum");
}

// --- Tier Discount Tests ---

TEST_F(GuestTest, TierDiscountBronze) {
    Guest g(1, "Test", "555-0000", "test@test.com", 500);
    EXPECT_DOUBLE_EQ(g.getTierDiscount(), 0.0);
}

TEST_F(GuestTest, TierDiscountSilver) {
    Guest g(1, "Test", "555-0000", "test@test.com", 2000);
    EXPECT_DOUBLE_EQ(g.getTierDiscount(), 0.05);
}

TEST_F(GuestTest, TierDiscountGold) {
    Guest g(1, "Test", "555-0000", "test@test.com", 7000);
    EXPECT_DOUBLE_EQ(g.getTierDiscount(), 0.10);
}

TEST_F(GuestTest, TierDiscountPlatinum) {
    Guest g(1, "Test", "555-0000", "test@test.com", 15000);
    EXPECT_DOUBLE_EQ(g.getTierDiscount(), 0.15);
}

// --- Check-In Status Tests ---

TEST_F(GuestTest, SetCheckedIn) {
    Guest g(1, "Test", "555-0000", "test@test.com");
    EXPECT_FALSE(g.getIsCheckedIn());
    
    g.setCheckedIn(true);
    EXPECT_TRUE(g.getIsCheckedIn());
    
    g.setCheckedIn(false);
    EXPECT_FALSE(g.getIsCheckedIn());
}

// --- Stay Recording Tests ---

TEST_F(GuestTest, RecordStay) {
    Guest g(1, "Test", "555-0000", "test@test.com");
    EXPECT_EQ(g.getTotalStays(), 0);
    
    g.recordStay();
    EXPECT_EQ(g.getTotalStays(), 1);
    
    g.recordStay();
    g.recordStay();
    EXPECT_EQ(g.getTotalStays(), 3);
}

// --- Tier Progression Tests ---

TEST_F(GuestTest, TierProgressionThroughPoints) {
    Guest g(1, "Test", "555-0000", "test@test.com", 0);
    
    EXPECT_STREQ(g.getLoyaltyTier(), "Bronze");
    
    g.addLoyaltyPoints(1000);
    EXPECT_STREQ(g.getLoyaltyTier(), "Silver");
    
    g.addLoyaltyPoints(4000);
    EXPECT_STREQ(g.getLoyaltyTier(), "Gold");
    
    g.addLoyaltyPoints(5000);
    EXPECT_STREQ(g.getLoyaltyTier(), "Platinum");
}

// ============================================================================
// EMPLOYEE CLASS TESTS
// ============================================================================

class EmployeeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }
};

// --- Constructor Tests ---

TEST_F(EmployeeTest, DefaultConstructor) {
    Employee e;
    EXPECT_EQ(e.getId(), 0);
    EXPECT_STREQ(e.getName(), "");
    EXPECT_STREQ(e.getPosition(), "");
    EXPECT_DOUBLE_EQ(e.getHourlyWage(), 0.0);
    EXPECT_EQ(e.getHoursWorked(), 0);
}

TEST_F(EmployeeTest, ParameterizedConstructor) {
    Employee e(301, "Alice Worker", "555-4444", "alice@hotel.com", "Front Desk", 18.50);
    
    EXPECT_EQ(e.getId(), 301);
    EXPECT_STREQ(e.getName(), "Alice Worker");
    EXPECT_STREQ(e.getPhone(), "555-4444");
    EXPECT_STREQ(e.getEmail(), "alice@hotel.com");
    EXPECT_STREQ(e.getPosition(), "Front Desk");
    EXPECT_DOUBLE_EQ(e.getHourlyWage(), 18.50);
    EXPECT_EQ(e.getHoursWorked(), 0);
}

// --- Inheritance Tests ---

TEST_F(EmployeeTest, InheritsFromPerson) {
    Employee e(100, "Test Employee", "555-0000", "emp@test.com", "Manager", 25.00);
    
    // Should be able to use Person methods
    EXPECT_EQ(e.getId(), 100);
    EXPECT_STREQ(e.getName(), "Test Employee");
    
    // Can use setters from Person
    e.setPhone("999-9999");
    EXPECT_STREQ(e.getPhone(), "999-9999");
}

// --- Position Tests ---

TEST_F(EmployeeTest, SetPosition) {
    Employee e(1, "Test", "555-0000", "test@test.com", "Clerk", 15.00);
    e.setPosition("Manager");
    EXPECT_STREQ(e.getPosition(), "Manager");
}

// --- Wage Tests ---

TEST_F(EmployeeTest, SetHourlyWagePositive) {
    Employee e(1, "Test", "555-0000", "test@test.com", "Clerk", 15.00);
    e.setHourlyWage(20.00);
    EXPECT_DOUBLE_EQ(e.getHourlyWage(), 20.00);
}

TEST_F(EmployeeTest, SetHourlyWageZeroOrNegative) {
    Employee e(1, "Test", "555-0000", "test@test.com", "Clerk", 15.00);
    e.setHourlyWage(0.0);
    EXPECT_DOUBLE_EQ(e.getHourlyWage(), 15.00);  // Unchanged
    e.setHourlyWage(-10.0);
    EXPECT_DOUBLE_EQ(e.getHourlyWage(), 15.00);  // Unchanged
}

// --- Hours Worked Tests ---

TEST_F(EmployeeTest, AddHoursWorkedPositive) {
    Employee e(1, "Test", "555-0000", "test@test.com", "Clerk", 15.00);
    e.addHoursWorked(8);
    EXPECT_EQ(e.getHoursWorked(), 8);
    
    e.addHoursWorked(4);
    EXPECT_EQ(e.getHoursWorked(), 12);
}

TEST_F(EmployeeTest, AddHoursWorkedZeroOrNegative) {
    Employee e(1, "Test", "555-0000", "test@test.com", "Clerk", 15.00);
    e.addHoursWorked(8);
    
    e.addHoursWorked(0);
    EXPECT_EQ(e.getHoursWorked(), 8);  // Unchanged
    
    e.addHoursWorked(-5);
    EXPECT_EQ(e.getHoursWorked(), 8);  // Unchanged
}

// --- Pay Calculation Tests ---

TEST_F(EmployeeTest, CalculatePayNoHours) {
    Employee e(1, "Test", "555-0000", "test@test.com", "Clerk", 15.00);
    EXPECT_DOUBLE_EQ(e.calculatePay(), 0.0);
}

TEST_F(EmployeeTest, CalculatePayWithHours) {
    Employee e(1, "Test", "555-0000", "test@test.com", "Clerk", 15.00);
    e.addHoursWorked(40);
    EXPECT_DOUBLE_EQ(e.calculatePay(), 600.0);  // 15 * 40
}

TEST_F(EmployeeTest, CalculatePayDecimalWage) {
    Employee e(1, "Test", "555-0000", "test@test.com", "Clerk", 18.75);
    e.addHoursWorked(20);
    EXPECT_DOUBLE_EQ(e.calculatePay(), 375.0);  // 18.75 * 20
}

// --- Reset Hours Tests ---

TEST_F(EmployeeTest, ResetHours) {
    Employee e(1, "Test", "555-0000", "test@test.com", "Clerk", 15.00);
    e.addHoursWorked(40);
    EXPECT_EQ(e.getHoursWorked(), 40);
    
    e.resetHours();
    EXPECT_EQ(e.getHoursWorked(), 0);
    EXPECT_DOUBLE_EQ(e.calculatePay(), 0.0);
}

TEST_F(EmployeeTest, ResetHoursDoesNotAffectWage) {
    Employee e(1, "Test", "555-0000", "test@test.com", "Clerk", 20.00);
    e.addHoursWorked(40);
    e.resetHours();
    
    EXPECT_DOUBLE_EQ(e.getHourlyWage(), 20.00);  // Wage unchanged
    EXPECT_STREQ(e.getPosition(), "Clerk");       // Position unchanged
}

// ============================================================================
// STANDARD ROOM TESTS
// ============================================================================

class StandardRoomTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(StandardRoomTest, DefaultConstructor) {
    StandardRoom room;
    EXPECT_EQ(room.getRoomNumber(), 0);
    EXPECT_EQ(room.getFloor(), 1);
    EXPECT_TRUE(room.getIsClean());
    EXPECT_FALSE(room.getIsUnderMaintenance());
    EXPECT_TRUE(room.isVacant());
    EXPECT_EQ(room.getCurrentGuest(), nullptr);
}

TEST_F(StandardRoomTest, ParameterizedConstructor) {
    StandardRoom room(101, 1, 2, true);
    EXPECT_EQ(room.getRoomNumber(), 101);
    EXPECT_EQ(room.getFloor(), 1);
    EXPECT_EQ(room.getNumBeds(), 2);
    EXPECT_TRUE(room.getHasWindow());
}

TEST_F(StandardRoomTest, RoomTypeReturnsCorrectString) {
    StandardRoom room(101, 1, 1, false);
    EXPECT_STREQ(room.getRoomType(), "Standard");
}

TEST_F(StandardRoomTest, BasePriceOneBedNoWindow) {
    StandardRoom room(101, 1, 1, false);
    EXPECT_NEAR_PRICE(room.getBasePrice(), 89.0);
}

TEST_F(StandardRoomTest, BasePriceOneBedWithWindow) {
    StandardRoom room(102, 1, 1, true);
    EXPECT_NEAR_PRICE(room.getBasePrice(), 99.0);  // 89 + 10
}

TEST_F(StandardRoomTest, BasePriceTwoBedsNoWindow) {
    StandardRoom room(103, 1, 2, false);
    EXPECT_NEAR_PRICE(room.getBasePrice(), 109.0);
}

TEST_F(StandardRoomTest, BasePriceTwoBedsWithWindow) {
    StandardRoom room(104, 1, 2, true);
    EXPECT_NEAR_PRICE(room.getBasePrice(), 119.0);  // 109 + 10
}

TEST_F(StandardRoomTest, MaxOccupancyOneBed) {
    StandardRoom room(101, 1, 1, false);
    EXPECT_EQ(room.getMaxOccupancy(), 2);
}

TEST_F(StandardRoomTest, MaxOccupancyTwoBeds) {
    StandardRoom room(101, 1, 2, false);
    EXPECT_EQ(room.getMaxOccupancy(), 4);
}

TEST_F(StandardRoomTest, CalculatePriceMultipleNights) {
    StandardRoom room(101, 1, 1, false);  // $89/night
    EXPECT_NEAR_PRICE(room.calculatePrice(3), 267.0);  // 89 * 3
}

TEST_F(StandardRoomTest, AmenitiesNotNull) {
    StandardRoom room(101, 1, 1, true);
    EXPECT_NE(room.getAmenities(), nullptr);
    EXPECT_GT(strlen(room.getAmenities()), 0);
}

// ============================================================================
// DELUXE ROOM TESTS
// ============================================================================

class DeluxeRoomTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(DeluxeRoomTest, DefaultConstructor) {
    DeluxeRoom room;
    EXPECT_TRUE(room.getHasMiniFridge());  // Always true for deluxe
}

TEST_F(DeluxeRoomTest, ParameterizedConstructor) {
    DeluxeRoom room(201, 2, 1, true, "Ocean");
    EXPECT_EQ(room.getRoomNumber(), 201);
    EXPECT_EQ(room.getFloor(), 2);
    EXPECT_EQ(room.getNumBeds(), 1);
    EXPECT_TRUE(room.getHasBalcony());
    EXPECT_STREQ(room.getViewType(), "Ocean");
}

TEST_F(DeluxeRoomTest, RoomTypeReturnsCorrectString) {
    DeluxeRoom room(201, 2, 1, false, "City");
    EXPECT_STREQ(room.getRoomType(), "Deluxe");
}

TEST_F(DeluxeRoomTest, BasePriceOneBedBasic) {
    DeluxeRoom room(201, 2, 1, false, "City");
    EXPECT_NEAR_PRICE(room.getBasePrice(), 149.0);
}

TEST_F(DeluxeRoomTest, BasePriceTwoBedsBasic) {
    DeluxeRoom room(202, 2, 2, false, "City");
    EXPECT_NEAR_PRICE(room.getBasePrice(), 179.0);
}

TEST_F(DeluxeRoomTest, BasePriceWithBalcony) {
    DeluxeRoom room(203, 2, 1, true, "City");
    EXPECT_NEAR_PRICE(room.getBasePrice(), 174.0);  // 149 + 25
}

TEST_F(DeluxeRoomTest, BasePriceWithOceanView) {
    DeluxeRoom room(204, 2, 1, false, "Ocean");
    EXPECT_NEAR_PRICE(room.getBasePrice(), 164.0);  // 149 + 15
}

TEST_F(DeluxeRoomTest, BasePriceWithPoolView) {
    DeluxeRoom room(205, 2, 1, false, "Pool");
    EXPECT_NEAR_PRICE(room.getBasePrice(), 159.0);  // 149 + 10
}

TEST_F(DeluxeRoomTest, BasePriceFullyLoaded) {
    DeluxeRoom room(206, 2, 2, true, "Ocean");
    // 179 (2 beds) + 25 (balcony) + 15 (ocean) = 219
    EXPECT_NEAR_PRICE(room.getBasePrice(), 219.0);
}

TEST_F(DeluxeRoomTest, MaxOccupancy) {
    DeluxeRoom room1(201, 2, 1, false, "City");
    DeluxeRoom room2(202, 2, 2, false, "City");
    
    EXPECT_EQ(room1.getMaxOccupancy(), 2);
    EXPECT_EQ(room2.getMaxOccupancy(), 4);
}

// ============================================================================
// SUITE TESTS
// ============================================================================

class SuiteTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(SuiteTest, DefaultConstructor) {
    Suite suite;
    EXPECT_TRUE(suite.getHasLivingRoom());  // Always true for suites
}

TEST_F(SuiteTest, ParameterizedConstructor) {
    Suite suite(301, 3, 2, 800, true, true);
    EXPECT_EQ(suite.getRoomNumber(), 301);
    EXPECT_EQ(suite.getFloor(), 3);
    EXPECT_EQ(suite.getNumBedrooms(), 2);
    EXPECT_EQ(suite.getSquareFeet(), 800);
    EXPECT_TRUE(suite.getHasKitchen());
    EXPECT_TRUE(suite.getHasJacuzzi());
}

TEST_F(SuiteTest, RoomTypeReturnsCorrectString) {
    Suite suite(301, 3, 1, 600, false, false);
    EXPECT_STREQ(suite.getRoomType(), "Suite");
}

TEST_F(SuiteTest, BasePriceOneBedroom) {
    Suite suite(301, 3, 1, 600, false, false);
    EXPECT_NEAR_PRICE(suite.getBasePrice(), 299.0);
}

TEST_F(SuiteTest, BasePriceTwoBedroom) {
    Suite suite(302, 3, 2, 800, false, false);
    EXPECT_NEAR_PRICE(suite.getBasePrice(), 399.0);
}

TEST_F(SuiteTest, BasePriceThreeBedroom) {
    Suite suite(303, 3, 3, 1200, false, false);
    EXPECT_NEAR_PRICE(suite.getBasePrice(), 549.0);
}

TEST_F(SuiteTest, BasePriceWithKitchen) {
    Suite suite(304, 3, 1, 600, true, false);
    EXPECT_NEAR_PRICE(suite.getBasePrice(), 374.0);  // 299 + 75
}

TEST_F(SuiteTest, BasePriceWithJacuzzi) {
    Suite suite(305, 3, 1, 600, false, true);
    EXPECT_NEAR_PRICE(suite.getBasePrice(), 399.0);  // 299 + 100
}

TEST_F(SuiteTest, BasePriceFullyLoaded) {
    Suite suite(306, 3, 2, 1000, true, true);
    // 399 (2BR) + 75 (kitchen) + 100 (jacuzzi) = 574
    EXPECT_NEAR_PRICE(suite.getBasePrice(), 574.0);
}

TEST_F(SuiteTest, MaxOccupancy) {
    Suite suite1(301, 3, 1, 600, false, false);  // 1BR
    Suite suite2(302, 3, 2, 800, false, false);  // 2BR
    Suite suite3(303, 3, 3, 1200, false, false); // 3BR
    
    // 2 per bedroom + 2 for living room
    EXPECT_EQ(suite1.getMaxOccupancy(), 4);   // 2*1 + 2
    EXPECT_EQ(suite2.getMaxOccupancy(), 6);   // 2*2 + 2
    EXPECT_EQ(suite3.getMaxOccupancy(), 8);   // 2*3 + 2
}

TEST_F(SuiteTest, CalculatePriceShortStay) {
    Suite suite(301, 3, 1, 600, false, false);  // $299/night
    EXPECT_NEAR_PRICE(suite.calculatePrice(3), 897.0);  // No discount
}

TEST_F(SuiteTest, CalculatePriceLongStayDiscount) {
    Suite suite(301, 3, 1, 600, false, false);  // $299/night
    // 7+ nights = 10% discount
    double expected = 299.0 * 7 * 0.9;  // 1883.70
    EXPECT_NEAR_PRICE(suite.calculatePrice(7), expected);
}

TEST_F(SuiteTest, CalculatePriceExtendedStay) {
    Suite suite(301, 3, 1, 600, false, false);  // $299/night
    // 10 nights with 10% discount
    double expected = 299.0 * 10 * 0.9;  // 2691.0
    EXPECT_NEAR_PRICE(suite.calculatePrice(10), expected);
}

// ============================================================================
// ROOM CHECK-IN/CHECK-OUT TESTS
// ============================================================================

class RoomGuestTest : public ::testing::Test {
protected:
    Guest guest{1, "Test Guest", "555-0000", "test@test.com", 1000};
    StandardRoom room{101, 1, 1, true};
    
    void SetUp() override {}
};

TEST_F(RoomGuestTest, CheckInSuccess) {
    EXPECT_TRUE(room.isVacant());
    
    bool result = room.checkIn(&guest);
    
    EXPECT_TRUE(result);
    EXPECT_FALSE(room.isVacant());
    EXPECT_EQ(room.getCurrentGuest(), &guest);
    EXPECT_TRUE(guest.getIsCheckedIn());
}

TEST_F(RoomGuestTest, CheckInFailsWhenOccupied) {
    Guest guest2(2, "Second Guest", "555-1111", "guest2@test.com");
    
    room.checkIn(&guest);
    bool result = room.checkIn(&guest2);
    
    EXPECT_FALSE(result);
    EXPECT_EQ(room.getCurrentGuest(), &guest);  // Original guest still there
}

TEST_F(RoomGuestTest, CheckInFailsWithNullGuest) {
    bool result = room.checkIn(nullptr);
    
    EXPECT_FALSE(result);
    EXPECT_TRUE(room.isVacant());
}

TEST_F(RoomGuestTest, CheckInFailsWhenDirty) {
    room.setClean(false);
    bool result = room.checkIn(&guest);
    
    EXPECT_FALSE(result);
    EXPECT_TRUE(room.isVacant());
}

TEST_F(RoomGuestTest, CheckInFailsUnderMaintenance) {
    room.setUnderMaintenance(true);
    bool result = room.checkIn(&guest);
    
    EXPECT_FALSE(result);
    EXPECT_TRUE(room.isVacant());
}

TEST_F(RoomGuestTest, CheckOutSuccess) {
    room.checkIn(&guest);
    
    Guest* returned = room.checkOut();
    
    EXPECT_EQ(returned, &guest);
    EXPECT_TRUE(room.isVacant());
    EXPECT_FALSE(guest.getIsCheckedIn());
}

TEST_F(RoomGuestTest, CheckOutEmptyRoom) {
    Guest* returned = room.checkOut();
    
    EXPECT_EQ(returned, nullptr);
    EXPECT_TRUE(room.isVacant());
}

TEST_F(RoomGuestTest, RoomMarkedDirtyAfterCheckIn) {
    room.setClean(true);
    room.checkIn(&guest);
    
    // Room should be marked for cleaning after check-in
    EXPECT_FALSE(room.getIsClean());
}

// ============================================================================
// POLYMORPHISM TESTS
// ============================================================================

class PolymorphismTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(PolymorphismTest, RoomPointerToStandardRoom) {
    StandardRoom standard(101, 1, 2, true);
    Room* roomPtr = &standard;
    
    EXPECT_STREQ(roomPtr->getRoomType(), "Standard");
    EXPECT_NEAR_PRICE(roomPtr->getBasePrice(), 119.0);  // 109 + 10 window
}

TEST_F(PolymorphismTest, RoomPointerToDeluxeRoom) {
    DeluxeRoom deluxe(201, 2, 1, true, "Ocean");
    Room* roomPtr = &deluxe;
    
    EXPECT_STREQ(roomPtr->getRoomType(), "Deluxe");
    EXPECT_NEAR_PRICE(roomPtr->getBasePrice(), 189.0);  // 149 + 25 + 15
}

TEST_F(PolymorphismTest, RoomPointerToSuite) {
    Suite suite(301, 3, 2, 800, true, false);
    Room* roomPtr = &suite;
    
    EXPECT_STREQ(roomPtr->getRoomType(), "Suite");
    EXPECT_NEAR_PRICE(roomPtr->getBasePrice(), 474.0);  // 399 + 75
}

TEST_F(PolymorphismTest, PolymorphicArray) {
    StandardRoom standard(101, 1, 1, false);  // $89
    DeluxeRoom deluxe(201, 2, 1, false, "City");  // $149
    Suite suite(301, 3, 1, 600, false, false);  // $299
    
    Room* rooms[3] = {&standard, &deluxe, &suite};
    
    double totalPrice = 0;
    for (int i = 0; i < 3; i++) {
        totalPrice += rooms[i]->getBasePrice();
    }
    
    EXPECT_NEAR_PRICE(totalPrice, 537.0);  // 89 + 149 + 299
}

TEST_F(PolymorphismTest, PolymorphicCalculatePrice) {
    StandardRoom standard(101, 1, 1, false);  // No discount
    Suite suite(301, 3, 1, 600, false, false);  // 10% off for 7+ nights
    
    Room* rooms[2] = {&standard, &suite};
    
    // Both for 7 nights
    double standardTotal = rooms[0]->calculatePrice(7);  // 89 * 7 = 623
    double suiteTotal = rooms[1]->calculatePrice(7);     // 299 * 7 * 0.9 = 1883.70
    
    EXPECT_NEAR_PRICE(standardTotal, 623.0);
    EXPECT_NEAR_PRICE(suiteTotal, 1883.70);
}

// ============================================================================
// PAYMENT TESTS - CASH
// ============================================================================

class CashPaymentTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(CashPaymentTest, Constructor) {
    CashPayment payment(1, 100.0, 120.0);
    EXPECT_EQ(payment.getPaymentId(), 1);
    EXPECT_DOUBLE_EQ(payment.getAmount(), 100.0);
    EXPECT_DOUBLE_EQ(payment.getAmountTendered(), 120.0);
    EXPECT_FALSE(payment.getIsProcessed());
}

TEST_F(CashPaymentTest, ProcessPaymentSuccess) {
    CashPayment payment(1, 100.0, 120.0);
    bool result = payment.processPayment();
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(payment.getIsProcessed());
    EXPECT_DOUBLE_EQ(payment.getChangeGiven(), 20.0);
}

TEST_F(CashPaymentTest, ProcessPaymentExactAmount) {
    CashPayment payment(1, 100.0, 100.0);
    bool result = payment.processPayment();
    
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(payment.getChangeGiven(), 0.0);
}

TEST_F(CashPaymentTest, ProcessPaymentInsufficientFunds) {
    CashPayment payment(1, 100.0, 80.0);
    bool result = payment.processPayment();
    
    EXPECT_FALSE(result);
    EXPECT_FALSE(payment.getIsProcessed());
}

TEST_F(CashPaymentTest, ProcessPaymentAlreadyProcessed) {
    CashPayment payment(1, 100.0, 120.0);
    payment.processPayment();
    bool result = payment.processPayment();  // Try again
    
    EXPECT_FALSE(result);
}

TEST_F(CashPaymentTest, RefundSuccess) {
    CashPayment payment(1, 100.0, 120.0);
    payment.processPayment();
    bool result = payment.refund();
    
    EXPECT_TRUE(result);
    EXPECT_FALSE(payment.getIsProcessed());
}

TEST_F(CashPaymentTest, RefundNotProcessed) {
    CashPayment payment(1, 100.0, 120.0);
    bool result = payment.refund();
    
    EXPECT_FALSE(result);
}

TEST_F(CashPaymentTest, PaymentType) {
    CashPayment payment(1, 100.0, 120.0);
    EXPECT_STREQ(payment.getPaymentType(), "Cash");
}

TEST_F(CashPaymentTest, NoTransactionFee) {
    CashPayment payment(1, 100.0, 120.0);
    EXPECT_DOUBLE_EQ(payment.getTransactionFee(), 0.0);
}

// ============================================================================
// PAYMENT TESTS - CREDIT CARD
// ============================================================================

class CreditCardPaymentTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(CreditCardPaymentTest, Constructor) {
    CreditCardPayment payment(1, 200.0, "4532", "John Doe", "12/25");
    EXPECT_EQ(payment.getPaymentId(), 1);
    EXPECT_DOUBLE_EQ(payment.getAmount(), 200.0);
    EXPECT_STREQ(payment.getCardNumber(), "4532");
    EXPECT_STREQ(payment.getCardHolderName(), "John Doe");
    EXPECT_FALSE(payment.getIsProcessed());
}

TEST_F(CreditCardPaymentTest, ProcessPaymentSuccess) {
    CreditCardPayment payment(1, 200.0, "4532", "John Doe", "12/25");
    bool result = payment.processPayment();
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(payment.getIsProcessed());
    EXPECT_TRUE(payment.getIsAuthorized());
}

TEST_F(CreditCardPaymentTest, ProcessPaymentAlreadyProcessed) {
    CreditCardPayment payment(1, 200.0, "4532", "John Doe", "12/25");
    payment.processPayment();
    bool result = payment.processPayment();
    
    EXPECT_FALSE(result);
}

TEST_F(CreditCardPaymentTest, RefundSuccess) {
    CreditCardPayment payment(1, 200.0, "4532", "John Doe", "12/25");
    payment.processPayment();
    bool result = payment.refund();
    
    EXPECT_TRUE(result);
    EXPECT_FALSE(payment.getIsProcessed());
    EXPECT_FALSE(payment.getIsAuthorized());
}

TEST_F(CreditCardPaymentTest, PaymentType) {
    CreditCardPayment payment(1, 200.0, "4532", "John Doe", "12/25");
    EXPECT_STREQ(payment.getPaymentType(), "Credit Card");
}

TEST_F(CreditCardPaymentTest, TransactionFee) {
    CreditCardPayment payment(1, 200.0, "4532", "John Doe", "12/25");
    EXPECT_NEAR_PRICE(payment.getTransactionFee(), 5.0);  // 2.5% of 200
}

TEST_F(CreditCardPaymentTest, TransactionFeeDecimal) {
    CreditCardPayment payment(1, 123.45, "4532", "John Doe", "12/25");
    EXPECT_NEAR_PRICE(payment.getTransactionFee(), 3.08625);  // 2.5% of 123.45
}

// ============================================================================
// PAYMENT TESTS - LOYALTY POINTS
// ============================================================================

class LoyaltyPointsPaymentTest : public ::testing::Test {
protected:
    Guest guest{1, "Test Guest", "555-0000", "test@test.com", 10000};
    
    void SetUp() override {}
};

TEST_F(LoyaltyPointsPaymentTest, Constructor) {
    LoyaltyPointsPayment payment(1, 50.0, &guest);
    EXPECT_EQ(payment.getPaymentId(), 1);
    EXPECT_DOUBLE_EQ(payment.getAmount(), 50.0);
    EXPECT_EQ(payment.getPointsUsed(), 5000);  // 100 points per dollar
}

TEST_F(LoyaltyPointsPaymentTest, CanAffordTrue) {
    LoyaltyPointsPayment payment(1, 50.0, &guest);  // Needs 5000, has 10000
    EXPECT_TRUE(payment.canAfford());
}

TEST_F(LoyaltyPointsPaymentTest, CanAffordFalse) {
    LoyaltyPointsPayment payment(1, 150.0, &guest);  // Needs 15000, has 10000
    EXPECT_FALSE(payment.canAfford());
}

TEST_F(LoyaltyPointsPaymentTest, ProcessPaymentSuccess) {
    LoyaltyPointsPayment payment(1, 50.0, &guest);
    bool result = payment.processPayment();
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(payment.getIsProcessed());
    EXPECT_EQ(guest.getLoyaltyPoints(), 5000);  // 10000 - 5000
}

TEST_F(LoyaltyPointsPaymentTest, ProcessPaymentInsufficientPoints) {
    LoyaltyPointsPayment payment(1, 150.0, &guest);  // Needs 15000
    bool result = payment.processPayment();
    
    EXPECT_FALSE(result);
    EXPECT_FALSE(payment.getIsProcessed());
    EXPECT_EQ(guest.getLoyaltyPoints(), 10000);  // Unchanged
}

TEST_F(LoyaltyPointsPaymentTest, ProcessPaymentNullGuest) {
    LoyaltyPointsPayment payment(1, 50.0, nullptr);
    bool result = payment.processPayment();
    
    EXPECT_FALSE(result);
}

TEST_F(LoyaltyPointsPaymentTest, RefundSuccess) {
    LoyaltyPointsPayment payment(1, 50.0, &guest);
    payment.processPayment();  // Guest now has 5000
    
    bool result = payment.refund();
    
    EXPECT_TRUE(result);
    EXPECT_FALSE(payment.getIsProcessed());
    EXPECT_EQ(guest.getLoyaltyPoints(), 10000);  // Points returned
}

TEST_F(LoyaltyPointsPaymentTest, PaymentType) {
    LoyaltyPointsPayment payment(1, 50.0, &guest);
    EXPECT_STREQ(payment.getPaymentType(), "Loyalty Points");
}

TEST_F(LoyaltyPointsPaymentTest, NoTransactionFee) {
    LoyaltyPointsPayment payment(1, 50.0, &guest);
    EXPECT_DOUBLE_EQ(payment.getTransactionFee(), 0.0);
}

// ============================================================================

// ============================================================================
// ROOM GUEST MANAGEMENT TESTS (All Room Types)
// Tests the guest management functionality implemented in derived classes
// ============================================================================

class RoomGuestManagementTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(RoomGuestManagementTest, StandardRoomCheckIn) {
    StandardRoom room(101, 1, 1, false);
    Guest guest(1, "Test Guest", "555-0000", "test@test.com");
    
    EXPECT_TRUE(room.isVacant());
    EXPECT_EQ(room.getCurrentGuest(), nullptr);
    
    bool result = room.checkIn(&guest);
    
    EXPECT_TRUE(result);
    EXPECT_FALSE(room.isVacant());
    EXPECT_EQ(room.getCurrentGuest(), &guest);
}

TEST_F(RoomGuestManagementTest, DeluxeRoomCheckIn) {
    DeluxeRoom room(201, 2, 1, false, "City");
    Guest guest(1, "Test Guest", "555-0000", "test@test.com");
    
    EXPECT_TRUE(room.isVacant());
    
    bool result = room.checkIn(&guest);
    
    EXPECT_TRUE(result);
    EXPECT_FALSE(room.isVacant());
    EXPECT_EQ(room.getCurrentGuest(), &guest);
}

TEST_F(RoomGuestManagementTest, SuiteCheckIn) {
    Suite room(301, 3, 1, 600, false, false);
    Guest guest(1, "Test Guest", "555-0000", "test@test.com");
    
    EXPECT_TRUE(room.isVacant());
    
    bool result = room.checkIn(&guest);
    
    EXPECT_TRUE(result);
    EXPECT_FALSE(room.isVacant());
    EXPECT_EQ(room.getCurrentGuest(), &guest);
}

TEST_F(RoomGuestManagementTest, CannotCheckInWhenOccupied) {
    StandardRoom room(101, 1, 1, false);
    Guest guest1(1, "Guest 1", "555-0001", "g1@test.com");
    Guest guest2(2, "Guest 2", "555-0002", "g2@test.com");
    
    room.checkIn(&guest1);
    bool result = room.checkIn(&guest2);
    
    EXPECT_FALSE(result);
    EXPECT_EQ(room.getCurrentGuest(), &guest1);
}

TEST_F(RoomGuestManagementTest, CannotCheckInNullGuest) {
    StandardRoom room(101, 1, 1, false);
    bool result = room.checkIn(nullptr);
    EXPECT_FALSE(result);
    EXPECT_TRUE(room.isVacant());
}

TEST_F(RoomGuestManagementTest, CheckOutReturnsGuest) {
    StandardRoom room(101, 1, 1, false);
    Guest guest(1, "Test Guest", "555-0000", "test@test.com");
    
    room.checkIn(&guest);
    Guest* checkedOut = room.checkOut();
    
    EXPECT_EQ(checkedOut, &guest);
    EXPECT_TRUE(room.isVacant());
    EXPECT_EQ(room.getCurrentGuest(), nullptr);
}

TEST_F(RoomGuestManagementTest, CheckOutWhenVacantReturnsNull) {
    StandardRoom room(101, 1, 1, false);
    Guest* result = room.checkOut();
    EXPECT_EQ(result, nullptr);
}

TEST_F(RoomGuestManagementTest, CheckInSetsGuestStatus) {
    StandardRoom room(101, 1, 1, false);
    Guest guest(1, "Test", "555-0000", "test@test.com");
    
    EXPECT_FALSE(guest.getIsCheckedIn());
    
    room.checkIn(&guest);
    
    EXPECT_TRUE(guest.getIsCheckedIn());
}

TEST_F(RoomGuestManagementTest, CheckOutClearsGuestStatus) {
    StandardRoom room(101, 1, 1, false);
    Guest guest(1, "Test", "555-0000", "test@test.com");
    
    room.checkIn(&guest);
    EXPECT_TRUE(guest.getIsCheckedIn());
    
    room.checkOut();
    EXPECT_FALSE(guest.getIsCheckedIn());
}

TEST_F(RoomGuestManagementTest, CheckInMarksRoomDirty) {
    StandardRoom room(101, 1, 1, false);
    Guest guest(1, "Test", "555-0000", "test@test.com");
    
    EXPECT_TRUE(room.getIsClean());
    
    room.checkIn(&guest);
    
    EXPECT_FALSE(room.getIsClean());
}

TEST_F(RoomGuestManagementTest, CannotCheckInDirtyRoom) {
    StandardRoom room(101, 1, 1, false);
    Guest guest(1, "Test", "555-0000", "test@test.com");
    
    room.setClean(false);
    
    bool result = room.checkIn(&guest);
    
    EXPECT_FALSE(result);
    EXPECT_TRUE(room.isVacant());
}

TEST_F(RoomGuestManagementTest, CannotCheckInRoomUnderMaintenance) {
    StandardRoom room(101, 1, 1, false);
    Guest guest(1, "Test", "555-0000", "test@test.com");
    
    room.setUnderMaintenance(true);
    
    bool result = room.checkIn(&guest);
    
    EXPECT_FALSE(result);
    EXPECT_TRUE(room.isVacant());
}

// ============================================================================
// INHERITANCE CONCEPT TESTS
// ============================================================================

class InheritanceTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(InheritanceTest, GuestInheritsPersonData) {
    Guest guest(100, "Alice Smith", "555-1234", "alice@test.com", 5000);
    
    // Can access Person base class methods
    EXPECT_EQ(guest.getId(), 100);
    EXPECT_STREQ(guest.getName(), "Alice Smith");
    EXPECT_STREQ(guest.getPhone(), "555-1234");
    EXPECT_STREQ(guest.getEmail(), "alice@test.com");
    
    // Also has Guest-specific data
    EXPECT_EQ(guest.getLoyaltyPoints(), 5000);
}

TEST_F(InheritanceTest, EmployeeInheritsPersonData) {
    Employee emp(200, "Bob Jones", "555-5678", "bob@test.com", "Manager", 25.0);
    
    // Can access Person base class methods
    EXPECT_EQ(emp.getId(), 200);
    EXPECT_STREQ(emp.getName(), "Bob Jones");
    
    // Also has Employee-specific data
    EXPECT_STREQ(emp.getPosition(), "Manager");
    EXPECT_DOUBLE_EQ(emp.getHourlyWage(), 25.0);
}

TEST_F(InheritanceTest, GuestCanModifyInheritedData) {
    Guest guest(1, "Original Name", "555-0000", "old@test.com", 0);
    
    guest.setName("New Name");
    guest.setEmail("new@test.com");
    
    EXPECT_STREQ(guest.getName(), "New Name");
    EXPECT_STREQ(guest.getEmail(), "new@test.com");
}

TEST_F(InheritanceTest, StandardRoomInheritsRoomData) {
    StandardRoom room(101, 1, 2, true);
    
    // Can access Room base class methods
    EXPECT_EQ(room.getRoomNumber(), 101);
    EXPECT_EQ(room.getFloor(), 1);
    EXPECT_TRUE(room.getIsClean());
    EXPECT_TRUE(room.isVacant());
    
    // Also has StandardRoom-specific data
    EXPECT_EQ(room.getNumBeds(), 2);
    EXPECT_TRUE(room.getHasWindow());
}

TEST_F(InheritanceTest, DeluxeRoomInheritsRoomData) {
    DeluxeRoom room(201, 2, 1, true, "Ocean");
    
    // Room base class functionality
    EXPECT_EQ(room.getRoomNumber(), 201);
    EXPECT_EQ(room.getFloor(), 2);
    
    // DeluxeRoom-specific
    EXPECT_TRUE(room.getHasBalcony());
    EXPECT_STREQ(room.getViewType(), "Ocean");
}

TEST_F(InheritanceTest, SuiteInheritsRoomData) {
    Suite suite(301, 3, 2, 800, true, true);
    
    // Room base class functionality
    EXPECT_EQ(suite.getRoomNumber(), 301);
    EXPECT_EQ(suite.getFloor(), 3);
    
    // Suite-specific
    EXPECT_EQ(suite.getNumBedrooms(), 2);
    EXPECT_TRUE(suite.getHasJacuzzi());
}

TEST_F(InheritanceTest, CashPaymentInheritsPaymentData) {
    CashPayment cash(1, 100.0, 120.0);
    
    // Payment base class functionality
    EXPECT_EQ(cash.getPaymentId(), 1);
    EXPECT_DOUBLE_EQ(cash.getAmount(), 100.0);
    EXPECT_FALSE(cash.getIsProcessed());
    
    // CashPayment-specific
    EXPECT_DOUBLE_EQ(cash.getAmountTendered(), 120.0);
}

TEST_F(InheritanceTest, CreditCardPaymentInheritsPaymentData) {
    CreditCardPayment card(2, 200.0, "1234", "Test User", "12/25");
    
    // Payment base class functionality
    EXPECT_EQ(card.getPaymentId(), 2);
    EXPECT_DOUBLE_EQ(card.getAmount(), 200.0);
    
    // CreditCardPayment-specific
    EXPECT_STREQ(card.getCardNumber(), "1234");
}

TEST_F(InheritanceTest, RoomTypesImplementPureVirtual) {
    StandardRoom standard(101, 1, 1, false);
    DeluxeRoom deluxe(201, 2, 1, false, "City");
    Suite suite(301, 3, 1, 600, false, false);
    
    EXPECT_STREQ(standard.getRoomType(), "Standard");
    EXPECT_STREQ(deluxe.getRoomType(), "Deluxe");
    EXPECT_STREQ(suite.getRoomType(), "Suite");
}

TEST_F(InheritanceTest, PaymentTypesImplementPureVirtual) {
    CashPayment cash(1, 100.0, 120.0);
    CreditCardPayment card(2, 100.0, "1234", "Test", "12/25");
    
    EXPECT_STREQ(cash.getPaymentType(), "Cash");
    EXPECT_STREQ(card.getPaymentType(), "Credit Card");
}

TEST_F(InheritanceTest, RoomCheckInWorksForAllTypes) {
    Guest guest(1, "Test", "555-0000", "test@test.com");
    
    StandardRoom sr(101, 1, 1, false);
    DeluxeRoom dr(201, 2, 1, false, "City");
    Suite suite(301, 3, 1, 600, false, false);
    
    // All room types inherit checkIn from Room base class
    EXPECT_TRUE(sr.checkIn(&guest));
    EXPECT_TRUE(dr.checkIn(&guest));
    EXPECT_TRUE(suite.checkIn(&guest));
}

TEST_F(InheritanceTest, DifferentRoomsPriceDifferently) {
    StandardRoom sr(101, 1, 1, false);
    DeluxeRoom dr(201, 2, 1, false, "City");
    Suite suite(301, 3, 1, 600, false, false);
    
    EXPECT_NEAR(sr.getBasePrice(), 89.0, 0.01);
    EXPECT_NEAR(dr.getBasePrice(), 149.0, 0.01);
    EXPECT_NEAR(suite.getBasePrice(), 299.0, 0.01);
}

TEST_F(InheritanceTest, PaymentFeesVaryByType) {
    CashPayment cash(1, 100.0, 120.0);
    CreditCardPayment card(2, 100.0, "1234", "Test", "12/25");
    
    EXPECT_DOUBLE_EQ(cash.getTransactionFee(), 0.0);
    EXPECT_NEAR(card.getTransactionFee(), 2.5, 0.01);
}
