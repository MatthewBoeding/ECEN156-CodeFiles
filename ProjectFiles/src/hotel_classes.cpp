#include "hotel_classes.h"
#include <cstring>
#include <iomanip>

// ============================================================================
//  NAME:
//  ASSIGNMENT: Hotel Management System - Week 6: Derived Classes
//  DATE:
// ============================================================================

// ============================================================================
// GUEST CLASS IMPLEMENTATION
// ============================================================================

Guest::Guest() : Person() {
    // TODO: Initialize Guest-specific members
    // loyaltyPoints = 0, isCheckedIn = false, totalStays = 0
}

Guest::Guest(int id, const char* name, const char* phone, const char* email, int loyaltyPoints)
    : Person(id, name, phone, email) {
    // TODO: Initialize Guest-specific members
    // Use the provided loyaltyPoints, isCheckedIn = false, totalStays = 0
}

int Guest::getLoyaltyPoints() const {
    return 0;  // TODO
}

bool Guest::getIsCheckedIn() const {
    return false;  // TODO
}

int Guest::getTotalStays() const {
    return 0;  // TODO
}

void Guest::setCheckedIn(bool status) {
    // TODO
}

void Guest::addLoyaltyPoints(int points) {
    // TODO: Add points to loyalty balance (only if points > 0)
}

bool Guest::redeemPoints(int points) {
    // TODO: Redeem points if guest has enough
    // Return true if successful, false if not enough points or invalid amount
    return false;
}

const char* Guest::getLoyaltyTier() const {
    // TODO: Return tier based on points
    // Bronze: 0-999, Silver: 1000-4999, Gold: 5000-9999, Platinum: 10000+
    return "Bronze";
}

double Guest::getTierDiscount() const {
    // TODO: Return discount based on tier
    // Bronze: 0%, Silver: 5%, Gold: 10%, Platinum: 15%
    return 0.0;
}

void Guest::recordStay() {
    // TODO: Increment totalStays
}

void Guest::display() const {
    // TODO: Call Person::display() and add guest info
    // "Loyalty: [points] pts ([tier]) | Stays: [total] | Status: [Checked In/Checked Out]"
}

// ============================================================================
// EMPLOYEE CLASS IMPLEMENTATION
// ============================================================================

Employee::Employee() : Person() {
    // TODO: Initialize with defaults
    // Empty position, hourlyWage = 0.0, hoursWorked = 0
}

Employee::Employee(int id, const char* name, const char* phone, const char* email,
                   const char* position, double hourlyWage)
    : Person(id, name, phone, email) {
    // TODO: Initialize Employee-specific members
}

const char* Employee::getPosition() const {
    return "";  // TODO
}

double Employee::getHourlyWage() const {
    return 0.0;  // TODO
}

int Employee::getHoursWorked() const {
    return 0;  // TODO
}

void Employee::setPosition(const char* position) {
    // TODO
}

void Employee::setHourlyWage(double wage) {
    // TODO: Only set if wage > 0
}

void Employee::addHoursWorked(int hours) {
    // TODO: Only add if hours > 0
}

double Employee::calculatePay() const {
    // TODO: Calculate pay with overtime
    // Regular pay for hours <= 40
    // Overtime (1.5x) for hours > 40
    return 0.0;
}

void Employee::resetHours() {
    // TODO: Set hoursWorked back to 0
}

void Employee::display() const {
    // TODO: Call Person::display() and add employee info
    // "Position: [position] | Wage: $[wage]/hr | Hours: [hours] | Pay Due: $[pay]"
}

// ============================================================================
// STANDARDROOM CLASS IMPLEMENTATION
// ============================================================================

StandardRoom::StandardRoom() : Room() {
    // TODO: Initialize with defaults
    // numBeds = 1, hasWindow = true, currentGuest = nullptr
}

StandardRoom::StandardRoom(int roomNumber, int floor, int numBeds, bool hasWindow)
    : Room(roomNumber, floor) {
    // TODO: Initialize StandardRoom-specific members
    // Don't forget: currentGuest = nullptr
}

int StandardRoom::getNumBeds() const {
    return 0;  // TODO
}

bool StandardRoom::getHasWindow() const {
    return false;  // TODO
}

double StandardRoom::getBasePrice() const {
    // TODO: Calculate base price
    // 1 bed: $89/night, 2 beds: $109/night
    // Add $10 if has window
    return 0.0;
}

