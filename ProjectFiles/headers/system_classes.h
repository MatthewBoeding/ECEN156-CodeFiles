#ifndef SYSTEM_CLASSES_H
#define SYSTEM_CLASSES_H

#include "hotel_classes.h"

// ============================================================================
// HOTEL MANAGEMENT SYSTEM - Week 7: Polymorphism & System Integration
// 
// This file contains the system classes that use polymorphism:
// - Reservation: Connects Guest, Room*, and Payment* polymorphically
// - Hotel: Manages collections of polymorphic Room*, Guest*, Employee*, Reservation*
//
// Focus: Runtime polymorphism, virtual function dispatch, polymorphic collections
// ============================================================================

// ============================================================================
// RESERVATION CLASS
// Demonstrates polymorphism by using Room* and Payment* pointers
// ============================================================================

class Reservation {
private:
    int reservationId;
    Guest* guest;
    Room* room;                 // Polymorphic pointer - can point to any room type
    int nights;
    char checkInDate[11];       // YYYY-MM-DD format
    char checkOutDate[11];
    bool isActive;
    bool isCheckedIn;
    double totalCost;
    Payment* payment;           // Polymorphic pointer - can point to any payment type

public:
    // Constructors
    Reservation();
    Reservation(int reservationId, Guest* guest, Room* room, int nights,
                const char* checkInDate);
    ~Reservation();
    
    // Getters
    int getReservationId() const;
    Guest* getGuest() const;
    Room* getRoom() const;
    int getNights() const;
    const char* getCheckInDate() const;
    const char* getCheckOutDate() const;
    bool getIsActive() const;
    bool getIsCheckedIn() const;
    double getTotalCost() const;
    Payment* getPayment() const;
    
    // Calculate total cost (uses polymorphic room->getBasePrice())
    // Also applies guest's loyalty discount
    double calculateTotalCost() const;
    
    // Reservation management
    bool confirmReservation();
    bool cancelReservation();
    bool checkIn();
    bool checkOut();
    
    // Payment (uses polymorphic payment->processPayment())
    bool attachPayment(Payment* payment);
    bool processPayment();
    
    // Display
    void display() const;
};

// ============================================================================
// HOTEL CLASS
// Central management class that demonstrates polymorphism with collections
// ============================================================================

class Hotel {
private:
    char name[100];
    char address[200];
    
    // Polymorphic arrays - can hold pointers to any derived type
    Room* rooms[100];           // Can hold StandardRoom*, DeluxeRoom*, Suite*
    int roomCount;
    
    Guest* guests[200];
    int guestCount;
    
    Employee* employees[50];
    int employeeCount;
    
    Reservation* reservations[500];
    int reservationCount;
    
    // Revenue tracking
    double totalRevenue;
    
    // ID counters
    int nextReservationId;

public:
    // Constructor & Destructor
    Hotel();
    Hotel(const char* name, const char* address);
    ~Hotel();
    
    // Getters
    const char* getName() const;
    const char* getAddress() const;
    int getRoomCount() const;
    int getGuestCount() const;
    int getEmployeeCount() const;
    int getReservationCount() const;
    double getTotalRevenue() const;
    
    // ==================== ROOM MANAGEMENT ====================
    // These methods demonstrate polymorphism with Room* pointers
    
    // Add rooms (accepts any Room* - StandardRoom*, DeluxeRoom*, Suite*)
    bool addRoom(Room* room);
    
    // Find rooms
    Room* findRoomByNumber(int roomNumber) const;
    
    // Get available rooms (returns polymorphic array)
    int getAvailableRooms(Room* available[], int maxSize) const;
    
    // Get rooms by type (uses polymorphic getRoomType() method)
    int getRoomsByType(const char* type, Room* result[], int maxSize) const;
    
    // Get the cheapest available room (uses polymorphic getBasePrice())
    Room* findCheapestAvailable() const;
    
    // Get rooms needing cleaning
    int getRoomsNeedingCleaning(Room* result[], int maxSize) const;
    
    // ==================== GUEST MANAGEMENT ====================
    
    // Add/remove guests
    bool addGuest(Guest* guest);
    bool removeGuest(int guestId);
    
    // Find guests
    Guest* findGuestById(int guestId) const;
    Guest* findGuestByName(const char* name) const;
    
    // Get guests by loyalty tier
    int getGuestsByTier(const char* tier, Guest* result[], int maxSize) const;
    
    // Get top loyalty members
    int getTopLoyaltyMembers(Guest* result[], int count) const;
    
    // ==================== EMPLOYEE MANAGEMENT ====================
    
    bool addEmployee(Employee* employee);
    Employee* findEmployeeById(int employeeId) const;
    double calculateTotalPayroll() const;
    
    // ==================== RESERVATION MANAGEMENT ====================
    // These methods demonstrate creating and managing polymorphic Reservation objects
    
    // Create a new reservation (uses polymorphic Room* and Guest*)
    Reservation* createReservation(Guest* guest, Room* room, int nights,
                                    const char* checkInDate);
    
    // Find reservations
    Reservation* findReservationById(int reservationId) const;
    int getGuestReservations(const Guest* guest, Reservation* result[], 
                             int maxSize) const;
    int getActiveReservations(Reservation* result[], int maxSize) const;
    
    // ==================== FINANCIAL REPORTING ====================
    
    // Calculate revenue from all completed reservations
    double calculateTotalRevenue() const;
    
    // Calculate revenue by room type (uses polymorphism to filter)
    double calculateRevenueByRoomType(const char* type) const;
    
    // Get occupancy rate
    double getOccupancyRate() const;
    
    // ==================== DISPLAY/REPORTS ====================
    // These methods demonstrate polymorphic display() calls
    
    void displayAllRooms() const;
    void displayAvailableRooms() const;
    void displayAllGuests() const;
    void displayActiveReservations() const;
    void displayFinancialSummary() const;
};

#endif // SYSTEM_CLASSES_H