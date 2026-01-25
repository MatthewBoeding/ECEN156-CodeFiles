#include <gtest/gtest.h>
#include "guest_management.h"
#include <cstring>

// ============================================================================
// WEEK 3 ASSIGNMENT: Guest Management System - Pointers
// 
// Implement the functions in guest_management.cpp to make all tests pass.
// This week focuses on working with POINTERS!
//
// DO NOT modify this test file!
// ============================================================================

// ============================================================================
// Test Fixtures
// ============================================================================

class GuestManagementTest : public ::testing::Test {
protected:
    Guest guests[5];
    Room rooms[4];
    
    void SetUp() override {
        // Initialize guests
        guests[0] = {1001, "Alice Johnson", "555-0101", "alice@email.com", 500, false};
        guests[1] = {1002, "Bob Smith", "555-0102", "bob@email.com", 1200, true};
        guests[2] = {1003, "Carol Davis", "555-0103", "carol@email.com", 300, false};
        guests[3] = {1004, "David Wilson", "555-0104", "david@email.com", 800, true};
        guests[4] = {1005, "Eve Brown", "555-0105", "eve@email.com", 1500, false};
        
        // Initialize rooms with nullptr guests
        rooms[0] = {101, "Single", 89.99, nullptr};
        rooms[1] = {102, "Single", 89.99, nullptr};
        rooms[2] = {201, "Double", 129.99, nullptr};
        rooms[3] = {301, "Suite", 249.99, nullptr};
    }
};

// ============================================================================
// Tests for findGuestById
// ============================================================================

TEST_F(GuestManagementTest, FindGuestByIdFound) {
    Guest* found = findGuestById(guests, 5, 1003);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->guestId, 1003);
    EXPECT_STREQ(found->name, "Carol Davis");
}

TEST_F(GuestManagementTest, FindGuestByIdNotFound) {
    Guest* found = findGuestById(guests, 5, 9999);
    EXPECT_EQ(found, nullptr);
}

TEST_F(GuestManagementTest, FindGuestByIdFirstElement) {
    Guest* found = findGuestById(guests, 5, 1001);
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(found->name, "Alice Johnson");
}

TEST_F(GuestManagementTest, FindGuestByIdLastElement) {
    Guest* found = findGuestById(guests, 5, 1005);
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(found->name, "Eve Brown");
}

TEST(FindGuestByIdTest, SingleGuest) {
    Guest g[] = {{1001, "Test Guest", "555-0000", "test@test.com", 100, false}};
    Guest* found = findGuestById(g, 1, 1001);
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(found->name, "Test Guest");
}

// ============================================================================
// Tests for findGuestByName
// ============================================================================

TEST_F(GuestManagementTest, FindGuestByNameFound) {
    Guest* found = findGuestByName(guests, 5, "Bob Smith");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->guestId, 1002);
}

TEST_F(GuestManagementTest, FindGuestByNameNotFound) {
    Guest* found = findGuestByName(guests, 5, "Nobody Here");
    EXPECT_EQ(found, nullptr);
}

TEST_F(GuestManagementTest, FindGuestByNameCaseSensitive) {
    Guest* found = findGuestByName(guests, 5, "bob smith");  // lowercase
    EXPECT_EQ(found, nullptr);  // Should not find (case-sensitive)
}

TEST_F(GuestManagementTest, FindGuestByNameFirstGuest) {
    Guest* found = findGuestByName(guests, 5, "Alice Johnson");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->guestId, 1001);
}

// ============================================================================
// Tests for countCheckedInGuests
// ============================================================================

TEST_F(GuestManagementTest, CountCheckedInGuests) {
    // Bob (1002) and David (1004) are checked in
    EXPECT_EQ(countCheckedInGuests(guests, 5), 2);
}

TEST(CountCheckedInTest, NoneCheckedIn) {
    Guest g[] = {
        {1, "A", "555", "a@a.com", 100, false},
        {2, "B", "555", "b@b.com", 200, false}
    };
    EXPECT_EQ(countCheckedInGuests(g, 2), 0);
}

