#include "base_classes.h"
#include <cstring>
#include <iomanip>
#include <ctime>

// ============================================================================
//  NAME:
//  ASSIGNMENT: Hotel Management System - Week 6: Derived Classes
//  DATE:
// ============================================================================

// ============================================================================
// PERSON CLASS IMPLEMENTATION
// ============================================================================

Person::Person() {
    // TODO: Initialize all member variables to default values
    // - id should be 0
    // - name, phone, email should be empty strings (use strcpy)
}

Person::Person(int id, const char* name, const char* phone, const char* email) {
    // TODO: Initialize all member variables with the provided parameters
    // - Use 'this->' to distinguish between parameters and member variables
    // - Use strcpy() to copy C-strings
}

Person::~Person() {
    // Virtual destructor - no dynamic memory to free
}

int Person::getId() const {
    // TODO: Return the person's id
}

const char* Person::getName() const {
    // TODO: Return the person's name
}

const char* Person::getPhone() const {
    // TODO: Return the person's phone number
}

const char* Person::getEmail() const {
    // TODO: Return the person's email
}

void Person::setName(const char* name) {
    // TODO: Copy the provided name to this->name using strcpy
}

void Person::setPhone(const char* phone) {
    // TODO: Copy the provided phone to this->phone using strcpy
}

void Person::setEmail(const char* email) {
    // TODO: Copy the provided email to this->email using strcpy
}

void Person::display() const {
    // TODO: Display person information in the following format:
    // "ID: [id] | Name: [name] | Phone: [phone] | Email: [email]"
    // Note: Do not add endl at the end
}

// ============================================================================
// ROOM BASE CLASS IMPLEMENTATION
// ============================================================================

Room::Room() {
    // TODO: Initialize all member variables to default values
    // - roomNumber should be 0
    // - floor should be 1
    // - isClean should be true
    // - isUnderMaintenance should be false
}

Room::Room(int roomNumber, int floor) {
    // TODO: Initialize member variables
    // - Set roomNumber and floor from parameters
    // - Set isClean to true
    // - Set isUnderMaintenance to false
}

Room::~Room() {
    // Virtual destructor - no dynamic memory to free in base class
}

int Room::getRoomNumber() const {
    // TODO: Return the room number
}

int Room::getFloor() const {
    // TODO: Return the floor number
}

bool Room::getIsClean() const {
    // TODO: Return whether the room is clean
}

bool Room::getIsUnderMaintenance() const {
    // TODO: Return whether the room is under maintenance
}

void Room::setClean(bool clean) {
    // TODO: Set the isClean member variable
}

void Room::setUnderMaintenance(bool maintenance) {
    // TODO: Set the isUnderMaintenance member variable
}

double Room::calculatePrice(int nights) const {
    // TODO: Calculate and return the total price for the given number of nights
    // Hint: Use getBasePrice() * nights
}

void Room::display() const {
    // TODO: Display room information in the following format:
    // Line 1: "Room [roomNumber] (Floor [floor]) - [getRoomType()]"
    // Line 2: "  Status: [Vacant/Occupied] | Clean: [Yes/No] | Maintenance: [Yes/No]"
    // Line 3: "  Price: $[getBasePrice()]/night | Max Occupancy: [getMaxOccupancy()]"
    // Line 4: "  Amenities: [getAmenities()]"
    // 
    // Hints:
    // - Use isVacant() to check if room is vacant
    // - Use fixed and setprecision(2) for price formatting
    // - Use ternary operator (condition ? "Yes" : "No") for boolean displays
}

// ============================================================================
// PAYMENT BASE CLASS IMPLEMENTATION
// ============================================================================

Payment::Payment() {
    // TODO: Initialize all member variables to default values
    // - paymentId should be 0
    // - amount should be 0.0
    // - isProcessed should be false
    // - timestamp should be "Not Set" (use strcpy)
}

Payment::Payment(int paymentId, double amount) {
    // TODO: Initialize member variables
    // - Set paymentId and amount from parameters
    // - Set isProcessed to false
    // - Set timestamp to current time using the following code:
    //   time_t now = time(0);
    //   strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M", localtime(&now));
}

Payment::~Payment() {
    // Virtual destructor
}

int Payment::getPaymentId() const {
    // TODO: Return the payment ID
}

double Payment::getAmount() const {
    // TODO: Return the payment amount
}

bool Payment::getIsProcessed() const {
    // TODO: Return whether the payment has been processed
}

const char* Payment::getTimestamp() const {
    // TODO: Return the timestamp
}

double Payment::getTransactionFee() const {
    // TODO: Return the default transaction fee (0.0)
}