const char* StandardRoom::getRoomType() const {
    return "Standard";
}

int StandardRoom::getMaxOccupancy() const {
    // TODO: 1 bed = 2 people, 2 beds = 4 people
    return 0;
}

const char* StandardRoom::getAmenities() const {
    // TODO: Return amenities string
    // "WiFi, TV, Air Conditioning" + ", Window View" if hasWindow
    return "";
}

Guest* StandardRoom::getCurrentGuest() const {
    return nullptr;  // TODO
}

bool StandardRoom::isVacant() const {
    // TODO: Return true if currentGuest is nullptr
    return true;
}

bool StandardRoom::checkIn(Guest* guest) {
    // TODO: Implement check-in logic
    // 1. Check if guest is not nullptr
    // 2. Check if room is vacant, clean, and not under maintenance
    // 3. Set currentGuest to guest
    // 4. Set guest's checkedIn status to true (guest->setCheckedIn(true))
    // 5. Mark room as not clean (setClean(false))
    // 6. Return true if successful, false otherwise
    return false;
}

Guest* StandardRoom::checkOut() {
    // TODO: Implement check-out logic
    // 1. If no guest, return nullptr
    // 2. Save current guest pointer
    // 3. Set guest's checkedIn status to false
    // 4. Set currentGuest to nullptr
    // 5. Return the saved guest pointer
    return nullptr;
}

void StandardRoom::display() const {
    // TODO: Call Room::display() and add Standard-specific info
    // "  Beds: [numBeds] | Window: [Yes/No]"
}

// ============================================================================
// DELUXEROOM CLASS IMPLEMENTATION
// ============================================================================

DeluxeRoom::DeluxeRoom() : Room() {
    // TODO: Initialize with defaults
    // numBeds = 1, hasBalcony = false, hasMiniFridge = true, 
    // viewType = "City", currentGuest = nullptr
}

DeluxeRoom::DeluxeRoom(int roomNumber, int floor, int numBeds,
                       bool hasBalcony, const char* viewType)
    : Room(roomNumber, floor) {
    // TODO: Initialize DeluxeRoom-specific members
    // hasMiniFridge is always true for deluxe rooms
    // Don't forget: currentGuest = nullptr
}

int DeluxeRoom::getNumBeds() const {
    return 0;  // TODO
}

bool DeluxeRoom::getHasBalcony() const {
    return false;  // TODO
}

bool DeluxeRoom::getHasMiniFridge() const {
    return false;  // TODO
}

const char* DeluxeRoom::getViewType() const {
    return "";  // TODO
}

double DeluxeRoom::getBasePrice() const {
    // TODO: Calculate base price
    // 1 bed: $149, 2 beds: $179
    // Add $25 if has balcony
    // Add $15 for Ocean view, $10 for Pool view
    return 0.0;
}

const char* DeluxeRoom::getRoomType() const {
    return "Deluxe";
}

int DeluxeRoom::getMaxOccupancy() const {
    // TODO: numBeds + 2 (e.g., 1 bed = 3 people, 2 beds = 4 people)
    return 0;
}

const char* DeluxeRoom::getAmenities() const {
    // TODO: Return amenities string
    // "WiFi, TV, AC, Mini-Fridge, [viewType] View"
    // Add ", Private Balcony" if hasBalcony
    return "";
}

Guest* DeluxeRoom::getCurrentGuest() const {
    return nullptr;  // TODO
}

bool DeluxeRoom::isVacant() const {
    // TODO: Return true if currentGuest is nullptr
    return true;
}

bool DeluxeRoom::checkIn(Guest* guest) {
    // TODO: Implement check-in logic (same as StandardRoom)
    // 1. Check if guest is not nullptr
    // 2. Check if room is vacant, clean, and not under maintenance
    // 3. Set currentGuest to guest
    // 4. Set guest's checkedIn status to true
    // 5. Mark room as not clean
    // 6. Return true if successful, false otherwise
    return false;
}

Guest* DeluxeRoom::checkOut() {
    // TODO: Implement check-out logic (same as StandardRoom)
    // 1. If no guest, return nullptr
    // 2. Save current guest pointer
    // 3. Set guest's checkedIn status to false
    // 4. Set currentGuest to nullptr
    // 5. Return the saved guest pointer
    return nullptr;
}

void DeluxeRoom::display() const {
    // TODO: Call Room::display() and add Deluxe-specific info
    // "  Beds: [numBeds] | Balcony: [Yes/No] | View: [viewType]"
}