TEST(CountCheckedInTest, AllCheckedIn) {
    Guest g[] = {
        {1, "A", "555", "a@a.com", 100, true},
        {2, "B", "555", "b@b.com", 200, true},
        {3, "C", "555", "c@c.com", 300, true}
    };
    EXPECT_EQ(countCheckedInGuests(g, 3), 3);
}

TEST(CountCheckedInTest, SingleGuestCheckedIn) {
    Guest g[] = {{1, "A", "555", "a@a.com", 100, true}};
    EXPECT_EQ(countCheckedInGuests(g, 1), 1);
}

// ============================================================================
// Tests for findTopLoyaltyMember
// ============================================================================

TEST_F(GuestManagementTest, FindTopLoyaltyMember) {
    Guest* top = findTopLoyaltyMember(guests, 5);
    ASSERT_NE(top, nullptr);
    EXPECT_EQ(top->guestId, 1005);  // Eve has 1500 points
    EXPECT_EQ(top->loyaltyPoints, 1500);
}

TEST(TopLoyaltyTest, SingleGuest) {
    Guest g[] = {{1, "Only Guest", "555", "only@test.com", 999, false}};
    Guest* top = findTopLoyaltyMember(g, 1);
    ASSERT_NE(top, nullptr);
    EXPECT_EQ(top->loyaltyPoints, 999);
}

TEST(TopLoyaltyTest, TieReturnsFirst) {
    Guest g[] = {
        {1, "First", "555", "first@test.com", 500, false},
        {2, "Second", "555", "second@test.com", 500, false}
    };
    Guest* top = findTopLoyaltyMember(g, 2);
    ASSERT_NE(top, nullptr);
    EXPECT_EQ(top->guestId, 1);  // First one when tied
}

TEST(TopLoyaltyTest, TopAtEnd) {
    Guest g[] = {
        {1, "Low", "555", "low@test.com", 100, false},
        {2, "Medium", "555", "med@test.com", 200, false},
        {3, "High", "555", "high@test.com", 999, false}
    };
    Guest* top = findTopLoyaltyMember(g, 3);
    ASSERT_NE(top, nullptr);
    EXPECT_EQ(top->guestId, 3);
}

// ============================================================================
// Tests for addLoyaltyPoints
// ============================================================================

TEST_F(GuestManagementTest, AddLoyaltyPointsSuccess) {
    EXPECT_TRUE(addLoyaltyPoints(guests, 5, 1001, 100));
    EXPECT_EQ(guests[0].loyaltyPoints, 600);  // Was 500, now 600
}

TEST_F(GuestManagementTest, AddLoyaltyPointsGuestNotFound) {
    EXPECT_FALSE(addLoyaltyPoints(guests, 5, 9999, 100));
}

TEST_F(GuestManagementTest, AddLoyaltyPointsZeroPoints) {
    EXPECT_TRUE(addLoyaltyPoints(guests, 5, 1002, 0));
    EXPECT_EQ(guests[1].loyaltyPoints, 1200);  // Unchanged
}

TEST_F(GuestManagementTest, AddLoyaltyPointsMultipleTimes) {
    addLoyaltyPoints(guests, 5, 1003, 50);
    addLoyaltyPoints(guests, 5, 1003, 50);
    EXPECT_EQ(guests[2].loyaltyPoints, 400);  // Was 300, added 50 twice
}

// ============================================================================
// Tests for updateGuestContact
// ============================================================================

TEST_F(GuestManagementTest, UpdateGuestContactBoth) {
    Guest* g = &guests[0];
    EXPECT_TRUE(updateGuestContact(g, "555-9999", "newemail@test.com"));
    EXPECT_STREQ(g->phone, "555-9999");
    EXPECT_STREQ(g->email, "newemail@test.com");
}

TEST_F(GuestManagementTest, UpdateGuestContactPhoneOnly) {
    Guest* g = &guests[0];
    EXPECT_TRUE(updateGuestContact(g, "555-9999", nullptr));
    EXPECT_STREQ(g->phone, "555-9999");
    EXPECT_STREQ(g->email, "alice@email.com");  // Unchanged
}

