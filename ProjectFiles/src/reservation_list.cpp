#include "reservation_list.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

// ============================================================================
// RESERVATION NODE IMPLEMENTATION
// ============================================================================

ReservationNode::ReservationNode() {
    // TODO: Initialize all three member variables to their null/zero defaults
    //       reservation -> nullptr  (no payload yet)
    //       next        -> nullptr  (no successor)
    //       prev        -> nullptr  (no predecessor)
}

ReservationNode::ReservationNode(Reservation* reservation) {
    // TODO: Store the incoming reservation pointer in this->reservation
    //       Set next and prev to nullptr
    //       Hint: use "this->reservation = reservation" to disambiguate
    //       the parameter name from the member name
}

// ============================================================================
// RESERVATION LIST - CONSTRUCTOR & DESTRUCTOR
// ============================================================================

ReservationList::ReservationList() {
    // TODO: Initialize head and tail to nullptr (empty list has no nodes)
    //       Initialize size to 0
}

ReservationList::~ReservationList() {
    // TODO: Walk the list from head to tail, deleting every node.
    //       For each node you must:
    //         1. Save current->next in a temp variable BEFORE deleting
    //            (once you delete current, current->next is undefined)
    //         2. delete current->reservation  (free the Reservation object)
    //         3. delete current               (free the node itself)
    //         4. Advance using your saved temp pointer
    //
    //       After the loop, set head and tail back to nullptr and size to 0
    //       so the object is left in a valid empty state.
    //
    //       Hint: this mirrors Hotel::~Hotel() which loops over reservations[]
    //       and calls delete on each pointer.
}

// ============================================================================
// ACCESSORS
// ============================================================================

// These are one-liners - just return the matching member variable.

ReservationNode* ReservationList::getHead() const {
    // TODO: return head
}

ReservationNode* ReservationList::getTail() const {
    // TODO: return tail
}

int ReservationList::getSize() const {
    // TODO: return size
}

bool ReservationList::isEmpty() const {
    // TODO: The list is empty when size == 0 (equivalently, when head == nullptr)
    //       Return that boolean expression directly
}

// ============================================================================
// INSERTION
// ============================================================================

void ReservationList::insert(Reservation* reservation) {
    // TODO: Guard - if reservation is nullptr, do nothing and return early.
    //
    // TODO: Allocate a new ReservationNode on the heap, passing reservation
    //       to the parameterized constructor.
    //
    // TODO: Handle two cases:
    //
    //   Case A - list is currently EMPTY (use isEmpty()):
    //       The new node is both the first and last node.
    //       Set head = newNode AND tail = newNode.
    //
    //   Case B - list already has nodes (append to tail):
    //       Step 1: newNode->prev = tail        (look back at current tail)
    //       Step 2: tail->next    = newNode     (current tail looks forward)
    //       Step 3: tail          = newNode     (advance tail pointer)
    //
    // TODO: Increment size by 1 in both cases.
}

// ============================================================================
// SEARCH
// ============================================================================

Reservation* ReservationList::findById(int reservationId) const {
    // TODO: Start a pointer "current" at head.
    //       Walk forward (current = current->next) until current == nullptr.
    //       At each node, check:
    //           current->reservation->getReservationId() == reservationId
    //       If it matches, return current->reservation immediately.
    //       If the loop ends without finding a match, return nullptr.
}

int ReservationList::findByGuest(const Guest* guest, Reservation* result[], int maxSize) const {
    // TODO: Same traversal pattern as findById, but collect ALL matches.
    //       Maintain an int "count" starting at 0.
    //       At each node, check:
    //           current->reservation->getGuest() == guest
    //       If it matches, store current->reservation in result[count]
    //       and increment count.
    //       Stop early if count reaches maxSize (don't overflow result[]).
    //       Return count when done.
}

int ReservationList::findActive(Reservation* result[], int maxSize) const {
    // TODO: Same pattern as findByGuest but the filter condition is:
    //           current->reservation->getIsActive() == true
    //       Collect matching reservations into result[], return count found.
}

int ReservationList::findCheckedIn(Reservation* result[], int maxSize) const {
    // TODO: Same pattern - filter condition is:
    //           current->reservation->getIsCheckedIn() == true
    //       Collect into result[], return count.
}

