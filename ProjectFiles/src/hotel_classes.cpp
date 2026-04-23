#include "hotel_classes.h"
#include <cstring>
#include <iomanip>

// ============================================================================
// ASSIGNMENT: Hotel Management System - Derived Classes
// Week: VI
// NAME: Gavin W Bowen
// COURSE: ECEN 156
// DATE:  2026/02/24
// ============================================================================

// ============================================================================
// GUEST CLASS IMPLEMENTATION
// ============================================================================

Guest::Guest() : Person() {// Initialize Guest-specific members
    loyaltyPoints = 0;
    isCheckedIn = false;
    totalStays = 0;
}

Guest::Guest(int id, const char* name, const char* phone, const char* email, int loyaltyPoints)
    : Person(id, name, phone, email) {// Initialize Guest-specific members
    this->loyaltyPoints = loyaltyPoints;
    this->isCheckedIn = false;
    this->totalStays = 0;
}

int Guest::getLoyaltyPoints() const {
    return this->loyaltyPoints;
}

bool Guest::getIsCheckedIn() const {
    return this->isCheckedIn;
}

int Guest::getTotalStays() const {
    return this->totalStays;
}

void Guest::setCheckedIn(bool status) {
    this->isCheckedIn = status;
}

void Guest::addLoyaltyPoints(int points) {
    if(points>0)
    {
        this->loyaltyPoints=this->loyaltyPoints+points;
    }
}

bool Guest::redeemPoints(int points) {// Redeem points if guest has enough
    bool redeem = false;
    if(points>0 && this->loyaltyPoints>=points)
    {
        this->loyaltyPoints = this->loyaltyPoints - points;
        redeem = true;
    }
    if(points<=0)
    {
        redeem = false;
    }
    return redeem;
}

const char* Guest::getLoyaltyTier() const {// Return tier based on points
    if(loyaltyPoints>=0 && loyaltyPoints<= 999)
    {
        return "Bronze";
    }
    if(loyaltyPoints>=1000 && loyaltyPoints<= 4999)
    {
        return "Silver";
    }
    if(loyaltyPoints>=5000 && loyaltyPoints<= 9999)
    {
        return "Gold";
    }
    if(loyaltyPoints>=10000)
    {
        return "Platinum";
    }
    
    return nullptr;
}

double Guest::getTierDiscount() const {// Return discount based on tier
if(loyaltyPoints>=0 && loyaltyPoints<= 999)
    {
        return 0.0;
    }
    if(loyaltyPoints>=1000 && loyaltyPoints<= 4999)
    {
        return 0.05;
    }
    if(loyaltyPoints>=5000 && loyaltyPoints<= 9999)
    {
        return 0.10;
    }
    if(loyaltyPoints>=10000)
    {
        return 0.15;
    }

    return 0;
}

void Guest::recordStay() {
    this->totalStays+=1;
}

void Guest::display() const {
    // TODO: Call Person::display() and add guest info
    // "Loyalty: [points] pts ([tier]) | Stays: [total] | Status: [Checked In/Checked Out]"
}

// ============================================================================
// EMPLOYEE CLASS IMPLEMENTATION
// ============================================================================

Employee::Employee() : Person() {// Initialize with defaults
    strcpy(position, "");
    hourlyWage = 0.0;
    hoursWorked = 0;
    
}

Employee::Employee(int id, const char* name, const char* phone, const char* email,
                   const char* position, double hourlyWage)// Initialize Employee-specific members
    : Person(id, name, phone, email) {
        strcpy(this->position, position);
        this->hourlyWage = hourlyWage;
        this->hoursWorked = 0.0;
}

const char* Employee::getPosition() const {
    return position;
}

double Employee::getHourlyWage() const {
    return hourlyWage;
}

int Employee::getHoursWorked() const {
    return hoursWorked;
}

void Employee::setPosition(const char* position) {
    strcpy(this->position, position);
}

void Employee::setHourlyWage(double wage) {
    if(this->hourlyWage>0 && wage>0)
    {
        this->hourlyWage=wage;
    }
}

void Employee::addHoursWorked(int hours) {
    if(hours>0)
    {
        this->hoursWorked=this->hoursWorked + hours;
    }
}

double Employee::calculatePay() const {// Calculate pay with overtime
    double wage = 0.0;
    if(this->hoursWorked>0.0 && this->hoursWorked<=40)
    {
        wage = this->hourlyWage * this->hoursWorked;
    }
    if(this->hoursWorked>40 && this->hoursWorked<100000)
    {
        wage = this->hourlyWage * 40 + (this->hoursWorked - 40) * this->hourlyWage * 1.5;
    }
    return wage;
}

