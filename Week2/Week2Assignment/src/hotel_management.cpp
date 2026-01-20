#include "hotel_management.h"
#include <cstring>

// ============================================================================
// SOLUTION FILE - FOR INSTRUCTOR USE ONLY
// Complete implementations of all hotel management functions
// ============================================================================

double calculateAveragePrice(const Room rooms[], int size) {
    return 0;
}

Room findMostExpensiveRoom(const Room rooms[], int size) {
    Room mostExpensive = rooms[0];

    return mostExpensive;
}

int countOccupiedRooms(const Room rooms[], int size) {
    int count = 0;

    return count;
}

Room* findRoomByNumber(Room rooms[], int size, int roomNumber) {

    return nullptr;
}

int countRoomsByType(const Room rooms[], int size, const char* type) {
    int count = 0;

    return count;
}

int getAvailableRooms(const Room rooms[], int size, Room available[]) {
    int count = 0;

    return count;
}

bool checkInRoom(Room rooms[], int size, int roomNumber) {

    return false;  // Room not found
}

bool checkOutRoom(Room rooms[], int size, int roomNumber) {

    return false;  // Room not found
}

double calculateReservationCost(const Room& room, int nights) {
    return room.pricePerNight * nights;
}

double calculateTotalRevenue(const Reservation reservations[], int resSize,
                             const Room rooms[], int roomSize) {
    double totalRevenue = 0.0;
    
    return totalRevenue;
}
