#include <gtest/gtest.h>
#include "hotel_management.h"
#include <cmath>

// ============================================================================
// ASSIGNMENT: Implement the functions in hotel_management.cpp to make all 
// tests pass. You are building a HOTEL MANAGEMENT SYSTEM!
//
// DO NOT modify this test file!
// ============================================================================

// Test fixture with sample hotel data
class HotelManagementTest : public ::testing::Test {
protected:
    Room rooms[6];
    
    void SetUp() override {
        rooms[0] = {101, "Single", 89.99, false};
        rooms[1] = {102, "Single", 89.99, true};
        rooms[2] = {201, "Double", 129.99, false};
        rooms[3] = {202, "Double", 129.99, false};
        rooms[4] = {301, "Suite", 249.99, true};
        rooms[5] = {302, "Suite", 249.99, false};
    }
};

// ----------------------------------------------------------------------------
// Tests for calculateAveragePrice
// ----------------------------------------------------------------------------
TEST_F(HotelManagementTest, CalculatesAverageRoomPrice) {
    double avg = calculateAveragePrice(rooms, 6);
    // (89.99*2 + 129.99*2 + 249.99*2) / 6 = 156.65
    EXPECT_NEAR(avg, 156.65, 0.01);
}

TEST(AveragePriceTest, SingleRoom) {
    Room r[] = {{101, "Single", 99.99, false}};
    EXPECT_DOUBLE_EQ(calculateAveragePrice(r, 1), 99.99);
}

TEST(AveragePriceTest, AllSame) {
    Room r[] = {
        {101, "Single", 100.00, false},
        {102, "Single", 100.00, false},
        {103, "Single", 100.00, false}
    };
    EXPECT_DOUBLE_EQ(calculateAveragePrice(r, 3), 100.00);
}

TEST(AveragePriceTest, MixedRooms) {
    Room r[] = {
        {101, "Single", 80.00, false},
        {201, "Suite", 200.00, false}
    };
    EXPECT_DOUBLE_EQ(calculateAveragePrice(r, 2), 140.00);
}

// ----------------------------------------------------------------------------
// Tests for findMostExpensiveRoom
// ----------------------------------------------------------------------------
TEST_F(HotelManagementTest, FindsMostExpensiveRoom) {
    Room expensive = findMostExpensiveRoom(rooms, 6);
    EXPECT_EQ(expensive.roomNumber, 301);  // One of the suites
    EXPECT_DOUBLE_EQ(expensive.pricePerNight, 249.99);
}

TEST(MostExpensiveTest, SingleRoom) {
    Room r[] = {{101, "Single", 89.99, false}};
    Room expensive = findMostExpensiveRoom(r, 1);
    EXPECT_EQ(expensive.roomNumber, 101);
}

TEST(MostExpensiveTest, FirstRoom) {
    Room r[] = {
        {101, "Suite", 300.00, false},
        {102, "Single", 80.00, false},
        {103, "Double", 120.00, false}
    };
    Room expensive = findMostExpensiveRoom(r, 3);
    EXPECT_EQ(expensive.roomNumber, 101);
}

TEST(MostExpensiveTest, LastRoom) {
    Room r[] = {
        {101, "Single", 80.00, false},
        {102, "Double", 120.00, false},
        {103, "Suite", 300.00, false}
    };
    Room expensive = findMostExpensiveRoom(r, 3);
    EXPECT_EQ(expensive.roomNumber, 103);
}

TEST(MostExpensiveTest, TieReturnsFirst) {
    Room r[] = {
        {101, "Suite", 250.00, false},
        {102, "Suite", 250.00, false},
        {103, "Double", 120.00, false}
    };
    Room expensive = findMostExpensiveRoom(r, 3);
    EXPECT_EQ(expensive.roomNumber, 101);  // Returns first when tied
}

// ----------------------------------------------------------------------------
// Tests for countOccupiedRooms
// ----------------------------------------------------------------------------
TEST_F(HotelManagementTest, CountsOccupiedRooms) {
    EXPECT_EQ(countOccupiedRooms(rooms, 6), 2);  // Rooms 102 and 301
}

TEST(CountOccupiedTest, NoneOccupied) {
    Room r[] = {
        {101, "Single", 89.99, false},
        {102, "Double", 129.99, false}
    };
    EXPECT_EQ(countOccupiedRooms(r, 2), 0);
}

TEST(CountOccupiedTest, AllOccupied) {
    Room r[] = {
        {101, "Single", 89.99, true},
        {102, "Double", 129.99, true},
        {103, "Suite", 249.99, true}
    };
    EXPECT_EQ(countOccupiedRooms(r, 3), 3);
}

TEST(CountOccupiedTest, SingleRoom) {
    Room r[] = {{101, "Single", 89.99, true}};
    EXPECT_EQ(countOccupiedRooms(r, 1), 1);
}

