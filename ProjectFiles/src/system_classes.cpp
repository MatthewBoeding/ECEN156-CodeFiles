#include "system_classes.h"
#include <cstring>
#include <iomanip>

// ============================================================================
//  NAME:
//  ASSIGNMENT: Hotel Management System - Week 7: Polymorphism & System Integration
//  DATE:
// ============================================================================

// ============================================================================
// RESERVATION CLASS IMPLEMENTATION
// Demonstrates polymorphism with Room* and Payment* pointers
// ============================================================================

Reservation::Reservation() {
    // TODO: Initialize all members to defaults
    // reservationId = 0, guest = nullptr, room = nullptr
    // nights = 0, empty dates, isActive = false, isCheckedIn = false
    // totalCost = 0.0, payment = nullptr
}

Reservation::Reservation(int reservationId, Guest* guest, Room* room,
                         int nights, const char* checkInDate) {
    // TODO: Initialize all members
    // Use strcpy for checkInDate
    // Calculate checkout date (simplified: just store checkInDate for now)
    // Calculate totalCost using calculateTotalCost()
    // isActive = true, isCheckedIn = false, payment = nullptr
}

Reservation::~Reservation() {
    // Note: Don't delete guest, room, or payment - we don't own them
    // Hotel class manages their lifecycle
}

int Reservation::getReservationId() const {
    return 0;  // TODO
}

Guest* Reservation::getGuest() const {
    return nullptr;  // TODO
}

Room* Reservation::getRoom() const {
    return nullptr;  // TODO
}

int Reservation::getNights() const {
    return 0;  // TODO
}

const char* Reservation::getCheckInDate() const {
    return "";  // TODO
}

const char* Reservation::getCheckOutDate() const {
    return "";  // TODO
}

bool Reservation::getIsActive() const {
    return false;  // TODO
}

bool Reservation::getIsCheckedIn() const {
    return false;  // TODO
}

double Reservation::getTotalCost() const {
    return 0.0;  // TODO
}

Payment* Reservation::getPayment() const {
    return nullptr;  // TODO
}

double Reservation::calculateTotalCost() const {
    // TODO: This demonstrates polymorphism!
    // 1. Get base cost from room->calculatePrice(nights)
    //    This will call the appropriate version (Standard/Deluxe/Suite)
    // 2. Apply guest's tier discount: cost * (1 - guest->getTierDiscount())
    // 3. Return the discounted cost
    return 0.0;
}

bool Reservation::confirmReservation() {
    // TODO: Set isActive = true if guest and room are valid
    return false;
}

bool Reservation::cancelReservation() {
    // TODO:
    // 1. Check if reservation is active and not checked in
    // 2. Set isActive = false
    // 3. If payment was processed, refund it (payment->refund())
    return false;
}

bool Reservation::checkIn() {
    // TODO: This demonstrates polymorphism!
    // 1. Check if reservation is active and not already checked in
    // 2. Check if payment is processed
    // 3. Call room->checkIn(guest) - works with any room type!
    // 4. Set isCheckedIn = true
    // 5. Return success status
    return false;
}

bool Reservation::checkOut() {
    // TODO:
    // 1. Check if reservation is checked in
    // 2. Call room->checkOut()
    // 3. Award loyalty points to guest (e.g., 10 points per dollar spent)
    // 4. Call guest->recordStay()
    // 5. Set isCheckedIn = false, isActive = false
    return false;
}

bool Reservation::attachPayment(Payment* p) {
    // TODO: Attach payment if not already attached
    // payment = p
    return false;
}

bool Reservation::processPayment() {
    // TODO: Process attached payment (polymorphic call!)
    // Call payment->processPayment()
    return false;
}

void Reservation::display() const {
    // TODO: Display full reservation details
    // Include guest info, room info, dates, cost, payment status
    // Use polymorphic display() calls on guest and room
}

// ============================================================================
// HOTEL CLASS IMPLEMENTATION
// Central management class demonstrating polymorphic collections
// ============================================================================

Hotel::Hotel() {
    // TODO: Initialize with empty name/address and zero counts
    // strcpy(name, ""); strcpy(address, "");
    // All counts = 0, totalRevenue = 0, nextReservationId = 1
    // Initialize all array elements to nullptr
}

Hotel::Hotel(const char* name, const char* address) {
    // TODO: Initialize with provided name/address
    // Use strcpy for name and address
    // Set all counts to 0, totalRevenue to 0
    // nextReservationId = 1
    // Initialize all array elements to nullptr
}

Hotel::~Hotel() {
    // TODO: Delete all dynamically allocated objects
    // This demonstrates polymorphic deletion!
    // Delete all rooms (will call proper destructor: ~StandardRoom, ~DeluxeRoom, etc.)
    // Delete all guests
    // Delete all employees
    // Delete all reservations
}

const char* Hotel::getName() const {
    return "";  // TODO
}

const char* Hotel::getAddress() const {
    return "";  // TODO
}

int Hotel::getRoomCount() const {
    return 0;  // TODO
}

int Hotel::getGuestCount() const {
    return 0;  // TODO
}

int Hotel::getEmployeeCount() const {
    return 0;  // TODO
}

int Hotel::getReservationCount() const {
    return 0;  // TODO
}

double Hotel::getTotalRevenue() const {
    return 0.0;  // TODO
}

