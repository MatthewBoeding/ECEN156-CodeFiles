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

    for(int i = 0; i<size; i++)
    {
        if(rooms[i].roomNumber == roomNumber)
        {
            return &rooms[i];
        }
    }
    return nullptr;
}

int countRoomsByType(const Room rooms[], int size, const char* type) {
    int count = 0;

    return count;
}

int getAvailableRooms(const Room rooms[], int size, Room available[]) {
    int count = 0;
    for(int i =0; i<size; i++)
    {
        if(!rooms[i].isOccupied)
        {
            available[count] = rooms[i];
            count++;
        }
    }
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
    // loop through reservations since they determine revenue
    for(int i =0; i<resSize; i++)
    { 
        Room * matchingRoom = findRoomByNumber(const_cast<Room*>(rooms), roomSize, reservations[i].roomNumber);          
        //next access room's pricepernight and reservations duration
        totalRevenue += matchingRoom->pricePerNight * reservations[i].nights;
    }
    return totalRevenue;
}