// ----------------------------------------------------------------------------
// Tests for findRoomByNumber
// ----------------------------------------------------------------------------
TEST_F(HotelManagementTest, FindsRoomByNumber) {
    Room* found = findRoomByNumber(rooms, 6, 201);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->roomNumber, 201);
    EXPECT_STREQ(found->type, "Double");
}

TEST_F(HotelManagementTest, FindRoomByNumberNotFound) {
    Room* found = findRoomByNumber(rooms, 6, 999);
    EXPECT_EQ(found, nullptr);
}

TEST_F(HotelManagementTest, FindRoomByNumberFirstRoom) {
    Room* found = findRoomByNumber(rooms, 6, 101);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->roomNumber, 101);
}

TEST_F(HotelManagementTest, FindRoomByNumberLastRoom) {
    Room* found = findRoomByNumber(rooms, 6, 302);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->roomNumber, 302);
}

TEST(FindRoomTest, SingleRoom) {
    Room r[] = {{101, "Single", 89.99, false}};
    Room* found = findRoomByNumber(r, 1, 101);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->roomNumber, 101);
}

// ----------------------------------------------------------------------------
// Tests for countRoomsByType
// ----------------------------------------------------------------------------
TEST_F(HotelManagementTest, CountsRoomsByType) {
    EXPECT_EQ(countRoomsByType(rooms, 6, "Single"), 2);
    EXPECT_EQ(countRoomsByType(rooms, 6, "Double"), 2);
    EXPECT_EQ(countRoomsByType(rooms, 6, "Suite"), 2);
}

TEST_F(HotelManagementTest, CountRoomsByTypeNoneFound) {
    EXPECT_EQ(countRoomsByType(rooms, 6, "Penthouse"), 0);
}

TEST(CountRoomsByTypeTest, TypeAllSameType) {
    Room r[] = {
        {101, "Single", 89.99, false},
        {102, "Single", 89.99, false},
        {103, "Single", 89.99, false}
    };
    EXPECT_EQ(countRoomsByType(r, 3, "Single"), 3);
}

TEST(CountRoomsByTypeTest, TypeCaseSensitive) {
    Room r[] = {
        {101, "Single", 89.99, false},
        {102, "single", 89.99, false}  // lowercase
    };
    EXPECT_EQ(countRoomsByType(r, 2, "Single"), 1);  // Case-sensitive
}

TEST(CountRoomsByTypeTest, TypeSingleRoom) {
    Room r[] = {{101, "Suite", 249.99, false}};
    EXPECT_EQ(countRoomsByType(r, 1, "Suite"), 1);
}

// ----------------------------------------------------------------------------
// Tests for getAvailableRooms
// ----------------------------------------------------------------------------
TEST_F(HotelManagementTest, GetsAvailableRooms) {
    Room available[6];
    int count = getAvailableRooms(rooms, 6, available);
    EXPECT_EQ(count, 4);  // Rooms 101, 201, 202, 302 are available
    
    // Verify all returned rooms are not occupied
    for (int i = 0; i < count; i++) {
        EXPECT_FALSE(available[i].isOccupied);
    }
}

TEST(AvailableRoomsTest, NoneAvailable) {
    Room r[] = {
        {101, "Single", 89.99, true},
        {102, "Double", 129.99, true}
    };
    Room available[2];
    int count = getAvailableRooms(r, 2, available);
    EXPECT_EQ(count, 0);
}

TEST(AvailableRoomsTest, AllAvailable) {
    Room r[] = {
        {101, "Single", 89.99, false},
        {102, "Double", 129.99, false},
        {103, "Suite", 249.99, false}
    };
    Room available[3];
    int count = getAvailableRooms(r, 3, available);
    EXPECT_EQ(count, 3);
}

TEST(AvailableRoomsTest, SingleRoom) {
    Room r[] = {{101, "Single", 89.99, false}};
    Room available[1];
    int count = getAvailableRooms(r, 1, available);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(available[0].roomNumber, 101);
}

// ----------------------------------------------------------------------------
// Tests for checkInRoom
// ----------------------------------------------------------------------------
TEST_F(HotelManagementTest, CheckInRoomSuccessfully) {
    bool success = checkInRoom(rooms, 6, 101);
    EXPECT_TRUE(success);
    EXPECT_TRUE(rooms[0].isOccupied);
}

TEST_F(HotelManagementTest, CheckInRoomAlreadyOccupied) {
    bool success = checkInRoom(rooms, 6, 102);  // Already occupied
    EXPECT_FALSE(success);
}

TEST_F(HotelManagementTest, CheckInRoomNotFound) {
    bool success = checkInRoom(rooms, 6, 999);
    EXPECT_FALSE(success);
}

TEST(CheckInTest, RoomFirstRoom) {
    Room r[] = {{101, "Single", 89.99, false}};
    bool success = checkInRoom(r, 1, 101);
    EXPECT_TRUE(success);
    EXPECT_TRUE(r[0].isOccupied);
}