TEST_F(GuestManagementTest, UpdateGuestContactEmailOnly) {
    Guest* g = &guests[0];
    EXPECT_TRUE(updateGuestContact(g, nullptr, "newemail@test.com"));
    EXPECT_STREQ(g->phone, "555-0101");  // Unchanged
    EXPECT_STREQ(g->email, "newemail@test.com");
}

TEST_F(GuestManagementTest, UpdateGuestContactNullGuest) {
    EXPECT_FALSE(updateGuestContact(nullptr, "555-9999", "test@test.com"));
}

TEST_F(GuestManagementTest, UpdateGuestContactBothNull) {
    Guest* g = &guests[0];
    EXPECT_TRUE(updateGuestContact(g, nullptr, nullptr));  // Valid, just no-op
    EXPECT_STREQ(g->phone, "555-0101");  // Unchanged
    EXPECT_STREQ(g->email, "alice@email.com");  // Unchanged
}

// ============================================================================
// Tests for checkGuestIntoRoom
// ============================================================================

TEST_F(GuestManagementTest, CheckGuestIntoRoomSuccess) {
    EXPECT_TRUE(checkGuestIntoRoom(&rooms[0], &guests[0]));
    EXPECT_EQ(rooms[0].currentGuest, &guests[0]);
    EXPECT_TRUE(guests[0].isCheckedIn);
}

TEST_F(GuestManagementTest, CheckGuestIntoRoomAlreadyOccupied) {
    rooms[0].currentGuest = &guests[1];  // Room already has guest
    EXPECT_FALSE(checkGuestIntoRoom(&rooms[0], &guests[0]));
}

TEST_F(GuestManagementTest, CheckGuestIntoRoomNullRoom) {
    EXPECT_FALSE(checkGuestIntoRoom(nullptr, &guests[0]));
}

TEST_F(GuestManagementTest, CheckGuestIntoRoomNullGuest) {
    EXPECT_FALSE(checkGuestIntoRoom(&rooms[0], nullptr));
}

TEST_F(GuestManagementTest, CheckGuestIntoRoomBothNull) {
    EXPECT_FALSE(checkGuestIntoRoom(nullptr, nullptr));
}

// ============================================================================
// Tests for checkGuestOutOfRoom
// ============================================================================

TEST_F(GuestManagementTest, CheckGuestOutOfRoomSuccess) {
    rooms[0].currentGuest = &guests[0];
    guests[0].isCheckedIn = true;
    
    Guest* checkedOut = checkGuestOutOfRoom(&rooms[0]);
    
    EXPECT_EQ(checkedOut, &guests[0]);
    EXPECT_EQ(rooms[0].currentGuest, nullptr);
    EXPECT_FALSE(guests[0].isCheckedIn);
}

TEST_F(GuestManagementTest, CheckGuestOutOfRoomVacant) {
    Guest* checkedOut = checkGuestOutOfRoom(&rooms[0]);
    EXPECT_EQ(checkedOut, nullptr);
}

TEST_F(GuestManagementTest, CheckGuestOutOfRoomNullRoom) {
    Guest* checkedOut = checkGuestOutOfRoom(nullptr);
    EXPECT_EQ(checkedOut, nullptr);
}

// ============================================================================
// Tests for findGuestRoom
// ============================================================================

TEST_F(GuestManagementTest, FindGuestRoomFound) {
    rooms[2].currentGuest = &guests[0];
    
    Room* found = findGuestRoom(rooms, 4, &guests[0]);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->roomNumber, 201);
}

TEST_F(GuestManagementTest, FindGuestRoomNotFound) {
    Room* found = findGuestRoom(rooms, 4, &guests[0]);
    EXPECT_EQ(found, nullptr);
}

TEST_F(GuestManagementTest, FindGuestRoomNullGuest) {
    Room* found = findGuestRoom(rooms, 4, nullptr);
    EXPECT_EQ(found, nullptr);
}

