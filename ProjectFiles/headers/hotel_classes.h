#ifndef HOTEL_CLASSES_H
#define HOTEL_CLASSES_H

#include "base_classes.h"

// ============================================================================
// HOTEL MANAGEMENT SYSTEM - Week 6: Derived Classes & Inheritance
// 
// This file contains derived classes that inherit from the base classes:
// - Guest, Employee: Derived from Person
// - StandardRoom, DeluxeRoom, Suite: Derived from Room
// - CashPayment, CreditCardPayment, LoyaltyPointsPayment: Derived from Payment
//
// Focus: Inheritance, constructor chaining, implementing pure virtual functions
// ============================================================================

// ============================================================================
// PERSON DERIVED CLASSES
// ============================================================================

// ----------------------------------------------------------------------------
// Guest (Derived from Person)
// Represents a hotel guest with loyalty program
// ----------------------------------------------------------------------------
class Guest : public Person {
private:
    int loyaltyPoints;
    bool isCheckedIn;
    int totalStays;

public:
    // Constructors
    Guest();
    Guest(int id, const char* name, const char* phone, const char* email,
          int loyaltyPoints = 0);
    
    // Getters
    int getLoyaltyPoints() const;
    bool getIsCheckedIn() const;
    int getTotalStays() const;
    
    // Setters
    void setCheckedIn(bool status);
    
    // Loyalty program methods
    void addLoyaltyPoints(int points);
    bool redeemPoints(int points);
    
    // Get loyalty tier based on points
    // Bronze: 0-999, Silver: 1000-4999, Gold: 5000-9999, Platinum: 10000+
    const char* getLoyaltyTier() const;
    
    // Get discount percentage based on tier
    double getTierDiscount() const;
    
    // Record a completed stay
    void recordStay();
    
    // Override display
    void display() const override;
};

// ----------------------------------------------------------------------------
// Employee (Derived from Person)
// Represents hotel staff members
// ----------------------------------------------------------------------------
class Employee : public Person {
private:
    char position[30];
    double hourlyWage;
    int hoursWorked;

public:
    // Constructors
    Employee();
    Employee(int id, const char* name, const char* phone, const char* email,
             const char* position, double hourlyWage);
    
    // Getters
    const char* getPosition() const;
    double getHourlyWage() const;
    int getHoursWorked() const;
    
    // Setters
    void setPosition(const char* position);
    void setHourlyWage(double wage);
    
    // Work tracking
    void addHoursWorked(int hours);
    double calculatePay() const;
    void resetHours();
    
    // Override display
    void display() const override;
};

// ============================================================================
// ROOM DERIVED CLASSES
// ============================================================================

// ----------------------------------------------------------------------------
// StandardRoom (Derived from Room)
// Basic room with essential amenities
// ----------------------------------------------------------------------------
class StandardRoom : public Room {
private:
    int numBeds;            // 1 or 2
    bool hasWindow;
    Guest* currentGuest;    // Guest management moved to derived class

public:
    StandardRoom();
    StandardRoom(int roomNumber, int floor, int numBeds, bool hasWindow);
    
    // Getters
    int getNumBeds() const;
    bool getHasWindow() const;
    
    // Override pure virtual methods from Room
    double getBasePrice() const override;
    const char* getRoomType() const override;
    int getMaxOccupancy() const override;
    const char* getAmenities() const override;
    
    // Guest management - implement pure virtual from base
    Guest* getCurrentGuest() const override;
    bool isVacant() const override;
    bool checkIn(Guest* guest) override;
    Guest* checkOut() override;
    
    // Override display
    void display() const override;
};

// ----------------------------------------------------------------------------
// DeluxeRoom (Derived from Room)
// Upgraded room with additional features
// ----------------------------------------------------------------------------
class DeluxeRoom : public Room {
private:
    int numBeds;
    bool hasBalcony;
    bool hasMiniFridge;
    char viewType[20];      // "City", "Pool", "Ocean", "Garden", etc.
    Guest* currentGuest;    // Guest management moved to derived class

public:
    DeluxeRoom();
    DeluxeRoom(int roomNumber, int floor, int numBeds, 
               bool hasBalcony, const char* viewType);
    
    // Getters
    int getNumBeds() const;
    bool getHasBalcony() const;
    bool getHasMiniFridge() const;
    const char* getViewType() const;
    