// ============================================================================
// REMOVAL
// ============================================================================

// unlinkNode is a static helper (not a member) that does the actual pointer
// surgery. Both removeById and deleteById call it.
//
// Parameters:
//   head, tail  - references to the list's head/tail (so we can update them)
//   size        - reference to the list's size counter
//   reservationId - the ID to search for
//   removedOut  - if non-null, write the removed Reservation* here so the
//                 caller can decide whether to delete it
//
// Returns true if a node was found and removed, false otherwise.

static bool unlinkNode(ReservationNode*& head, ReservationNode*& tail,
                        int& size, int reservationId,
                        Reservation** removedOut) {
    // TODO: Walk from head looking for a node whose
    //       reservation->getReservationId() == reservationId.
    //
    // TODO: When found, perform the four-pointer relinking:
    //
    //   Predecessor side (current->prev):
    //     If current->prev != nullptr:
    //         current->prev->next = current->next   (skip over current)
    //     Else (current IS the head):
    //         head = current->next                  (advance head)
    //
    //   Successor side (current->next):
    //     If current->next != nullptr:
    //         current->next->prev = current->prev   (skip over current)
    //     Else (current IS the tail):
    //         tail = current->prev                  (retreat tail)
    //
    // TODO: If removedOut is not nullptr, store current->reservation there
    //       so the caller can choose to delete it.
    //
    // TODO: delete current (the node shell), decrement size, return true.
    //
    // TODO: If the loop ends without finding the ID, return false.
}

bool ReservationList::removeById(int reservationId) {
    // TODO: Call unlinkNode passing nullptr for removedOut.
    //       This unlinks and deletes the NODE but leaves the
    //       Reservation object alive for whoever still holds a pointer to it.
    //       Return whatever unlinkNode returns.
}

bool ReservationList::deleteById(int reservationId) {
    // TODO: Declare a Reservation* res = nullptr.
    //       Call unlinkNode passing &res for removedOut.
    //       If found (unlinkNode returned true) AND res != nullptr,
    //       call "delete res" to also destroy the Reservation object.
    //       Return the bool result from unlinkNode.
}

// ============================================================================
// AGGREGATE OPERATIONS
// ============================================================================

double ReservationList::calculateTotalRevenue() const {
    // TODO: Declare a double "revenue = 0.0".
    //       Walk the list. For each node, get the Reservation* res.
    //       A reservation counts as completed revenue when ALL of:
    //           !res->getIsActive()       (not still active/future)
    //           !res->getIsCheckedIn()    (guest has checked out)
    //           res->getPayment() != nullptr
    //           res->getPayment()->getIsProcessed() == true
    //       If all conditions pass, add res->getTotalCost() to revenue.
    //       Return revenue.
    //
    //       Hint: this exactly mirrors Hotel::calculateTotalRevenue().
}

double ReservationList::calculateRevenueByRoomType(const char* type) const {
    // TODO: Same as calculateTotalRevenue but add a room-type filter:
    //       Also require:
    //           res->getRoom() != nullptr
    //           strcmp(res->getRoom()->getRoomType(), type) == 0
    //
    //       Note: getRoomType() is a VIRTUAL function - this is polymorphic
    //       dispatch in action. The list doesn't know if it's a Standard,
    //       Deluxe, or Suite - the vtable picks the right version at runtime.
}

int ReservationList::countActive() const {
    // TODO: Walk the list counting nodes where
    //           current->reservation->getIsActive() == true
    //       Return the count.
}

// ============================================================================
// DISPLAY
// ============================================================================

void ReservationList::displayAll() const {
    // TODO: Print a header line and the total count.
    //       If isEmpty(), print "(No reservations)" and return early.
    //       Otherwise walk the list and call current->reservation->display()
    //       on each node, followed by a blank endl.
    //
    //       Note: display() is virtual - each Reservation subtype will print
    //       its own details automatically.
}

void ReservationList::displayActive() const {
    // TODO: Print a header line.
    //       If isEmpty(), print "(No reservations)" and return early.
    //       Walk the list - only call display() on nodes where
    //           current->reservation->getIsActive() == true
    //       Keep a local activeCount and print it at the end.
}