void Employee::resetHours() {
    this->hoursWorked=0;
}

void Employee::display() const {
    // TODO: Call Person::display() and add employee info
    // "Position: [position] | Wage: $[wage]/hr | Hours: [hours] | Pay Due: $[pay]"
}

// ============================================================================
// STANDARDROOM CLASS IMPLEMENTATION
// ============================================================================

StandardRoom::StandardRoom() : Room() {// Initialize with defaults
    numBeds = 1;
    hasWindow = true;
    currentGuest = nullptr;
}

StandardRoom::StandardRoom(int roomNumber, int floor, int numBeds, bool hasWindow)
    : Room(roomNumber, floor) {// Initialize StandardRoom-specific members
        this->numBeds = numBeds;
        this->hasWindow = hasWindow;
        this->currentGuest = nullptr;
}

int StandardRoom::getNumBeds() const {
    return numBeds;
}

bool StandardRoom::getHasWindow() const {
    return hasWindow;
}

double StandardRoom::getBasePrice() const {
    double basePrice = 0.0;
    if(this->numBeds==1)
    {
        if(this->hasWindow==true)
        {
            basePrice = 89.0 + 10.0;
        }
        if(this->hasWindow==false)
        {
            basePrice = 89.0;
        }
    }
    if(this->numBeds==2)
    {
        if(this->hasWindow==true)
        {
            basePrice = 109.0 + 10.0;
        }
        if(this->hasWindow==false)
        {
            basePrice = 109.0;
        }
    }
    return basePrice;
}

const char* StandardRoom::getRoomType() const {
    return "Standard";
}

int StandardRoom::getMaxOccupancy() const {
    int numPeople;
    numPeople = numBeds * 2;
    return numPeople;
}

const char* StandardRoom::getAmenities() const {
    if(hasWindow==true)
    {
        return "WiFi, TV, Air Conditioning, Window View";
    }
    return "WiFi, TV, Air Conditioning";
}

Guest* StandardRoom::getCurrentGuest() const {
    return this->currentGuest;
}

bool StandardRoom::isVacant() const {
    bool vac = true;
    if(this->currentGuest!=nullptr)
    {
        vac = false;
    }
    return vac;
}

bool StandardRoom::checkIn(Guest* guest) {
    bool chkIn = false;
    if(guest!=nullptr)
    {
        if(this->isVacant()==true && this->isClean==true && this->isUnderMaintenance==false)
        {
            this->currentGuest=guest;
            guest->setCheckedIn(true);
            setClean(false);
            chkIn = true;
        }
    }
    return chkIn;
}

Guest* StandardRoom::checkOut() {
    Guest* chkOut = nullptr;
    if(this->currentGuest!=nullptr)
    {
        currentGuest->setCheckedIn(false);
        chkOut = getCurrentGuest();
        this->currentGuest = nullptr;
    }
    return chkOut;
}

void StandardRoom::display() const {
    // TODO: Call Room::display() and add Standard-specific info
    // "  Beds: [numBeds] | Window: [Yes/No]"
}

// ============================================================================
// DELUXEROOM CLASS IMPLEMENTATION
// ============================================================================

DeluxeRoom::DeluxeRoom() : Room() {// Initialize with defaults
    numBeds = 1;
    hasBalcony = false;
    hasMiniFridge = true;
    strcpy(viewType, "");
    currentGuest = nullptr;
}

DeluxeRoom::DeluxeRoom(int roomNumber, int floor, int numBeds,
                       bool hasBalcony, const char* viewType)
    : Room(roomNumber, floor) {// Initialize DeluxeRoom-specific members
    this->numBeds=numBeds;
    this->hasBalcony=hasBalcony;
    this->hasMiniFridge=true;
    strcpy(this->viewType, viewType);
    this->currentGuest=nullptr;
}

int DeluxeRoom::getNumBeds() const {
    return numBeds;
}

bool DeluxeRoom::getHasBalcony() const {
    return hasBalcony;
}

bool DeluxeRoom::getHasMiniFridge() const {
    return hasMiniFridge;
}

const char* DeluxeRoom::getViewType() const {
    return viewType;
}

