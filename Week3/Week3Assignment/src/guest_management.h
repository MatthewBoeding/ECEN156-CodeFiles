#ifndef GUEST_MANAGEMENT_H
#define GUEST_MANAGEMENT_H

#include <cstring>

// ============================================================================
// Guest Management System - Data Structures
// Week 3: Pointers
// ============================================================================

struct Guest {
    int guestId;            // Unique guest ID
    char name[50];          // Guest name
    char phone[15];         // Phone number
    char email[50];         // Email address
    int loyaltyPoints;      // Loyalty program points
    bool isCheckedIn;       // Currently checked in?
};

struct Room {
    int roomNumber;         // Room number (e.g., 101, 102, 201)
    char type[20];          // Room type: "Single", "Double", "Suite"
    double pricePerNight;   // Price per night in dollars
    Guest* currentGuest;    // Pointer to current guest (nullptr if vacant)
};

struct Reservation {
    int reservationId;      // Unique reservation ID
    Guest* guest;           // Pointer to the guest
    Room* room;             // Pointer to the room
    int nights;             // Number of nights staying
    bool isActive;          // Is reservation currently active?
};

// ============================================================================
// ASSIGNMENT: Implement these functions in guest_management.cpp
// This week focuses on POINTERS - pay attention to:
//   - Dereferencing pointers with * and ->
//   - Checking for nullptr before using pointers
//   - Pointer arithmetic and arrays
//   - Passing pointers to functions
// ============================================================================

// ----------------------------------------------------------------------------
// Guest Management Functions (Basic Pointer Operations)
// ----------------------------------------------------------------------------

/**
 * Find a guest by their ID
 * @param guests - array of Guest structs
 * @param size - number of guests in the array
 * @param guestId - the guest ID to search for
 * @return pointer to the Guest if found, nullptr if not found
 */
Guest* findGuestById(Guest guests[], int size, int guestId);

/**
 * Find a guest by their name (case-sensitive)
 * @param guests - array of Guest structs
 * @param size - number of guests in the array
 * @param name - the name to search for
 * @return pointer to the Guest if found, nullptr if not found
 */
Guest* findGuestByName(Guest guests[], int size, const char* name);

/**
 * Count how many guests are currently checked in
 * Uses pointer arithmetic to traverse the array
 * @param guests - pointer to first Guest in array
 * @param size - number of guests in the array
 * @return count of checked-in guests
 */
int countCheckedInGuests(const Guest* guests, int size);

/**
 * Find the guest with the most loyalty points
 * @param guests - array of Guest structs
 * @param size - number of guests in the array
 * @return pointer to the Guest with most points
 */
Guest* findTopLoyaltyMember(Guest guests[], int size);

/**
 * Add loyalty points to a guest (found by ID)
 * @param guests - array of Guest structs
 * @param size - number of guests in the array
 * @param guestId - the guest ID to add points to
 * @param points - number of points to add
 * @return true if successful, false if guest not found
 */
bool addLoyaltyPoints(Guest guests[], int size, int guestId, int points);

/**
 * Update a guest's contact information using a pointer
 * @param guest - pointer to the Guest to update (may be nullptr)
 * @param newPhone - new phone number (nullptr to keep existing)
 * @param newEmail - new email address (nullptr to keep existing)
 * @return true if successful, false if guest pointer is nullptr
 */
bool updateGuestContact(Guest* guest, const char* newPhone, const char* newEmail);

// ----------------------------------------------------------------------------
// Room-Guest Relationship Functions (Pointer Connections)
// ----------------------------------------------------------------------------

/**
 * Check a guest into a room (connects guest pointer to room)
 * @param room - pointer to the Room
 * @param guest - pointer to the Guest
 * @return true if successful, false if room occupied or pointers null
 */
bool checkGuestIntoRoom(Room* room, Guest* guest);

/**
 * Check a guest out of a room (disconnects guest pointer)
 * @param room - pointer to the Room
 * @return pointer to the Guest who was checked out, nullptr if room was vacant
 */
Guest* checkGuestOutOfRoom(Room* room);

/**
 * Find which room a guest is currently in
 * @param rooms - array of Room structs
 * @param size - number of rooms in the array
 * @param guest - pointer to the Guest to find
 * @return pointer to the Room the guest is in, nullptr if not found
 */
Room* findGuestRoom(Room rooms[], int size, const Guest* guest);

/**
 * Count how many rooms are currently occupied (have a guest)
 * @param rooms - array of Room structs
 * @param size - number of rooms in the array
 * @return count of occupied rooms
 */
int countOccupiedRooms(const Room rooms[], int size);

/**
 * Get all vacant rooms (rooms with no guest)
 * @param rooms - array of Room structs
 * @param size - number of rooms in the array
 * @param vacantRooms - array to store pointers to vacant rooms
 * @return number of vacant rooms found
 */
int getVacantRooms(Room rooms[], int size, Room* vacantRooms[]);

// ----------------------------------------------------------------------------
// Reservation Functions (Working with Multiple Pointers)
// ----------------------------------------------------------------------------

/**
 * Create a reservation linking a guest to a room
 * @param reservation - pointer to Reservation to initialize
 * @param reservationId - ID for the new reservation
 * @param guest - pointer to the Guest
 * @param room - pointer to the Room
 * @param nights - number of nights
 * @return true if successful, false if any pointer is null
 */
bool createReservation(Reservation* reservation, int reservationId,
                       Guest* guest, Room* room, int nights);

/**
 * Calculate the total cost of a reservation
 * @param reservation - pointer to the Reservation
 * @return total cost (room price * nights), or 0.0 if invalid
 */
double calculateReservationCost(const Reservation* reservation);

/**
 * Find all active reservations for a specific guest
 * @param reservations - array of Reservation structs
 * @param size - number of reservations
 * @param guest - pointer to the Guest to search for
 * @param guestReservations - array to store pointers to matching reservations
 * @return number of reservations found for this guest
 */
int findGuestReservations(Reservation reservations[], int size,
                          const Guest* guest, Reservation* guestReservations[]);

/**
 * Calculate total revenue from all active reservations
 * @param reservations - array of Reservation structs
 * @param size - number of reservations
 * @return total revenue from active reservations
 */
double calculateTotalRevenue(const Reservation reservations[], int size);

/**
 * Cancel a reservation (set to inactive)
 * @param reservation - pointer to the Reservation to cancel
 * @return true if successful, false if pointer null or already inactive
 */
bool cancelReservation(Reservation* reservation);

// ----------------------------------------------------------------------------
// Advanced Pointer Functions
// ----------------------------------------------------------------------------

/**
 * Swap two guest pointers
 * @param g1 - pointer to first Guest pointer
 * @param g2 - pointer to second Guest pointer
 */
void swapGuestPointers(Guest** g1, Guest** g2);

/**
 * Sort an array of guest pointers by loyalty points (descending)
 * Uses bubble sort with pointer swapping
 * @param guestPtrs - array of pointers to Guests
 * @param size - number of pointers in the array
 */
void sortGuestsByLoyalty(Guest* guestPtrs[], int size);

/**
 * Find guests with loyalty points in a given range
 * @param guests - array of Guest structs
 * @param size - number of guests
 * @param minPoints - minimum points (inclusive)
 * @param maxPoints - maximum points (inclusive)
 * @param result - array to store pointers to matching guests
 * @return number of guests found in range
 */
int findGuestsInPointsRange(Guest guests[], int size, int minPoints,
                            int maxPoints, Guest* result[]);

#endif
