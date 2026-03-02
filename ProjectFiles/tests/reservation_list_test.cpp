// ============================================================================
// Hotel Management System - Reservation Linked List Test Suite
// Tests for: ReservationNode (doubly linked list node)
//            ReservationList (doubly linked list operations)
//            Integration with Hotel and polymorphic Room*/Payment* pointers
//
// Build: g++ -std=c++17 base_classes.cpp hotel_classes.cpp system_classes.cpp reservation_list_test.cpp -lgtest -lgtest_main -pthread -o reservation_list_test
// Run: ./reservation_list_test
// ============================================================================

#include <gtest/gtest.h>
#include <cstring>
#include <cmath>
#include "system_classes.h"  // Includes hotel_classes.h and base_classes.h
#include "reservation_list.h"

// Helper for floating point comparison
#define EXPECT_NEAR_PRICE(val1, val2) EXPECT_NEAR(val1, val2, 0.01)

// ============================================================================
// RESERVATION NODE TESTS
// Tests the struct/node that makes up each element of the list
// ============================================================================

TEST(ReservationNodeTest, DefaultConstructor) {
    ReservationNode node;
    EXPECT_EQ(node.reservation, nullptr);
    EXPECT_EQ(node.next, nullptr);
    EXPECT_EQ(node.prev, nullptr);
}

TEST(ReservationNodeTest, ParameterizedConstructor) {
    Guest guest(1, "Test Guest", "555-0000", "test@test.com", 1000);
    StandardRoom room(101, 1, 1, true);
    Reservation* res = new Reservation(1001, &guest, &room, 3, "2024-06-01");

    ReservationNode node(res);

    EXPECT_EQ(node.reservation, res);
    EXPECT_EQ(node.next, nullptr);
    EXPECT_EQ(node.prev, nullptr);

    delete res;
}

TEST(ReservationNodeTest, LinksAreIndependent) {
    // Two nodes should not share prev/next pointers
    Guest guest(1, "Test Guest", "555-0000", "test@test.com", 0);
    StandardRoom room(101, 1, 1, true);
    Reservation* r1 = new Reservation(1001, &guest, &room, 2, "2024-06-01");
    Reservation* r2 = new Reservation(1002, &guest, &room, 3, "2024-06-05");

    ReservationNode n1(r1);
    ReservationNode n2(r2);

    n1.next = &n2;
    n2.prev = &n1;

    EXPECT_EQ(n1.next, &n2);
    EXPECT_EQ(n2.prev, &n1);
    EXPECT_EQ(n1.prev, nullptr);
    EXPECT_EQ(n2.next, nullptr);

    delete r1;
    delete r2;
}

// ============================================================================
// RESERVATION LIST - CONSTRUCTION & BASIC STATE
// ============================================================================

class ReservationListTest : public ::testing::Test {
protected:
    ReservationList* list;

    // Reusable guests and rooms
    Guest* goldGuest;
    Guest* bronzeGuest;
    StandardRoom* room101;
    StandardRoom* room102;
    DeluxeRoom* room201;

    void SetUp() override {
        list        = new ReservationList();
        goldGuest   = new Guest(1, "Gold Guest",   "555-1111", "gold@test.com",   7000);
        bronzeGuest = new Guest(2, "Bronze Guest", "555-2222", "bronze@test.com",  200);
        room101     = new StandardRoom(101, 1, 1, false);   // $89/night
        room102     = new StandardRoom(102, 1, 2, true);    // $89/night
        room201     = new DeluxeRoom  (201, 2, 1, true, "Ocean");  // $149/night
    }

    void TearDown() override {
        delete list;
        delete goldGuest;
        delete bronzeGuest;
        delete room101;
        delete room102;
        delete room201;
    }
};

TEST_F(ReservationListTest, DefaultConstructor) {
    EXPECT_EQ(list->getSize(), 0);
    EXPECT_EQ(list->getHead(), nullptr);
    EXPECT_EQ(list->getTail(), nullptr);
    EXPECT_TRUE(list->isEmpty());
}

// ============================================================================
// RESERVATION LIST - INSERTION
// ============================================================================