double DeluxeRoom::getBasePrice() const {
    double basePrice = 0.0;
    if(numBeds==1)
    {
        if(hasBalcony==true)
        {
            if(strcmp(viewType, "Ocean")==0)
            {
                basePrice = 149.0 + 25.0 + 15.0;
            }
            if(strcmp(viewType, "Pool")==0)
            {
                basePrice = 149.0 + 25.0 + 10.0;
            }
            if(strcmp(viewType, "Ocean")!=0 && strcmp(viewType, "Pool")!=0)
            {
                basePrice = 149.0 + 25.0;
            }
        }
        if(hasBalcony!=true)
        {
            if(strcmp(viewType, "Ocean")==0)
            {
                basePrice = 149.0 + 15.0;
            }
            if(strcmp(viewType, "Pool")==0)
            {
                basePrice = 149.0 + 10.0;
            }
            if(strcmp(viewType, "Ocean")!=0 && strcmp(viewType, "Pool")!=0)
            {
                basePrice = 149.0;
            }
        }
    }
    if(numBeds==2)
    {
        if(hasBalcony==true)
        {
            if(strcmp(viewType, "Ocean")==0)
            {
                basePrice = 179.0 + 25.0 + 15.0;
            }
            if(strcmp(viewType, "Pool")==0)
            {
                basePrice = 179.0 + 25.0 + 10.0;
            }
            if(strcmp(viewType, "Ocean")!=0 && strcmp(viewType, "Pool")!=0)
            {
                basePrice = 179.0 + 25.0;
            }
        }
        if(hasBalcony!=true)
        {
            if(strcmp(viewType, "Ocean")==0)
            {
                basePrice = 179.0 + 15.0;
            }
            if(strcmp(viewType, "Pool")==0)
            {
                basePrice = 179.0 + 10.0;
            }
            if(strcmp(viewType, "Ocean")!=0 && strcmp(viewType, "Pool")!=0)
            {
                basePrice = 179.0;
            }
        }
    }
    return basePrice;
}

const char* DeluxeRoom::getRoomType() const {
    return "Deluxe";
}

int DeluxeRoom::getMaxOccupancy() const {
    int maxPeople = 0;
    maxPeople = numBeds + 2;
    return maxPeople;
}

const char* DeluxeRoom::getAmenities() const {
    if(hasBalcony==true)
    {
        return "WiFi, TV, AC, Mini-Fridge, [viewType] View, Private Balcony";
    }
    return "WiFi, TV, AC, Mini-Fridge, [viewType] View";
}

Guest* DeluxeRoom::getCurrentGuest() const {
    if(this->currentGuest!=nullptr)
    {
        return this->currentGuest;
    }
    return nullptr;
}

bool DeluxeRoom::isVacant() const {
    bool vacant = true;
    if(currentGuest!=nullptr)
    {
        vacant=false;
    }
    return vacant;
}

bool DeluxeRoom::checkIn(Guest* guest) {
    bool chkIn = false;
    if(this->currentGuest==nullptr)
    {
        if(this->isVacant()==true && isClean==true && isUnderMaintenance==false)
        {
            this->currentGuest = guest;
            guest->setCheckedIn(true);
            isClean=false;
            chkIn = true;
        }
        
    }
    return chkIn;
}

Guest* DeluxeRoom::checkOut() {
    Guest* chkOut = nullptr;
    if(this->currentGuest!=nullptr)
    {
        chkOut = this->currentGuest;
        this->currentGuest = nullptr;
    }
    return chkOut;
}

void DeluxeRoom::display() const {
    // TODO: Call Room::display() and add Deluxe-specific info
    // "  Beds: [numBeds] | Balcony: [Yes/No] | View: [viewType]"
}

// ============================================================================
// SUITE CLASS IMPLEMENTATION
// ============================================================================

Suite::Suite() : Room() {// Initialize with defaults
    numBedrooms = 1;
    squareFeet = 600;
    hasKitchen = false;
    hasLivingRoom = true;
    hasJacuzzi = false;
    currentGuest = nullptr;
}

Suite::Suite(int roomNumber, int floor, int numBedrooms, int squareFeet,
             bool hasKitchen, bool hasJacuzzi)
    : Room(roomNumber, floor) {// Initialize Suite-specific members
    this->numBedrooms=numBedrooms;
    this->squareFeet=squareFeet;
    this->hasKitchen=hasKitchen;
    this->hasLivingRoom=true;
    this->hasJacuzzi=hasJacuzzi;
    this->currentGuest=nullptr;
}

int Suite::getNumBedrooms() const {
    return numBedrooms;
}