// ============================================================================
// SUITE CLASS IMPLEMENTATION
// ============================================================================

Suite::Suite() : Room() {
    // TODO: Initialize with defaults
    // numBedrooms = 1, squareFeet = 600, hasKitchen = false, 
    // hasLivingRoom = true, hasJacuzzi = false, currentGuest = nullptr
}

Suite::Suite(int roomNumber, int floor, int numBedrooms, int squareFeet,
             bool hasKitchen, bool hasJacuzzi)
    : Room(roomNumber, floor) {
    // TODO: Initialize Suite-specific members
    // hasLivingRoom is always true for suites
    // Don't forget: currentGuest = nullptr
}

int Suite::getNumBedrooms() const {
    return 0;  // TODO
}

bool Suite::getHasKitchen() const {
    return false;  // TODO
}

bool Suite::getHasLivingRoom() const {
    return false;  // TODO
}

bool Suite::getHasJacuzzi() const {
    return false;  // TODO
}

int Suite::getSquareFeet() const {
    return 0;  // TODO
}

double Suite::getBasePrice() const {
    // TODO: Calculate base price
    // 1 bedroom: $299, 2 bedrooms: $399, 3+: $549
    // Add $75 if has kitchen
    // Add $100 if has jacuzzi
    return 0.0;
}

const char* Suite::getRoomType() const {
    return "Suite";
}

int Suite::getMaxOccupancy() const {
    // TODO: (numBedrooms * 2) + 2
    // e.g., 1 bedroom = 4 people, 2 bedrooms = 6 people
    return 0;
}

const char* Suite::getAmenities() const {
    // TODO: Return amenities string
    // "WiFi, TV, AC, Living Room"
    // Add ", Full Kitchen" if hasKitchen
    // Add ", Jacuzzi" if hasJacuzzi
    return "";
}

Guest* Suite::getCurrentGuest() const {
    return nullptr;  // TODO
}

bool Suite::isVacant() const {
    // TODO: Return true if currentGuest is nullptr
    return true;
}

bool Suite::checkIn(Guest* guest) {
    // TODO: Implement check-in logic (same as StandardRoom)
    // 1. Check if guest is not nullptr
    // 2. Check if room is vacant, clean, and not under maintenance
    // 3. Set currentGuest to guest
    // 4. Set guest's checkedIn status to true
    // 5. Mark room as not clean
    // 6. Return true if successful, false otherwise
    return false;
}

Guest* Suite::checkOut() {
    // TODO: Implement check-out logic (same as StandardRoom)
    // 1. If no guest, return nullptr
    // 2. Save current guest pointer
    // 3. Set guest's checkedIn status to false
    // 4. Set currentGuest to nullptr
    // 5. Return the saved guest pointer
    return nullptr;
}

double Suite::calculatePrice(int nights) const {
    // TODO: Override to add extended stay discount
    // Get base total: getBasePrice() * nights
    // If nights >= 7, apply 10% discount (multiply by 0.9)
    return 0.0;
}

void Suite::display() const {
    // TODO: Call Room::display() and add Suite-specific info
    // "  Bedrooms: [num] | Square Feet: [sqft] | Kitchen: [Yes/No] | Jacuzzi: [Yes/No]"
}

// ============================================================================
// CASHPAYMENT CLASS IMPLEMENTATION
// ============================================================================

CashPayment::CashPayment() : Payment() {
    // TODO: Initialize with defaults
    // amountTendered = 0.0, changeGiven = 0.0
}

CashPayment::CashPayment(int paymentId, double amount, double amountTendered)
    : Payment(paymentId, amount) {
    // TODO: Initialize CashPayment-specific members
    // Calculate changeGiven (if amountTendered >= amount, else 0)
}

double CashPayment::getAmountTendered() const {
    return 0.0;  // TODO
}

double CashPayment::getChangeGiven() const {
    return 0.0;  // TODO
}

bool CashPayment::processPayment() {
    // TODO: Process the payment
    // 1. Check if already processed (return false)
    // 2. Check if amountTendered >= amount (return false if not)
    // 3. Set isProcessed to true
    // 4. Return true
    return false;
}

bool CashPayment::refund() {
    // TODO: Refund the payment
    // 1. Check if payment was processed (return false if not)
    // 2. Set isProcessed to false
    // 3. Return true
    return false;
}

const char* CashPayment::getPaymentType() const {
    return "Cash";
}