TEST(CheckInTest, RoomLastRoom) {
    Room r[] = {
        {101, "Single", 89.99, false},
        {102, "Double", 129.99, false},
        {103, "Suite", 249.99, false}
    };
    bool success = checkInRoom(r, 3, 103);
    EXPECT_TRUE(success);
    EXPECT_TRUE(r[2].isOccupied);
}

// ----------------------------------------------------------------------------
// Tests for checkOutRoom
// ----------------------------------------------------------------------------
TEST_F(HotelManagementTest, CheckOutRoomSuccessfully) {
    bool success = checkOutRoom(rooms, 6, 102);  // Currently occupied
    EXPECT_TRUE(success);
    EXPECT_FALSE(rooms[1].isOccupied);
}

TEST_F(HotelManagementTest, CheckOutRoomAlreadyAvailable) {
    bool success = checkOutRoom(rooms, 6, 101);  // Already available
    EXPECT_FALSE(success);
}

TEST_F(HotelManagementTest, CheckOutRoomNotFound) {
    bool success = checkOutRoom(rooms, 6, 999);
    EXPECT_FALSE(success);
}

TEST(CheckOutTest, RoomFirstRoom) {
    Room r[] = {{101, "Single", 89.99, true}};
    bool success = checkOutRoom(r, 1, 101);
    EXPECT_TRUE(success);
    EXPECT_FALSE(r[0].isOccupied);
}

TEST(CheckOutTest, RoomLastRoom) {
    Room r[] = {
        {101, "Single", 89.99, false},
        {102, "Double", 129.99, false},
        {103, "Suite", 249.99, true}
    };
    bool success = checkOutRoom(r, 3, 103);
    EXPECT_TRUE(success);
    EXPECT_FALSE(r[2].isOccupied);
}

// ----------------------------------------------------------------------------
// Tests for calculateReservationCost
// ----------------------------------------------------------------------------
TEST(ReservationCostTest, CalculatesReservationCostSingleNight) {
    Room r = {101, "Single", 89.99, false};
    EXPECT_DOUBLE_EQ(calculateReservationCost(r, 1), 89.99);
}

TEST(ReservationCostTest, CalculatesReservationCostMultipleNights) {
    Room r = {201, "Double", 129.99, false};
    EXPECT_NEAR(calculateReservationCost(r, 3), 389.97, 0.01);
}

TEST(ReservationCostTest, CalculatesReservationCostWeekStay) {
    Room r = {301, "Suite", 250.00, false};
    EXPECT_DOUBLE_EQ(calculateReservationCost(r, 7), 1750.00);
}

TEST(ReservationCostTest, CalculatesReservationCostExpensiveSuite) {
    Room r = {401, "Penthouse", 500.00, false};
    EXPECT_DOUBLE_EQ(calculateReservationCost(r, 5), 2500.00);
}

// ----------------------------------------------------------------------------
// Tests for calculateTotalRevenue
// ----------------------------------------------------------------------------
TEST(TotalRevenueTest, CalculatesTotalRevenue) {
    Room rooms[] = {
        {101, "Single", 100.00, false},
        {102, "Double", 150.00, false},
        {103, "Suite", 250.00, false}
    };
    
    Reservation reservations[] = {
        {1, 101, 1001, 2},  // 2 nights in room 101 = $200
        {2, 102, 1002, 3},  // 3 nights in room 102 = $450
        {3, 103, 1003, 1}   // 1 night in room 103 = $250
    };
    
    double revenue = calculateTotalRevenue(reservations, 3, rooms, 3);
    EXPECT_DOUBLE_EQ(revenue, 900.00);  // 200 + 450 + 250
}

TEST(TotalRevenueTest, SingleReservation) {
    Room rooms[] = {{101, "Single", 89.99, false}};
    Reservation reservations[] = {{1, 101, 1001, 3}};
    
    double revenue = calculateTotalRevenue(reservations, 1, rooms, 1);
    EXPECT_NEAR(revenue, 269.97, 0.01);
}

TEST(TotalRevenueTest, NoReservations) {
    Room rooms[] = {{101, "Single", 89.99, false}};
    Reservation reservations[] = {};
    
    double revenue = calculateTotalRevenue(reservations, 0, rooms, 1);
    EXPECT_DOUBLE_EQ(revenue, 0.00);
}

TEST(TotalRevenueTest, MultipleReservations) {
    Room rooms[] = {
        {101, "Single", 80.00, false},
        {102, "Double", 120.00, false}
    };
    
    Reservation reservations[] = {
        {1, 101, 1001, 1},  // $80
        {2, 101, 1002, 2},  // $160
        {3, 102, 1003, 1},  // $120
        {4, 102, 1004, 3}   // $360
    };
    
    double revenue = calculateTotalRevenue(reservations, 4, rooms, 2);
    EXPECT_DOUBLE_EQ(revenue, 720.00);
}