TEST_F(ReservationListTest, InsertFirstReservation) {
    Reservation* res = new Reservation(1001, goldGuest, room101, 3, "2024-06-01");
    list->insert(res);

    EXPECT_EQ(list->getSize(), 1);
    EXPECT_FALSE(list->isEmpty());
    EXPECT_NE(list->getHead(), nullptr);
    EXPECT_NE(list->getTail(), nullptr);
    // Single element: head and tail should be the same node
    EXPECT_EQ(list->getHead(), list->getTail());
}

TEST_F(ReservationListTest, InsertSetsHeadReservation) {
    Reservation* res = new Reservation(1001, goldGuest, room101, 3, "2024-06-01");
    list->insert(res);

    EXPECT_EQ(list->getHead()->reservation, res);
}

TEST_F(ReservationListTest, InsertMultipleReservations) {
    Reservation* r1 = new Reservation(1001, goldGuest,   room101, 3, "2024-06-01");
    Reservation* r2 = new Reservation(1002, bronzeGuest, room102, 2, "2024-06-05");
    Reservation* r3 = new Reservation(1003, goldGuest,   room201, 5, "2024-06-10");

    list->insert(r1);
    list->insert(r2);
    list->insert(r3);

    EXPECT_EQ(list->getSize(), 3);
}

TEST_F(ReservationListTest, InsertMaintainsTailPointer) {
    Reservation* r1 = new Reservation(1001, goldGuest,   room101, 3, "2024-06-01");
    Reservation* r2 = new Reservation(1002, bronzeGuest, room102, 2, "2024-06-05");

    list->insert(r1);
    list->insert(r2);

    // Tail should point to most recently inserted reservation
    EXPECT_EQ(list->getTail()->reservation, r2);
}

TEST_F(ReservationListTest, InsertMaintainsDoublyLinkedPointers) {
    Reservation* r1 = new Reservation(1001, goldGuest,   room101, 3, "2024-06-01");
    Reservation* r2 = new Reservation(1002, bronzeGuest, room201, 2, "2024-06-05");

    list->insert(r1);
    list->insert(r2);

    ReservationNode* head = list->getHead();
    ReservationNode* tail = list->getTail();

    // Forward link: head -> tail
    EXPECT_EQ(head->next, tail);
    // Backward link: tail -> head
    EXPECT_EQ(tail->prev, head);
    // Sentinels
    EXPECT_EQ(head->prev, nullptr);
    EXPECT_EQ(tail->next, nullptr);
}

TEST_F(ReservationListTest, InsertNullDoesNothing) {
    list->insert(nullptr);

    EXPECT_EQ(list->getSize(), 0);
    EXPECT_TRUE(list->isEmpty());
}

// ============================================================================
// RESERVATION LIST - SEARCH / FIND
// ============================================================================

TEST_F(ReservationListTest, FindByIdReturnsCorrectReservation) {
    Reservation* r1 = new Reservation(1001, goldGuest,   room101, 3, "2024-06-01");
    Reservation* r2 = new Reservation(1002, bronzeGuest, room201, 2, "2024-06-05");

    list->insert(r1);
    list->insert(r2);

    Reservation* found = list->findById(1002);

    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->getReservationId(), 1002);
}

TEST_F(ReservationListTest, FindByIdReturnsNullWhenNotFound) {
    Reservation* r1 = new Reservation(1001, goldGuest, room101, 3, "2024-06-01");
    list->insert(r1);

    Reservation* found = list->findById(9999);

    EXPECT_EQ(found, nullptr);
}

TEST_F(ReservationListTest, FindByIdOnEmptyList) {
    Reservation* found = list->findById(1001);
    EXPECT_EQ(found, nullptr);
}

TEST_F(ReservationListTest, FindByGuestReturnsAllGuestReservations) {
    Reservation* r1 = new Reservation(1001, goldGuest,   room101, 3, "2024-06-01");
    Reservation* r2 = new Reservation(1002, bronzeGuest, room201, 2, "2024-06-05");
    Reservation* r3 = new Reservation(1003, goldGuest,   room102, 1, "2024-06-15");

    list->insert(r1);
    list->insert(r2);
    list->insert(r3);

    Reservation* results[10];
    int count = list->findByGuest(goldGuest, results, 10);

    EXPECT_EQ(count, 2);
}