void CashPayment::display() const {
    // TODO: Display cash payment info
    // "CASH PAYMENT #[id]"
    // "  Amount: $[amount] | Tendered: $[tendered] | Change: $[change]"
    // "  Status: [Processed/Pending]"
}

double CashPayment::getTransactionFee() const {
    return 0.0;  // Cash has no fees
}

// ============================================================================
// CREDITCARDPAYMENT CLASS IMPLEMENTATION
// ============================================================================

CreditCardPayment::CreditCardPayment() : Payment() {
    // TODO: Initialize with defaults
    // Empty strings, isAuthorized = false
}

CreditCardPayment::CreditCardPayment(int paymentId, double amount,
                                     const char* lastFourDigits,
                                     const char* cardHolderName,
                                     const char* expDate)
    : Payment(paymentId, amount) {
    // TODO: Initialize CreditCardPayment-specific members
    // isAuthorized = false
}

const char* CreditCardPayment::getCardNumber() const {
    return "";  // TODO
}

const char* CreditCardPayment::getCardHolderName() const {
    return "";  // TODO
}

bool CreditCardPayment::getIsAuthorized() const {
    return false;  // TODO
}

bool CreditCardPayment::processPayment() {
    // TODO: Process the payment
    // 1. Check if already processed (return false)
    // 2. Set isAuthorized to true
    // 3. Set isProcessed to true
    // 4. Return true
    return false;
}

bool CreditCardPayment::refund() {
    // TODO: Refund the payment
    // 1. Check if payment was processed (return false if not)
    // 2. Set isProcessed to false
    // 3. Set isAuthorized to false
    // 4. Return true
    return false;
}

const char* CreditCardPayment::getPaymentType() const {
    return "Credit Card";
}

void CreditCardPayment::display() const {
    // TODO: Display credit card payment info
    // "CREDIT CARD PAYMENT #[id]"
    // "  Card: ****-****-****-[last4] | Holder: [name]"
    // "  Amount: $[amount] + $[fee] fee = $[total]"
    // "  Status: [Processed/Pending] | Authorized: [Yes/No]"
}

double CreditCardPayment::getTransactionFee() const {
    // TODO: Return 2.5% of amount
    return 0.0;
}

// ============================================================================
// LOYALTYPOINTSPAYMENT CLASS IMPLEMENTATION
// ============================================================================

LoyaltyPointsPayment::LoyaltyPointsPayment() : Payment() {
    // TODO: Initialize with defaults
    // guest = nullptr, pointsUsed = 0
}

LoyaltyPointsPayment::LoyaltyPointsPayment(int paymentId, double amount, Guest* guest)
    : Payment(paymentId, amount) {
    // TODO: Initialize LoyaltyPointsPayment-specific members
    // Calculate pointsUsed: amount * POINTS_PER_DOLLAR
}

int LoyaltyPointsPayment::getPointsUsed() const {
    return 0;  // TODO
}

int LoyaltyPointsPayment::getPointsPerDollar() const {
    return POINTS_PER_DOLLAR;
}

bool LoyaltyPointsPayment::canAfford() const {
    // TODO: Check if guest has enough points
    // Return false if guest is nullptr
    return false;
}

bool LoyaltyPointsPayment::processPayment() {
    // TODO: Process the payment
    // 1. Check if already processed (return false)
    // 2. Check if can afford (return false)
    // 3. Redeem points from guest (use guest->redeemPoints())
    // 4. If redeem fails, return false
    // 5. Set isProcessed to true
    // 6. Return true
    return false;
}

bool LoyaltyPointsPayment::refund() {
    // TODO: Refund the payment
    // 1. Check if payment was processed (return false if not)
    // 2. Add points back to guest (if guest not nullptr)
    // 3. Set isProcessed to false
    // 4. Return true
    return false;
}

const char* LoyaltyPointsPayment::getPaymentType() const {
    return "Loyalty Points";
}

void LoyaltyPointsPayment::display() const {
    // TODO: Display loyalty points payment info
    // "LOYALTY POINTS PAYMENT #[id]"
    // "  Guest: [name]" (if guest not nullptr)
    // "  Amount: $[amount] ([points] points)"
    // "  Rate: [POINTS_PER_DOLLAR] points per dollar"
    // "  Status: [Processed/Pending]"
}

double LoyaltyPointsPayment::getTransactionFee() const {
    return 0.0;  // No fees for loyalty points
}