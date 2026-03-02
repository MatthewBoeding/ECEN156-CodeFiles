#ifndef RESERVATION_LIST_H
#define RESERVATION_LIST_H

#include "system_classes.h"

// ============================================================================
// HOTEL MANAGEMENT SYSTEM - Reservation Linked List
//
// This file contains a doubly linked list for managing Reservation objects.
// Replaces the fixed Reservation* reservations[500] array in Hotel with an
// unbounded, dynamically linked structure.
//
// ReservationNode: A single node holding one Reservation* and prev/next links
// ReservationList: The full doubly linked list with insert, remove, search,
//                  traversal, and aggregate operations
// ============================================================================

// ============================================================================
// RESERVATION NODE
// Each node holds a pointer to a Reservation and links to its neighbors
// ============================================================================

struct ReservationNode {
    Reservation* reservation;   // Polymorphic - owns the Reservation object
    ReservationNode* next;
    ReservationNode* prev;

    // Constructors
    ReservationNode();
    ReservationNode(Reservation* reservation);
};

// ============================================================================
// RESERVATION LIST
// Doubly linked list that manages a collection of Reservation objects.
// Insertion is at the tail (chronological order).
// Owns the ReservationNode objects it creates, but NOT the Reservation objects
// themselves - callers are responsible for managing Reservation lifetimes
// unless deleteOnRemove is used.
// ============================================================================

class ReservationList {
private:
    ReservationNode* head;
    ReservationNode* tail;
    int size;

public:
    // Constructor & Destructor
    // Destructor deletes all nodes and the Reservation objects they point to
    ReservationList();
    ~ReservationList();

    // ==================== ACCESSORS ====================

    ReservationNode* getHead() const;
    ReservationNode* getTail() const;
    int getSize() const;
    bool isEmpty() const;

    // ==================== INSERTION ====================

    // Insert a reservation at the tail (chronological order)
    // Does nothing if reservation is nullptr
    void insert(Reservation* reservation);

    // ==================== SEARCH ====================

    // Find a reservation by its ID - returns nullptr if not found
    Reservation* findById(int reservationId) const;

    // Find all reservations for a given guest
    // Fills result[] and returns count found (up to maxSize)
    int findByGuest(const Guest* guest, Reservation* result[], int maxSize) const;

    // Find all currently active reservations
    // Fills result[] and returns count found (up to maxSize)
    int findActive(Reservation* result[], int maxSize) const;

    // Find all checked-in reservations
    int findCheckedIn(Reservation* result[], int maxSize) const;

    // ==================== REMOVAL ====================

    // Remove the node with the given reservation ID
    // Deletes the node but does NOT delete the Reservation object
    // Returns true if found and removed, false if not found
    bool removeById(int reservationId);

    // Remove and DELETE the Reservation object as well
    // Use this when the list owns the reservation's lifetime
    bool deleteById(int reservationId);

    // ==================== AGGREGATE OPERATIONS ====================

    // Sum totalCost of all inactive, payment-processed reservations
    // (i.e. completed stays - mirrors Hotel::calculateTotalRevenue logic)
    double calculateTotalRevenue() const;

    // Sum totalCost of completed reservations for a specific room type
    // Uses polymorphic room->getRoomType() to filter
    double calculateRevenueByRoomType(const char* type) const;

    // Count active reservations
    int countActive() const;

    // ==================== DISPLAY ====================

    // Print all reservations in order (head to tail)
    void displayAll() const;

    // Print only active reservations
    void displayActive() const;
};

#endif // RESERVATION_LIST_H