TEST_F(ReservationListTest, FindActiveReservations) {
    Reservation* r1 = new Reservation(1001, goldGuest,   room101, 3, "2024-06-01");
    Reservation* r2 = new Reservation(1002, bronzeGuest, room201, 2, "2024-06-05");
    Reservation* r3 = new Reservation(1003, goldGuest,   room102, 1, "2024-06-15");

    list->insert(r1);
    list->insert(r2);
    list->insert(r3);

    r2->cancelReservation();  // Make one inactive

    Reservation* active[10];
    int count = list->findActive(active, 10);

    EXPECT_EQ(count, 2);
}

// ============================================================================
// RESERVATION LIST - REMOVAL
// ============================================================================

TEST_F(ReservationListTest, RemoveByIdFromSingleElementList) {
    Reservation* res = new Reservation(1001, goldGuest, room101, 3, "2024-06-01");
    list->insert(res);

    bool result = list->removeById(1001);

    EXPECT_TRUE(result);
    EXPECT_EQ(list->getSize(), 0);
    EXPECT_TRUE(list->isEmpty());
    EXPECT_EQ(list->getHead(), nullptr);
    EXPECT_EQ(list->getTail(), nullptr);
}

TEST_F(ReservationListTest, RemoveHeadNode) {
    Reservation* r1 = new Reservation(1001, goldGuest,   room101, 3, "2024-06-01");
    Reservation* r2 = new Reservation(1002, bronzeGuest, room201, 2, "2024-06-05");

    list->insert(r1);
    list->insert(r2);

    list->removeById(1001);

    EXPECT_EQ(list->getSize(), 1);
    EXPECT_EQ(list->getHead()->reservation->getReservationId(), 1002);
    // New head should have no prev
    EXPECT_EQ(list->getHead()->prev, nullptr);
}

TEST_F(ReservationListTest, RemoveTailNode) {
    Reservation* r1 = new Reservation(1001, goldGuest,   room101, 3, "2024-06-01");
    Reservation* r2 = new Reservation(1002, bronzeGuest, room201, 2, "2024-06-05");

    list->insert(r1);
    list->insert(r2);

    list->removeById(1002);

    EXPECT_EQ(list->getSize(), 1);
    EXPECT_EQ(list->getTail()->reservation->getReservationId(), 1001);
    // New tail should have no next
    EXPECT_EQ(list->getTail()->next, nullptr);
}

TEST_F(ReservationListTest, RemoveMiddleNode) {
    Reservation* r1 = new Reservation(1001, goldGuest,   room101, 3, "2024-06-01");
    Reservation* r2 = new Reservation(1002, bronzeGuest, room201, 2, "2024-06-05");
    Reservation* r3 = new Reservation(1003, goldGuest,   room102, 1, "2024-06-15");

    list->insert(r1);
    list->insert(r2);
    list->insert(r3);

    list->removeById(1002);

    EXPECT_EQ(list->getSize(), 2);

    // Remaining nodes should be properly relinked
    ReservationNode* head = list->getHead();
    ReservationNode* tail = list->getTail();
    EXPECT_EQ(head->next, tail);
    EXPECT_EQ(tail->prev, head);
}

TEST_F(ReservationListTest, RemoveByIdNotFound) {
    Reservation* r1 = new Reservation(1001, goldGuest, room101, 3, "2024-06-01");
    list->insert(r1);

    bool result = list->removeById(9999);

    EXPECT_FALSE(result);
    EXPECT_EQ(list->getSize(), 1);  // List unchanged
}

TEST_F(ReservationListTest, RemoveFromEmptyList) {
    bool result = list->removeById(1001);
    EXPECT_FALSE(result);
}