// ============================================================================
// Tests for countOccupiedRooms
// ============================================================================

TEST_F(GuestManagementTest, CountOccupiedRoomsNone) {
    EXPECT_EQ(countOccupiedRooms(rooms, 4), 0);
}

TEST_F(GuestManagementTest, CountOccupiedRoomsSome) {
    rooms[0].currentGuest = &guests[0];
    rooms[2].currentGuest = &guests[1];
    EXPECT_EQ(countOccupiedRooms(rooms, 4), 2);
}

TEST_F(GuestManagementTest, CountOccupiedRoomsAll) {
    rooms[0].currentGuest = &guests[0];
    rooms[1].currentGuest = &guests[1];
    rooms[2].currentGuest = &guests[2];
    rooms[3].currentGuest = &guests[3];
    EXPECT_EQ(countOccupiedRooms(rooms, 4), 4);
}

// ============================================================================
// Tests for getVacantRooms
// ============================================================================

TEST_F(GuestManagementTest, GetVacantRoomsAll) {
    Room* vacant[4];
    int count = getVacantRooms(rooms, 4, vacant);
    EXPECT_EQ(count, 4);
}

TEST_F(GuestManagementTest, GetVacantRoomsSome) {
    rooms[0].currentGuest = &guests[0];
    rooms[2].currentGuest = &guests[1];
    
    Room* vacant[4];
    int count = getVacantRooms(rooms, 4, vacant);
    
    EXPECT_EQ(count, 2);
    // Verify the vacant rooms are 102 and 301
    bool found102 = false, found301 = false;
    for (int i = 0; i < count; i++) {
        if (vacant[i]->roomNumber == 102) found102 = true;
        if (vacant[i]->roomNumber == 301) found301 = true;
    }
    EXPECT_TRUE(found102);
    EXPECT_TRUE(found301);
}

TEST_F(GuestManagementTest, GetVacantRoomsNone) {
    rooms[0].currentGuest = &guests[0];
    rooms[1].currentGuest = &guests[1];
    rooms[2].currentGuest = &guests[2];
    rooms[3].currentGuest = &guests[3];
    
    Room* vacant[4];
    int count = getVacantRooms(rooms, 4, vacant);
    EXPECT_EQ(count, 0);
}

// ============================================================================
// Tests for createReservation
// ============================================================================

TEST_F(GuestManagementTest, CreateReservationSuccess) {
    Reservation res;
    EXPECT_TRUE(createReservation(&res, 5001, &guests[0], &rooms[0], 3));
    
    EXPECT_EQ(res.reservationId, 5001);
    EXPECT_EQ(res.guest, &guests[0]);
    EXPECT_EQ(res.room, &rooms[0]);
    EXPECT_EQ(res.nights, 3);
    EXPECT_TRUE(res.isActive);
}

TEST_F(GuestManagementTest, CreateReservationNullReservation) {
    EXPECT_FALSE(createReservation(nullptr, 5001, &guests[0], &rooms[0], 3));
}

TEST_F(GuestManagementTest, CreateReservationNullGuest) {
    Reservation res;
    EXPECT_FALSE(createReservation(&res, 5001, nullptr, &rooms[0], 3));
}

TEST_F(GuestManagementTest, CreateReservationNullRoom) {
    Reservation res;
    EXPECT_FALSE(createReservation(&res, 5001, &guests[0], nullptr, 3));
}

// ============================================================================
// Tests for calculateReservationCost
// ============================================================================

TEST_F(GuestManagementTest, CalculateReservationCostValid) {
    Reservation res = {5001, &guests[0], &rooms[2], 3, true};  // Double room, 3 nights
    double cost = calculateReservationCost(&res);
    EXPECT_NEAR(cost, 389.97, 0.01);  // 129.99 * 3
}

TEST_F(GuestManagementTest, CalculateReservationCostSingleNight) {
    Reservation res = {5001, &guests[0], &rooms[0], 1, true};  // Single room, 1 night
    double cost = calculateReservationCost(&res);
    EXPECT_NEAR(cost, 89.99, 0.01);
}