bool Suite::getHasKitchen() const {
    return hasKitchen;
}

bool Suite::getHasLivingRoom() const {
    return hasLivingRoom;
}

bool Suite::getHasJacuzzi() const {
    return hasJacuzzi;
}

int Suite::getSquareFeet() const {
    return squareFeet;
}

double Suite::getBasePrice() const {
    double basePrice = 0.0;
    if(numBedrooms==0)
    {
        return 0.0;
    }
    if(numBedrooms==1)
    {
        if(hasKitchen==true && hasJacuzzi!=true)
        {
            basePrice = 299.0 + 75.0;
        }
        if(hasKitchen!=true && hasJacuzzi==true)
        {
            basePrice = 299.0 + 100.0;
        }
        if(hasKitchen==true && hasJacuzzi==true)
        {
            basePrice = 299.0 + 75.0 + 100.0;
        }
        if(hasKitchen!=true && hasJacuzzi!=true)
        {
            basePrice = 299.0;
        }
        
    }
        if(numBedrooms==2)
    {
        if(hasKitchen==true && hasJacuzzi!=true)
        {
            basePrice = 399.0 + 75.0;
        }
        if(hasKitchen!=true && hasJacuzzi==true)
        {
            basePrice = 399.0 + 100.0;
        }
        if(hasKitchen==true && hasJacuzzi==true)
        {
            basePrice = 399.0 + 75.0 + 100.0;
        }
        if(hasKitchen!=true && hasJacuzzi!=true)
        {
            basePrice = 399.0;
        }
        
    }
        if(numBedrooms>=3)
    {
        if(hasKitchen==true && hasJacuzzi!=true)
        {
            basePrice = 549.0 + 75.0;
        }
        if(hasKitchen!=true && hasJacuzzi==true)
        {
            basePrice = 549.0 + 100.0;
        }
        if(hasKitchen==true && hasJacuzzi==true)
        {
            basePrice = 549.0 + 75.0 + 100.0;
        }
        if(hasKitchen!=true && hasJacuzzi!=true)
        {
            basePrice = 549.0;
        }
    }
    return basePrice;
}

const char* Suite::getRoomType() const {
    return "Suite";
}

int Suite::getMaxOccupancy() const {
    int naxOcc = 0;
    naxOcc = (numBedrooms * 2) + 2;
    return naxOcc;
}

const char* Suite::getAmenities() const {
    if(hasKitchen==true)
    {
        return "WiFi, TV, AC, Living Room, Full Kitchen";
    }
    if(hasJacuzzi==true)
    {
        return "WiFi, TV, AC, Living Room, Jacuzzi";
    }
    if(hasKitchen==true && hasJacuzzi==true)
    {
        return "WiFi, TV, AC, Living Room, Full Kitchen, Jacuzzi";
    }
    return "WiFi, TV, AC, Living Room";
}

Guest* Suite::getCurrentGuest() const {
    if(this->currentGuest!=nullptr)
    {
        return this->currentGuest;
    }
    return nullptr;
}

bool Suite::isVacant() const {
    if(currentGuest!=nullptr)
    {
        return false;
    }
    return true;
}

bool Suite::checkIn(Guest* guest) {
    bool here = false;
    if(guest!=nullptr)
    {
        if(isVacant()==true && isClean==true && isUnderMaintenance!=true)
        {
            currentGuest=guest;
            guest->setCheckedIn(true);
            isVacant();
            this->isClean = false;
            here = true;
        }
    }
    return here;
}

Guest* Suite::checkOut() {
    Guest* gone;
    if(currentGuest!=nullptr)
    {
        gone = this->currentGuest;
        currentGuest->setCheckedIn(false);
        this->currentGuest = nullptr;
        return gone;
    }
    return nullptr;
}

double Suite::calculatePrice(int nights) const {
    double totPri = 0.0;
    totPri = getBasePrice() * nights;
    if(nights>=7)
    {
        totPri=totPri*0.9;
    }
    return totPri;
}

void Suite::display() const {
    // TODO: Call Room::display() and add Suite-specific info
    // "  Bedrooms: [num] | Square Feet: [sqft] | Kitchen: [Yes/No] | Jacuzzi: [Yes/No]"
}

// ============================================================================
// CASHPAYMENT CLASS IMPLEMENTATION
// ============================================================================

CashPayment::CashPayment() : Payment() {// Initialize with defaults
    amountTendered = 0.0;
    changeGiven = 0.0;
}

