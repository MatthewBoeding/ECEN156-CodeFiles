#include "guest_management.h"
#include <cstring>

// ============================================================================
//  NAME:
//  ASSIGNMENT:
//  DATE:
// ============================================================================

// ============================================================================
// GUEST MANAGEMENT SYSTEM - Week 3 Assignment
//
// This week focuses on POINTERS! You'll work with:
// - Pointer declarations and dereferencing
// - The arrow operator (->) for accessing members through pointers
// - nullptr checks for safety
// - Pointers as struct members (linking objects together)
// - Arrays of pointers
// - Pointer-to-pointer (double pointers)
//
// Key concepts:
// - Guest* ptr;           // Pointer to a Guest
// - ptr->name             // Access member through pointer (same as (*ptr).name)
// - ptr == nullptr        // Check if pointer is null
// - &guests[i]            // Get address of array element
// - Guest* arr[]          // Array of pointers to Guests
// - Guest** pp            // Pointer to a pointer (double pointer)
//
// IMPORTANT: Always check for nullptr before dereferencing a pointer!
// ============================================================================

// ----------------------------------------------------------------------------
// Guest Management Functions (Basic Pointer Operations)
// ----------------------------------------------------------------------------

Guest* findGuestById(Guest guests[], int size, int guestId) {
    // TODO: Find guest with matching guestId
    // Hint: Loop through array, compare guestId, return &guests[i] if found
    // Return nullptr if not found
    return nullptr;  // Replace this
}

Guest* findGuestByName(Guest guests[], int size, const char* name) {
    // TODO: Find guest with matching name
    // Hint: Use strcmp(guests[i].name, name) == 0 to compare
    // Return pointer to guest if found, nullptr if not found
    return nullptr;  // Replace this
}

int countCheckedInGuests(const Guest* guests, int size) {
    // TODO: Count guests where isCheckedIn is true
    // Challenge: Try using pointer arithmetic instead of array indexing!
    //   - Use (guests + i) instead of &guests[i]
    //   - Use (guests + i)->isCheckedIn instead of guests[i].isCheckedIn
    // Or use regular array indexing - both are acceptable
    return 0;  // Replace this
}

Guest* findTopLoyaltyMember(Guest guests[], int size) {
    // TODO: Find guest with the highest loyaltyPoints
    // Hint: Track pointer to best guest found so far
    //   Guest* top = &guests[0];
    //   if (guests[i].loyaltyPoints > top->loyaltyPoints) ...
    return nullptr;  // Replace this
}

bool addLoyaltyPoints(Guest guests[], int size, int guestId, int points) {
    // TODO: Find guest by ID and add points to their loyaltyPoints
    // Hint: Use findGuestById, check for nullptr, then add points
    // Return true if successful, false if guest not found
    return false;  // Replace this
}

bool updateGuestContact(Guest* guest, const char* newPhone, const char* newEmail) {
    // TODO: Update guest's phone and/or email
    // IMPORTANT: First check if guest is nullptr!
    // If newPhone is not nullptr, copy it to guest->phone using strcpy
    // If newEmail is not nullptr, copy it to guest->email using strcpy
    // Return false if guest is nullptr, true otherwise
    return false;  // Replace this
}

// ----------------------------------------------------------------------------
// Room-Guest Relationship Functions (Pointer Connections)
// ----------------------------------------------------------------------------

bool checkGuestIntoRoom(Room* room, Guest* guest) {
    // TODO: Assign guest to room's currentGuest pointer
    // Check that both room and guest are not nullptr
    // Check that room->currentGuest is nullptr (room is vacant)
    // Set room->currentGuest = guest
    // Set guest->isCheckedIn = true
    // Return true if successful, false otherwise
    return false;  // Replace this
}

Guest* checkGuestOutOfRoom(Room* room) {
    // TODO: Remove guest from room and return pointer to that guest
    // Check that room is not nullptr
    // Save the currentGuest pointer before clearing it
    // Set room->currentGuest = nullptr
    // Set the guest's isCheckedIn = false (if guest wasn't null)
    // Return the saved guest pointer (or nullptr if room was vacant)
    return nullptr;  // Replace this
}