// ==================== ROOM MANAGEMENT ====================
// These methods demonstrate working with polymorphic Room* arrays

bool Hotel::addRoom(Room* room) {
    // TODO: Add room to array if space available
    // room can be StandardRoom*, DeluxeRoom*, or Suite* - polymorphism!
    // Return true if added successfully
    return false;
}

Room* Hotel::findRoomByNumber(int roomNumber) const {
    // TODO: Search through rooms array
    // Return pointer to room or nullptr if not found
    return nullptr;
}

int Hotel::getAvailableRooms(Room* available[], int maxSize) const {
    // TODO: Fill array with pointers to vacant rooms
    // Use room->isVacant() polymorphic call
    // Return count of available rooms
    return 0;
}

int Hotel::getRoomsByType(const char* type, Room* result[], int maxSize) const {
    // TODO: This demonstrates polymorphism!
    // Use room->getRoomType() to filter
    // Compare with strcmp(room->getRoomType(), type)
    // Fill result array with matching rooms
    // Return count
    return 0;
}

Room* Hotel::findCheapestAvailable() const {
    // TODO: This demonstrates polymorphism!
    // Loop through rooms, find vacant room with lowest getBasePrice()
    // getBasePrice() is a virtual function - calls correct version!
    return nullptr;
}

int Hotel::getRoomsNeedingCleaning(Room* result[], int maxSize) const {
    // TODO: Find rooms that are not clean
    // Use room->getIsClean()
    return 0;
}

// ==================== GUEST MANAGEMENT ====================

bool Hotel::addGuest(Guest* guest) {
    // TODO: Add guest to array if space available
    return false;
}

bool Hotel::removeGuest(int guestId) {
    // TODO: Find and remove guest from array
    // Shift remaining guests down
    return false;
}

Guest* Hotel::findGuestById(int guestId) const {
    // TODO: Search through guests array
    return nullptr;
}

Guest* Hotel::findGuestByName(const char* name) const {
    // TODO: Search by name (use strcmp)
    return nullptr;
}

int Hotel::getGuestsByTier(const char* tier, Guest* result[], int maxSize) const {
    // TODO: Find all guests with matching loyalty tier
    // Use guest->getLoyaltyTier()
    return 0;
}

int Hotel::getTopLoyaltyMembers(Guest* result[], int count) const {
    // TODO: Find guests with highest loyalty points
    // Sort or find top 'count' members
    return 0;
}

// ==================== EMPLOYEE MANAGEMENT ====================

bool Hotel::addEmployee(Employee* employee) {
    // TODO: Add employee to array
    return false;
}

Employee* Hotel::findEmployeeById(int employeeId) const {
    // TODO: Search through employees array
    return nullptr;
}

double Hotel::calculateTotalPayroll() const {
    // TODO: Sum up all employees' pay
    // Use employee->calculatePay() for each employee
    return 0.0;
}

// ==================== RESERVATION MANAGEMENT ====================

Reservation* Hotel::createReservation(Guest* guest, Room* room, int nights,
                                      const char* checkInDate) {
    // TODO: Create new reservation
    // Use nextReservationId and increment it
    // Add to reservations array
    // Return pointer to new reservation
    return nullptr;
}

Reservation* Hotel::findReservationById(int reservationId) const {
    // TODO: Search through reservations array
    return nullptr;
}

int Hotel::getGuestReservations(const Guest* guest, Reservation* result[], 
                                int maxSize) const {
    // TODO: Find all reservations for a specific guest
    return 0;
}

int Hotel::getActiveReservations(Reservation* result[], int maxSize) const {
    // TODO: Find all active reservations
    // Use reservation->getIsActive()
    return 0;
}

// ==================== FINANCIAL REPORTING ====================

double Hotel::calculateTotalRevenue() const {
    // TODO: Sum revenue from all completed (checked out) reservations
    return 0.0;
}

double Hotel::calculateRevenueByRoomType(const char* type) const {
    // TODO: This demonstrates polymorphism!
    // Calculate revenue only from rooms of specified type
    // Use room->getRoomType() to filter
    return 0.0;
}

double Hotel::getOccupancyRate() const {
    // TODO: Calculate percentage of occupied rooms
    // Count occupied rooms / total rooms * 100
    return 0.0;
}

// ==================== DISPLAY/REPORTS ====================
// These methods demonstrate polymorphic display() calls

void Hotel::displayAllRooms() const {
    // TODO: Display all rooms
    // Call room->display() for each - polymorphic call!
    cout << "========== ALL ROOMS ==========" << endl;
    // Loop through rooms and call display()
}

void Hotel::displayAvailableRooms() const {
    // TODO: Display only available rooms
    cout << "========== AVAILABLE ROOMS ==========" << endl;
}

void Hotel::displayAllGuests() const {
    // TODO: Display all guests
    cout << "========== ALL GUESTS ==========" << endl;
    // Call guest->display() for each
}

void Hotel::displayActiveReservations() const {
    // TODO: Display all active reservations
    cout << "========== ACTIVE RESERVATIONS ==========" << endl;
}

void Hotel::displayFinancialSummary() const {
    // TODO: Display financial report
    // Show total revenue, occupancy rate, payroll, etc.
    cout << "========== FINANCIAL SUMMARY ==========" << endl;
    cout << "Hotel: " << getName() << endl;
    // Add more details
}