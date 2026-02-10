#ifndef BASE_CLASSES_H
#define BASE_CLASSES_H

#include <iostream>
#include <cstring>
using namespace std;

// ============================================================================
// HOTEL MANAGEMENT SYSTEM - Week 5: Base Classes
// Object-Oriented Programming with Classes and Encapsulation
//
// This file contains the base classes that form the foundation of the system:
// - Person: Base class for all people in the system
// - Room: Abstract base class for all room types
// - Payment: Abstract base class for all payment methods
//
// Focus: Encapsulation, abstract classes, virtual functions, pure virtual functions
// ============================================================================

// ============================================================================
// PERSON BASE CLASS
// ============================================================================

// ----------------------------------------------------------------------------
// Person (Base Class)
// Encapsulates common attributes for all people in the system
// This is a concrete base class that can be instantiated
// ----------------------------------------------------------------------------
class Person {
private:
    int id;
    char name[50];
    char phone[15];
    char email[50];

public:
    // Constructors
    Person();
    Person(int id, const char* name, const char* phone, const char* email);
    
    // Virtual destructor (good practice for base classes)
    virtual ~Person();
    
    // Getters
    int getId() const;
    const char* getName() const;
    const char* getPhone() const;
    const char* getEmail() const;
    
    // Setters
    void setName(const char* name);
    void setPhone(const char* phone);
    void setEmail(const char* email);
    
    // Virtual display method (can be overridden by derived classes)
    virtual void display() const;
};

// ============================================================================
// ROOM BASE CLASS (ABSTRACT)
// ============================================================================

// Forward declaration (Guest is defined in hotel_classes.h)
class Guest;

// ----------------------------------------------------------------------------
// Room (Abstract Base Class)
// Defines the interface for all room types
// This is an abstract class - cannot be instantiated directly
// Pure virtual functions (= 0) must be implemented by derived classes
// ----------------------------------------------------------------------------
class Room {
protected:
    int roomNumber;
    int floor;
    bool isClean;
    bool isUnderMaintenance;

public:
    // Constructor & Virtual Destructor
    Room();
    Room(int roomNumber, int floor);
    virtual ~Room();
    
    // Getters
    int getRoomNumber() const;
    int getFloor() const;
    bool getIsClean() const;
    bool getIsUnderMaintenance() const;
    
    // Setters
    void setClean(bool clean);
    void setUnderMaintenance(bool maintenance);
    
    // Pure virtual methods - MUST be implemented by derived classes
    // The = 0 makes this an abstract class
    virtual double getBasePrice() const = 0;
    virtual const char* getRoomType() const = 0;
    virtual int getMaxOccupancy() const = 0;
    virtual const char* getAmenities() const = 0;
    
    // Guest management - must be implemented by derived classes
    virtual Guest* getCurrentGuest() const = 0;
    virtual bool isVacant() const = 0;
    virtual bool checkIn(Guest* guest) = 0;
    virtual Guest* checkOut() = 0;
    
    // Virtual methods with default implementations
    // Derived classes can override these if needed
    virtual double calculatePrice(int nights) const;
    virtual void display() const;
};

// ============================================================================
// PAYMENT BASE CLASS (ABSTRACT)
// ============================================================================

// ----------------------------------------------------------------------------
// Payment (Abstract Base Class)
// Defines interface for all payment methods
// This is an abstract class - cannot be instantiated directly
// ----------------------------------------------------------------------------
class Payment {
protected:
    int paymentId;
    double amount;
    bool isProcessed;
    char timestamp[20];

public:
    // Constructors
    Payment();
    Payment(int paymentId, double amount);
    
    // Virtual destructor (important for polymorphic deletion)
    virtual ~Payment();
    
    // Getters
    int getPaymentId() const;
    double getAmount() const;
    bool getIsProcessed() const;
    const char* getTimestamp() const;
    
    // Pure virtual methods - MUST be implemented by derived classes
    virtual bool processPayment() = 0;
    virtual bool refund() = 0;
    virtual const char* getPaymentType() const = 0;
    virtual void display() const = 0;
    
    // Virtual method with default implementation
    // Most payment types have no fees, but some (like credit cards) do
    virtual double getTransactionFee() const;
};

#endif // BASE_CLASSES_H