    // Override pure virtual methods from Room
    double getBasePrice() const override;
    const char* getRoomType() const override;
    int getMaxOccupancy() const override;
    const char* getAmenities() const override;
    
    // Guest management - implement pure virtual from base
    Guest* getCurrentGuest() const override;
    bool isVacant() const override;
    bool checkIn(Guest* guest) override;
    Guest* checkOut() override;
    
    // Override display
    void display() const override;
};

// ----------------------------------------------------------------------------
// Suite (Derived from Room)
// Premium room with luxury amenities
// ----------------------------------------------------------------------------
class Suite : public Room {
private:
    int numBedrooms;
    bool hasKitchen;
    bool hasLivingRoom;
    bool hasJacuzzi;
    int squareFeet;
    Guest* currentGuest;    // Guest management moved to derived class

public:
    Suite();
    Suite(int roomNumber, int floor, int numBedrooms, int squareFeet,
          bool hasKitchen, bool hasJacuzzi);
    
    // Getters
    int getNumBedrooms() const;
    bool getHasKitchen() const;
    bool getHasLivingRoom() const;
    bool getHasJacuzzi() const;
    int getSquareFeet() const;
    
    // Override pure virtual methods from Room
    double getBasePrice() const override;
    const char* getRoomType() const override;
    int getMaxOccupancy() const override;
    const char* getAmenities() const override;
    
    // Guest management - implement pure virtual from base
    Guest* getCurrentGuest() const override;
    bool isVacant() const override;
    bool checkIn(Guest* guest) override;
    Guest* checkOut() override;
    
    // Suites have special pricing for extended stays
    double calculatePrice(int nights) const override;
    
    // Override display
    void display() const override;
};

// ============================================================================
// PAYMENT DERIVED CLASSES
// ============================================================================

// ----------------------------------------------------------------------------
// CashPayment (Derived from Payment)
// ----------------------------------------------------------------------------
class CashPayment : public Payment {
private:
    double amountTendered;
    double changeGiven;

public:
    CashPayment();
    CashPayment(int paymentId, double amount, double amountTendered);
    
    // Getters
    double getAmountTendered() const;
    double getChangeGiven() const;
    
    // Override pure virtual methods from Payment
    bool processPayment() override;
    bool refund() override;
    const char* getPaymentType() const override;
    void display() const override;
    
    // Override transaction fee (cash has no fee)
    double getTransactionFee() const override;
};

// ----------------------------------------------------------------------------
// CreditCardPayment (Derived from Payment)
// ----------------------------------------------------------------------------
class CreditCardPayment : public Payment {
private:
    char cardNumber[20];        // Last 4 digits only for security
    char cardHolderName[50];
    char expirationDate[6];     // MM/YY
    bool isAuthorized;

public:
    CreditCardPayment();
    CreditCardPayment(int paymentId, double amount, const char* lastFourDigits,
                      const char* cardHolderName, const char* expDate);
    
    // Getters
    const char* getCardNumber() const;
    const char* getCardHolderName() const;
    bool getIsAuthorized() const;
    
    // Override pure virtual methods from Payment
    bool processPayment() override;
    bool refund() override;
    const char* getPaymentType() const override;
    void display() const override;
    
    // Override transaction fee (credit cards charge 2.5%)
    double getTransactionFee() const override;
};

// ----------------------------------------------------------------------------
// LoyaltyPointsPayment (Derived from Payment)
// Pay using accumulated loyalty points
// ----------------------------------------------------------------------------
class LoyaltyPointsPayment : public Payment {
private:
    Guest* guest;
    int pointsUsed;
    static const int POINTS_PER_DOLLAR = 100;  // 100 points = $1

public:
    LoyaltyPointsPayment();
    LoyaltyPointsPayment(int paymentId, double amount, Guest* guest);
    
    // Getters
    int getPointsUsed() const;
    int getPointsPerDollar() const;
    
    // Check if guest has enough points
    bool canAfford() const;
    
    // Override pure virtual methods from Payment
    bool processPayment() override;
    bool refund() override;
    const char* getPaymentType() const override;
    void display() const override;
    
    // Override transaction fee (loyalty points have no fee)
    double getTransactionFee() const override;
};

#endif // HOTEL_CLASSES_H