TEST_F(GuestManagementTest, CalculateReservationCostNullReservation) {
    EXPECT_DOUBLE_EQ(calculateReservationCost(nullptr), 0.0);
}

TEST_F(GuestManagementTest, CalculateReservationCostNullRoom) {
    Reservation res = {5001, &guests[0], nullptr, 3, true};
    EXPECT_DOUBLE_EQ(calculateReservationCost(&res), 0.0);
}

// ============================================================================
// Tests for findGuestReservations
// ============================================================================

TEST_F(GuestManagementTest, FindGuestReservationsFound) {
    Reservation reservations[] = {
        {5001, &guests[0], &rooms[0], 2, true},
        {5002, &guests[1], &rooms[1], 3, true},
        {5003, &guests[0], &rooms[2], 1, true},  // Same guest as 5001
        {5004, &guests[2], &rooms[3], 2, true}
    };
    
    Reservation* found[4];
    int count = findGuestReservations(reservations, 4, &guests[0], found);
    
    EXPECT_EQ(count, 2);
}

TEST_F(GuestManagementTest, FindGuestReservationsNone) {
    Reservation reservations[] = {
        {5001, &guests[0], &rooms[0], 2, true},
        {5002, &guests[1], &rooms[1], 3, true}
    };
    
    Reservation* found[4];
    int count = findGuestReservations(reservations, 2, &guests[4], found);
    
    EXPECT_EQ(count, 0);
}

TEST_F(GuestManagementTest, FindGuestReservationsOnlyActive) {
    Reservation reservations[] = {
        {5001, &guests[0], &rooms[0], 2, true},
        {5002, &guests[0], &rooms[1], 3, false},  // Inactive
        {5003, &guests[0], &rooms[2], 1, true}
    };
    
    Reservation* found[4];
    int count = findGuestReservations(reservations, 3, &guests[0], found);
    
    EXPECT_EQ(count, 2);  // Only active ones
}

// ============================================================================
// Tests for calculateTotalRevenue
// ============================================================================

TEST_F(GuestManagementTest, CalculateTotalRevenueAllActive) {
    Reservation reservations[] = {
        {5001, &guests[0], &rooms[0], 2, true},   // 89.99 * 2 = 179.98
        {5002, &guests[1], &rooms[2], 3, true}    // 129.99 * 3 = 389.97
    };
    
    double revenue = calculateTotalRevenue(reservations, 2);
    EXPECT_NEAR(revenue, 569.95, 0.01);
}

TEST_F(GuestManagementTest, CalculateTotalRevenueWithInactive) {
    Reservation reservations[] = {
        {5001, &guests[0], &rooms[0], 2, true},   // 89.99 * 2 = 179.98
        {5002, &guests[1], &rooms[2], 3, false},  // Inactive - don't count
        {5003, &guests[2], &rooms[3], 1, true}    // 249.99 * 1 = 249.99
    };
    
    double revenue = calculateTotalRevenue(reservations, 3);
    EXPECT_NEAR(revenue, 429.97, 0.01);
}

TEST_F(GuestManagementTest, CalculateTotalRevenueEmpty) {
    Reservation reservations[] = {};
    double revenue = calculateTotalRevenue(reservations, 0);
    EXPECT_DOUBLE_EQ(revenue, 0.0);
}

// ============================================================================
// Tests for cancelReservation
// ============================================================================

TEST_F(GuestManagementTest, CancelReservationSuccess) {
    Reservation res = {5001, &guests[0], &rooms[0], 2, true};
    EXPECT_TRUE(cancelReservation(&res));
    EXPECT_FALSE(res.isActive);
}

TEST_F(GuestManagementTest, CancelReservationAlreadyInactive) {
    Reservation res = {5001, &guests[0], &rooms[0], 2, false};
    EXPECT_FALSE(cancelReservation(&res));
}

TEST_F(GuestManagementTest, CancelReservationNull) {
    EXPECT_FALSE(cancelReservation(nullptr));
}

// ============================================================================
// Tests for swapGuestPointers
// ============================================================================