// ============================================================================
// RESERVATION LIST - TRAVERSAL & AGGREGATE OPERATIONS
// ============================================================================
TEST_F(ReservationListTest, CalculateTotalRevenue) {
    // Gold tier = 10% discount, $89/night x 3 = 240.30
    Reservation* r1 = new Reservation(1001, goldGuest, room101, 3, "2024-06-01");
    // Bronze tier = no discount, $149/night (+ Ocean View and Balcony ($40))x 2 = 378.00
    Reservation* r2 = new Reservation(1002, bronzeGuest, room201, 2, "2024-06-05");

    list->insert(r1);
    list->insert(r2);

    CashPayment payment(1, r1->calculateTotalCost(), 300.0);
    r1->attachPayment(&payment);
    r1->processPayment();
    r1->checkIn();
    r1->checkOut();




    CreditCardPayment payment2(2, r2->calculateTotalCost(), "1234", "Mr. Bill", "01/26");
    r2->attachPayment(&payment);
    r2->processPayment();
    r2->checkIn();
    r2->checkOut();
    double expected = (89.0 * 3 * 0.9) + ((149+25+15)*2);
    EXPECT_NEAR_PRICE(list->calculateTotalRevenue(), expected);
}


TEST_F(ReservationListTest, CalculateTotalRevenueWithCancellation) {
    // Gold tier = 10% discount, $89/night x 3 = 240.30
    Reservation* r1 = new Reservation(1001, goldGuest, room101, 3, "2024-06-01");
    // Bronze tier = no discount, $149/night (+ Ocean View and Balcony ($40))x 2 = 378.00
    Reservation* r2 = new Reservation(1002, bronzeGuest, room201, 2, "2024-06-05");

    list->insert(r1);
    list->insert(r2);

    CashPayment payment(1, r1->calculateTotalCost(), 300.0);

    r1->attachPayment(&payment);
    r1->processPayment();
    r1->checkIn();
    r1->checkOut();


    r2->cancelReservation();

    double expected = (89.0 * 3 * 0.9);
    EXPECT_NEAR_PRICE(list->calculateTotalRevenue(), expected);
}

TEST_F(ReservationListTest, CalculateTotalRevenueNoPayments) {
    // Gold tier = 10% discount, $89/night x 3 = 240.30
    Reservation* r1 = new Reservation(1001, goldGuest, room101, 3, "2024-06-01");
    // Bronze tier = no discount, $149/night (+ Ocean View and Balcony ($40))x 2 = 378.00
    Reservation* r2 = new Reservation(1002, bronzeGuest, room201, 2, "2024-06-05");

    list->insert(r1);
    list->insert(r2);

    // Don't have a payment, so no revenue collected
    r1->cancelReservation();
    r2->cancelReservation();

    EXPECT_NEAR_PRICE(list->calculateTotalRevenue(), 0);
}


TEST_F(ReservationListTest, CalculateTotalRevenueEmptyList) {
    EXPECT_NEAR_PRICE(list->calculateTotalRevenue(), 0.0);
}

TEST_F(ReservationListTest, GetSizeAfterMultipleOperations) {
    Reservation* r1 = new Reservation(1001, goldGuest,   room101, 3, "2024-06-01");
    Reservation* r2 = new Reservation(1002, bronzeGuest, room201, 2, "2024-06-05");
    Reservation* r3 = new Reservation(1003, goldGuest,   room102, 1, "2024-06-15");

    list->insert(r1);
    list->insert(r2);
    list->insert(r3);
    EXPECT_EQ(list->getSize(), 3);

    list->removeById(1002);
    EXPECT_EQ(list->getSize(), 2);

    Reservation* r4 = new Reservation(1004, bronzeGuest, room102, 4, "2024-07-01");
    list->insert(r4);
    EXPECT_EQ(list->getSize(), 3);
}

// ============================================================================
// RESERVATION LIST - POLYMORPHISM INTEGRATION
// Verify that the list correctly handles polymorphic Room* and Payment* pointers
// ============================================================================

class ReservationListPolymorphismTest : public ::testing::Test {
protected:
    ReservationList* list;
    Guest* guest;

