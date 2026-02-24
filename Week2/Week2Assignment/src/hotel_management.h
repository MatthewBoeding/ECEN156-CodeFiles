#ifndef HOTEL_MANAGEMENT_H
#define HOTEL_MANAGEMENT_H

#include <cstring>

// ============================================================================
// Hotel Management System - Data Structures
// ============================================================================

struct Room {
    int roomNumber;         // Room number (e.g., 101, 102, 201)
    char type[20];          // Room type: "Single", "Double", "Suite"
    double pricePerNight;   // Price per night in dollars
    bool isOccupied;        // true if room is currently occupied
};

struct Guest {
    int guestId;            // Unique guest ID
    char name[50];          // Guest name
    char phone[15];         // Phone number
};

struct Reservation {
    int reservationId;      // Unique reservation ID
    int roomNumber;         // Which room is reserved
    int guestId;            // Which guest made the reservation
    int nights;             // Number of nights staying
};

// ============================================================================
// ASSIGNMENT: Implement these functions in hotel_management.cpp
// Read the tests in hotel_management_test.cpp to understand what each 
// function should do.
// ============================================================================

// ----------------------------------------------------------------------------
// Room Management Functions
// ----------------------------------------------------------------------------

/**
 * Calculate the average price per night across all rooms
 * @param rooms - array of Room structs
 * @param size - number of rooms in the array
 * @return the average price per night
 */
double calculateAveragePrice(const Room rooms[], int size);

/**
 * Find the most expensive room
 * @param rooms - array of Room structs
 * @param size - number of rooms in the array
 * @return the Room with the highest price per night
 */
Room findMostExpensiveRoom(const Room rooms[], int size);

/**
 * Count how many rooms are currently occupied
 * @param rooms - array of Room structs
 * @param size - number of rooms in the array
 * @return count of occupied rooms
 */
int countOccupiedRooms(const Room rooms[], int size);

/**
 * Find a room by its room number
 * @param rooms - array of Room structs
 * @param size - number of rooms in the array
 * @param roomNumber - the room number to search for
 * @return pointer to the Room if found, nullptr if not found
 */
Room* findRoomByNumber(Room rooms[], int size, int roomNumber);

/**
 * Count how many rooms of a specific type exist
 * @param rooms - array of Room structs
 * @param size - number of rooms in the array
 * @param type - room type to count (e.g., "Single", "Double", "Suite")
 * @return count of rooms matching the type
 */
int countRoomsByType(const Room rooms[], int size, const char* type);

/**
 * Get all available (not occupied) rooms
 * @param rooms - array of Room structs to search
 * @param size - number of rooms in the array
 * @param available - array to store available rooms
 * @return number of available rooms found
 */
int getAvailableRooms(const Room rooms[], int size, Room available[]);

/**
 * Check in a guest to a room (mark room as occupied)
 * @param rooms - array of Room structs
 * @param size - number of rooms in the array
 * @param roomNumber - room number to check in
 * @return true if successful, false if room not found or already occupied
 */
bool checkInRoom(Room rooms[], int size, int roomNumber);

/**
 * Check out a guest from a room (mark room as available)
 * @param rooms - array of Room structs
 * @param size - number of rooms in the array
 * @param roomNumber - room number to check out
 * @return true if successful, false if room not found or already available
 */
bool checkOutRoom(Room rooms[], int size, int roomNumber);

// ----------------------------------------------------------------------------
// Reservation Functions
// ----------------------------------------------------------------------------

/**
 * Calculate the total cost of a reservation
 * @param room - the room being reserved
 * @param nights - number of nights staying
 * @return total cost (pricePerNight * nights)
 */
double calculateReservationCost(const Room& room, int nights);

/**
 * Find the total revenue from all reservations
 * @param reservations - array of Reservation structs
 * @param resSize - number of reservations
 * @param rooms - array of Room structs
 * @param roomSize - number of rooms
 * @return total revenue across all reservations
 */
double calculateTotalRevenue(const Reservation reservations[], int resSize,
                             const Room rooms[], int roomSize);

#endif