TEST_F(GuestManagementTest, SwapGuestPointers) {
    Guest* p1 = &guests[0];
    Guest* p2 = &guests[1];
    
    swapGuestPointers(&p1, &p2);
    
    EXPECT_EQ(p1, &guests[1]);
    EXPECT_EQ(p2, &guests[0]);
}

TEST_F(GuestManagementTest, SwapGuestPointersSamePointer) {
    Guest* p1 = &guests[0];
    Guest* p2 = &guests[0];
    
    swapGuestPointers(&p1, &p2);
    
    EXPECT_EQ(p1, &guests[0]);
    EXPECT_EQ(p2, &guests[0]);
}

// ============================================================================
// Tests for sortGuestsByLoyalty
// ============================================================================

TEST_F(GuestManagementTest, SortGuestsByLoyaltyDescending) {
    Guest* ptrs[] = {&guests[0], &guests[1], &guests[2], &guests[3], &guests[4]};
    // Points: 500, 1200, 300, 800, 1500
    
    sortGuestsByLoyalty(ptrs, 5);
    
    // Should be sorted descending: 1500, 1200, 800, 500, 300
    EXPECT_EQ(ptrs[0]->loyaltyPoints, 1500);
    EXPECT_EQ(ptrs[1]->loyaltyPoints, 1200);
    EXPECT_EQ(ptrs[2]->loyaltyPoints, 800);
    EXPECT_EQ(ptrs[3]->loyaltyPoints, 500);
    EXPECT_EQ(ptrs[4]->loyaltyPoints, 300);
}

TEST_F(GuestManagementTest, SortGuestsByLoyaltyAlreadySorted) {
    Guest sorted[] = {
        {1, "A", "555", "a@a.com", 500, false},
        {2, "B", "555", "b@b.com", 300, false},
        {3, "C", "555", "c@c.com", 100, false}
    };
    Guest* ptrs[] = {&sorted[0], &sorted[1], &sorted[2]};
    
    sortGuestsByLoyalty(ptrs, 3);
    
    EXPECT_EQ(ptrs[0]->loyaltyPoints, 500);
    EXPECT_EQ(ptrs[1]->loyaltyPoints, 300);
    EXPECT_EQ(ptrs[2]->loyaltyPoints, 100);
}

TEST_F(GuestManagementTest, SortGuestsByLoyaltySingleElement) {
    Guest* ptrs[] = {&guests[0]};
    sortGuestsByLoyalty(ptrs, 1);
    EXPECT_EQ(ptrs[0]->loyaltyPoints, 500);
}

// ============================================================================
// Tests for findGuestsInPointsRange
// ============================================================================

TEST_F(GuestManagementTest, FindGuestsInPointsRangeFound) {
    Guest* result[5];
    // Points: 500, 1200, 300, 800, 1500
    int count = findGuestsInPointsRange(guests, 5, 400, 1000, result);
    
    EXPECT_EQ(count, 2);  // 500 and 800 are in range
}

TEST_F(GuestManagementTest, FindGuestsInPointsRangeNone) {
    Guest* result[5];
    int count = findGuestsInPointsRange(guests, 5, 2000, 3000, result);
    
    EXPECT_EQ(count, 0);
}

TEST_F(GuestManagementTest, FindGuestsInPointsRangeAll) {
    Guest* result[5];
    int count = findGuestsInPointsRange(guests, 5, 0, 10000, result);
    
    EXPECT_EQ(count, 5);
}

TEST_F(GuestManagementTest, FindGuestsInPointsRangeExactMatch) {
    Guest* result[5];
    int count = findGuestsInPointsRange(guests, 5, 500, 500, result);
    
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result[0]->loyaltyPoints, 500);
}

TEST_F(GuestManagementTest, FindGuestsInPointsRangeInclusive) {
    Guest* result[5];
    // Points: 500, 1200, 300, 800, 1500
    int count = findGuestsInPointsRange(guests, 5, 300, 800, result);
    
    EXPECT_EQ(count, 3);  // 300, 500, and 800 (inclusive)
}