Room* findGuestRoom(Room rooms[], int size, const Guest* guest) {
    // TODO: Find which room contains this guest
    // Hint: Compare rooms[i].currentGuest with guest pointer
    // Remember: comparing pointers checks if they point to same object
    // Return pointer to the room, or nullptr if guest not in any room
    return nullptr;  // Replace this
}

int countOccupiedRooms(const Room rooms[], int size) {
    // TODO: Count rooms where currentGuest is not nullptr
    return 0;  // Replace this
}

int getVacantRooms(Room rooms[], int size, Room* vacantRooms[]) {
    // TODO: Fill vacantRooms array with pointers to rooms that have no guest
    // vacantRooms is an array of POINTERS - store addresses: vacantRooms[count] = &rooms[i]
    // Return the count of vacant rooms found
    return 0;  // Replace this
}

// ----------------------------------------------------------------------------
// Reservation Functions (Working with Multiple Pointers)
// ----------------------------------------------------------------------------

bool createReservation(Reservation* reservation, int reservationId,
                       Guest* guest, Room* room, int nights) {
    // TODO: Initialize all fields of the reservation
    // Check that reservation, guest, and room are all not nullptr
    // Set all the fields using the arrow operator:
    //   reservation->reservationId = reservationId;
    //   reservation->guest = guest;
    //   etc.
    // Set isActive to true
    // Return true if successful, false if any pointer was null
    return false;  // Replace this
}

double calculateReservationCost(const Reservation* reservation) {
    // TODO: Calculate total cost (room's pricePerNight * nights)
    // Check that reservation is not nullptr
    // Check that reservation->room is not nullptr
    // Access the price through the pointer chain: reservation->room->pricePerNight
    // Return 0.0 if any pointer is invalid
    return 0.0;  // Replace this
}

int findGuestReservations(Reservation reservations[], int size,
                          const Guest* guest, Reservation* guestReservations[]) {
    // TODO: Find all active reservations for a specific guest
    // Loop through reservations
    // If reservation is active AND reservation.guest == guest (same pointer)
    //   Add pointer to guestReservations array
    // Return count of matching reservations
    return 0;  // Replace this
}

double calculateTotalRevenue(const Reservation reservations[], int size) {
    // TODO: Sum up the cost of all ACTIVE reservations
    // Use calculateReservationCost for each active reservation
    // Hint: Need to pass address of each reservation: &reservations[i]
    return 0.0;  // Replace this
}

bool cancelReservation(Reservation* reservation) {
    // TODO: Set reservation's isActive to false
    // Check that reservation is not nullptr
    // Check that reservation is currently active
    // Return true if cancelled, false if null or already inactive
    return false;  // Replace this
}

// ----------------------------------------------------------------------------
// Advanced Pointer Functions
// ----------------------------------------------------------------------------

void swapGuestPointers(Guest** g1, Guest** g2) {
    // TODO: Swap the two Guest pointers
    // This uses double pointers (pointer to pointer)
    // *g1 gives you the Guest* that g1 points to
    // Save *g1 to temp, set *g1 = *g2, set *g2 = temp
    // No return value needed
}

void sortGuestsByLoyalty(Guest* guestPtrs[], int size) {
    // TODO: Sort the array of guest pointers by loyaltyPoints (descending)
    // Use bubble sort: compare adjacent elements, swap if out of order
    // Access loyalty points: guestPtrs[i]->loyaltyPoints
    // Swap using: swapGuestPointers(&guestPtrs[i], &guestPtrs[j])
    // Descending means highest points first
}

int findGuestsInPointsRange(Guest guests[], int size, int minPoints,
                            int maxPoints, Guest* result[]) {
    // TODO: Find all guests with loyaltyPoints between min and max (inclusive)
    // Store pointers to matching guests in result array
    // Return count of guests found
    return 0;  // Replace this
}
