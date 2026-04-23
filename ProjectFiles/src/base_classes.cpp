#include "base_classes.h"
#include <cstring>
#include <iomanip>
#include <ctime>

// ============================================================================
// ASSIGNMENT: Hotel Management System - Basic Classes
// Week: V
// NAME: Gavin W Bowen
// COURSE: ECEN 156
// DATE:  2026/02/17
// ============================================================================

// ============================================================================
// PERSON CLASS IMPLEMENTATION
// ============================================================================

Person::Person(){
    id = 0;
    strcpy(name, "");
    strcpy(phone, "");
    strcpy(email, "");
}

Person::Person(int id, const char* name, const char* phone, const char* email) {
    this->id = id;
    strcpy(this->name, name);
    strcpy(this->phone, phone);
    strcpy(this->email, email);
}

Person::~Person() {
}

int Person::getId() const {
    return id;
}

const char* Person::getName() const {
    return name;
}

const char* Person::getPhone() const {
    return phone;
}

const char* Person::getEmail() const {
    return email;
}

void Person::setName(const char* name) {
    strcpy(this->name, name);
}

void Person::setPhone(const char* phone) {
    strcpy(this->phone, phone);
}

void Person::setEmail(const char* email) {
    strcpy(this->email, email);
}

void Person::display() const {
    cout <<"ID: "<<this->id<<" | Name: "<<this->name<<" | Phone: "<<this->phone<<" | Email: "<<this->email;
}

// ============================================================================
// ROOM BASE CLASS IMPLEMENTATION
// ============================================================================

Room::Room() {
    roomNumber = 0;
    floor = 1;
    isClean = true;
    isUnderMaintenance = false;
}

Room::Room(int roomNumber, int floor) {
    this->roomNumber = roomNumber;
    this->floor = roomNumber;
    isClean = true;
    isUnderMaintenance = false;
}

Room::~Room() {
}

int Room::getRoomNumber() const {
    return roomNumber;
}

int Room::getFloor() const {
    return floor;
}

bool Room::getIsClean() const {
    return isClean;
}

bool Room::getIsUnderMaintenance() const {
    return isUnderMaintenance;
}

void Room::setClean(bool clean) {
    this->isClean = isClean;}

void Room::setUnderMaintenance(bool maintenance) {
    this->isUnderMaintenance = isUnderMaintenance;
}

double Room::calculatePrice(int nights) const {
    double calPri = 0.0;
    calPri = getBasePrice() * nights;
    return calPri;
}

void Room::display() const {
    cout <<"Room "<<this->roomNumber<<" (Floor "<<this->floor<<") "<<getRoomType()<<endl;
    cout <<"\tStatus: "<<isVacant()<<" | Clean: "<<this->isClean<<" | Maintenance: "<<this->isUnderMaintenance<<endl;
    cout <<"\tPrice: $"<<getBasePrice()<<"/night | Max Occupancy: "<<getMaxOccupancy()<<endl;
    cout <<"\tAmenities: "<<getAmenities()<<endl;
}

// ============================================================================
// PAYMENT BASE CLASS IMPLEMENTATION
// ============================================================================

Payment::Payment() {
    paymentId = 0;
    amount = 0.0;
    isProcessed = false;
    strcpy(timestamp, "");
}

Payment::Payment(int paymentId, double amount) {
    this->paymentId = paymentId;
    this->amount = amount;
    this->isProcessed = false;
    strcpy(this->timestamp, timestamp);
}

Payment::~Payment() {
}

int Payment::getPaymentId() const {
    return paymentId;
}

double Payment::getAmount() const {
    return amount;
}

bool Payment::getIsProcessed() const {
    return isProcessed;
}

const char* Payment::getTimestamp() const {
    return timestamp;
}

double Payment::getTransactionFee() const {
    return 0.0;
}