CashPayment::CashPayment(int paymentId, double amount, double amountTendered)
    : Payment(paymentId, amount) {// Initialize CashPayment-specific members
    this->amountTendered=amountTendered;
    this->changeGiven=0.0;
    
    // Calculate changeGiven (if amountTendered >= amount, else 0)
}

double CashPayment::getAmountTendered() const {
    return amountTendered;
}

double CashPayment::getChangeGiven() const {
    return changeGiven;
}

bool CashPayment::processPayment() {
    bool process = false;
    if(isProcessed==false)
    {
        if(amountTendered>=amount)
        {
            if(amountTendered>=amount)
            {
                isProcessed = true;
                process = true;
                changeGiven = amountTendered-amount;
            }
        }
    }
    return process;
}

bool CashPayment::refund() {
    bool rfnd = false;
    if(isProcessed!=false)
    {
        isProcessed = false;
        rfnd = true;
    }
    return rfnd;
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
    return 0.0;
}

// ============================================================================
// CREDITCARDPAYMENT CLASS IMPLEMENTATION
// ============================================================================

CreditCardPayment::CreditCardPayment() : Payment() {// Initialize with defaults
    isAuthorized = false;
    strcpy(cardHolderName, "");
    strcpy(cardNumber, "");
    strcpy(expirationDate, "");
}

CreditCardPayment::CreditCardPayment(int paymentId, double amount,
                                     const char* lastFourDigits,
                                     const char* cardHolderName,
                                     const char* expDate)
    : Payment(paymentId, amount) {// Initialize CreditCardPayment-specific members
    this->isAuthorized=false;
    strcpy(this->cardHolderName, cardHolderName);
    strcpy(this->cardNumber, lastFourDigits);
    strcpy(this->expirationDate, expDate);
}

const char* CreditCardPayment::getCardNumber() const {
    return this->cardNumber;
}

const char* CreditCardPayment::getCardHolderName() const {
    return this->cardHolderName;
}

bool CreditCardPayment::getIsAuthorized() const {
    return isAuthorized;
}

bool CreditCardPayment::processPayment() {
    bool procPay = false;
    if(isProcessed!=true)
    {
        isAuthorized = true;
        isProcessed = true;
        procPay = true;
    }
    return procPay;
}

bool CreditCardPayment::refund() {
    bool rfnd = false;
    if(isProcessed!=false)
    {
        isProcessed = false;
        isAuthorized = false;
        rfnd = true;
    }
    return rfnd;
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
    double fee = 0.0;
    fee = this->amount * 0.025;
    return fee;
}

// ============================================================================
// LOYALTYPOINTSPAYMENT CLASS IMPLEMENTATION
// ============================================================================

LoyaltyPointsPayment::LoyaltyPointsPayment() : Payment() {// Initialize with defaults
    guest = nullptr;
    pointsUsed = 0;
}

LoyaltyPointsPayment::LoyaltyPointsPayment(int paymentId, double amount, Guest* guest)
    : Payment(paymentId, amount) {
    this->guest=guest;
    this->pointsUsed=amount*POINTS_PER_DOLLAR;
}

int LoyaltyPointsPayment::getPointsUsed() const {
    return pointsUsed;
}

int LoyaltyPointsPayment::getPointsPerDollar() const {
    return POINTS_PER_DOLLAR;
}

bool LoyaltyPointsPayment::canAfford() const {
    bool canAff = false;
    if(this->guest!=nullptr)
    {
        if(this->guest->getLoyaltyPoints()>=pointsUsed)
        {
            canAff = true;

        }
    }
    return canAff;
}

bool LoyaltyPointsPayment::processPayment() {
    bool procPay = false;
    if(guest!=nullptr && isProcessed!=true && canAfford()!=false)
    {
        guest->redeemPoints(pointsUsed);
        isProcessed = true;
        procPay = true;
    }
    return procPay;
}

bool LoyaltyPointsPayment::refund() {
    bool rfnd = false;
    if(guest!=nullptr)
    {
        if(isProcessed!=false)
        {
            guest->addLoyaltyPoints(pointsUsed);
            isProcessed = false;
            rfnd = true;
        }
    }
    return rfnd;
}

const char* LoyaltyPointsPayment::getPaymentType() const {
    return "Loyalty Points";
}

void LoyaltyPointsPayment::display() const {
}

double LoyaltyPointsPayment::getTransactionFee() const {
    return 0.0;
}