    void SetUp() override {
        list  = new ReservationList();
        guest = new Guest(1, "Poly Guest", "555-9999", "poly@test.com", 5000);
    }

    void TearDown() override {
        delete list;
        delete guest;
    }
};

TEST_F(ReservationListPolymorphismTest, InsertReservationsWithDifferentRoomTypes) {
    // Polymorphic Room* pointers
    Room* standard = new StandardRoom(101, 1, 1, false);
    Room* deluxe   = new DeluxeRoom(201, 2, 1, false, "City");
    Room* suite    = new Suite(301, 3, 2, 800, true, true);

    Reservation* r1 = new Reservation(1001, guest, standard, 2, "2024-06-01");
    Reservation* r2 = new Reservation(1002, guest, deluxe,   3, "2024-06-05");
    Reservation* r3 = new Reservation(1003, guest, suite,    1, "2024-06-10");

    list->insert(r1);
    list->insert(r2);
    list->insert(r3);

    EXPECT_EQ(list->getSize(), 3);

    // Verify polymorphic dispatch still works through list nodes
    Reservation* found = list->findById(1001);
    EXPECT_STREQ(found->getRoom()->getRoomType(), "Standard");

    found = list->findById(1002);
    EXPECT_STREQ(found->getRoom()->getRoomType(), "Deluxe");

    found = list->findById(1003);
    EXPECT_STREQ(found->getRoom()->getRoomType(), "Suite");

    delete standard;
    delete deluxe;
    delete suite;
}

TEST_F(ReservationListPolymorphismTest, RevenueCalculationUsesPolymorphicPricing) {
    // Suite has special extended-stay pricing - verify it flows through the list correctly
    Room* suite = new Suite(301, 3, 1, 600, false, false);
    // Suite's calculatePrice(7) uses its own override (extended-stay discount)
    double expected = suite->calculatePrice(7) * (1.0 - guest->getTierDiscount());
    
    Reservation* res = new Reservation(1001, guest, suite, 7, "2024-06-01");

    list->insert(res);
    CashPayment payment(1, suite->calculatePrice(7) * (1.0 - guest->getTierDiscount()), 2000);
    res->attachPayment(&payment);
    res->processPayment();
    res->checkIn();
    res->checkOut();

    EXPECT_NEAR_PRICE(list->calculateTotalRevenue(), expected);

    delete suite;
}

TEST_F(ReservationListPolymorphismTest, PaymentTypesStoredPolymorphically) {
    Room* room = new StandardRoom(101, 1, 1, false);

    Reservation* r1 = new Reservation(1001, guest, room, 2, "2024-06-01");
    Reservation* r2 = new Reservation(1002, guest, room, 2, "2024-06-05");

    // Attach different polymorphic Payment* types
    CashPayment* cash = new CashPayment(1, r1->calculateTotalCost(), 200.0);
    CreditCardPayment* card = new CreditCardPayment(2, r2->calculateTotalCost(),
                                                    "4242", guest->getName(), "12/26");
    r1->attachPayment(cash);
    r2->attachPayment(card);

    list->insert(r1);
    list->insert(r2);

    // Verify payment types survive round-trip through list
    Reservation* found1 = list->findById(1001);
    Reservation* found2 = list->findById(1002);

    EXPECT_STREQ(found1->getPayment()->getPaymentType(), "Cash");
    EXPECT_STREQ(found2->getPayment()->getPaymentType(), "Credit Card");

    delete room;
    delete cash;
    delete card;
}

// ============================================================================
// DISPLAY TESTS (Confirm no crashes during traversal)
// ============================================================================

TEST_F(ReservationListTest, DisplayAllDoesNotCrash) {
    Reservation* r1 = new Reservation(1001, goldGuest,   room101, 3, "2024-06-01");
    Reservation* r2 = new Reservation(1002, bronzeGuest, room201, 2, "2024-06-05");

    list->insert(r1);
    list->insert(r2);

    EXPECT_NO_THROW(list->displayAll());
}

TEST_F(ReservationListTest, DisplayAllOnEmptyListDoesNotCrash) {
    EXPECT_NO_THROW(list->displayAll());
}
