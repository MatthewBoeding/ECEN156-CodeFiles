// ============================================================================
// Week 6 In-Class Lecture: Polymorphism and Abstract Classes
// 
// Today we'll learn:
// 1. What polymorphism means and why it's powerful
// 2. Virtual functions and dynamic binding
// 3. Abstract classes and pure virtual functions
// 4. Polymorphic arrays (base class pointers to derived objects)
// 5. Virtual destructors (why they're essential)
// 6. Building a complete polymorphic system
//
// We'll build a VEHICLE RENTAL SYSTEM (different from your Hotel assignment!)
// ============================================================================

#include <iostream>
#include <cstring>
using namespace std;

// ============================================================================
// PART 1: THE PROBLEM POLYMORPHISM SOLVES
// ============================================================================

/*
 * Imagine you have different types of vehicles: Cars, Trucks, Motorcycles
 * 
 * WITHOUT polymorphism, you'd need:
 *   - Separate arrays for each type
 *   - Separate functions for each type
 *   - Lots of duplicated code!
 * 
 * WITH polymorphism:
 *   - One array holds ALL vehicle types
 *   - One function works with ALL vehicle types
 *   - Each type can have its own behavior
 */

// ============================================================================
// PART 2: BASIC POLYMORPHISM WITH VIRTUAL FUNCTIONS
// ============================================================================

// Base class with virtual function
class Vehicle {
protected:
    int id;
    char make[30];
    char model[30];
    int year;
    bool isAvailable;

public:
    Vehicle() : id(0), year(2000), isAvailable(true) {
        strcpy(make, "Unknown");
        strcpy(model, "Unknown");
    }
    
    Vehicle(int vehicleId, const char* vMake, const char* vModel, int vYear)
        : id(vehicleId), year(vYear), isAvailable(true)
    {
        strcpy(make, vMake);
        strcpy(model, vModel);
    }
    
    // Virtual destructor - ESSENTIAL for polymorphism!
    virtual ~Vehicle() {
        // cout << "  [Vehicle destructor for " << make << " " << model << "]" << endl;
    }
    
    // Getters
    int getId() const { return id; }
    const char* getMake() const { return make; }
    const char* getModel() const { return model; }
    int getYear() const { return year; }
    bool getIsAvailable() const { return isAvailable; }
    
    // Setters
    void setAvailable(bool status) { isAvailable = status; }
    
    // Virtual function - CAN be overridden by derived classes
    virtual void display() const {
        cout << id << ": " << year << " " << make << " " << model;
        cout << " [" << (isAvailable ? "Available" : "Rented") << "]" << endl;
    }
    
    // Virtual function for rental price
    virtual double getDailyRate() const {
        return 50.0;  // Default rate
    }
    
    // Virtual function for description
    virtual const char* getVehicleType() const {
        return "Vehicle";
    }
};

// Derived class 1: Car
class Car : public Vehicle {
private:
    int numDoors;
    bool hasGPS;
    char category[20];  // "Economy", "Standard", "Luxury"

public:
    Car() : Vehicle(), numDoors(4), hasGPS(false) {
        strcpy(category, "Standard");
    }
    
    Car(int id, const char* make, const char* model, int year,
        int doors, bool gps, const char* cat)
        : Vehicle(id, make, model, year), numDoors(doors), hasGPS(gps)
    {
        strcpy(category, cat);
    }
    
    // Getters
    int getNumDoors() const { return numDoors; }
    bool getHasGPS() const { return hasGPS; }
    const char* getCategory() const { return category; }
    
    // Override virtual functions
    const char* getVehicleType() const override {
        return "Car";
    }
    
    double getDailyRate() const override {
        double rate = 45.0;  // Base car rate
        
        if (strcmp(category, "Economy") == 0) {
            rate = 35.0;
        } else if (strcmp(category, "Luxury") == 0) {
            rate = 95.0;
        }
        
        if (hasGPS) {
            rate += 10.0;  // GPS add-on
        }
        
        return rate;
    }
    
    void display() const override {
        cout << "[CAR] ";
        Vehicle::display();  // Call base class display
        cout << "      Category: " << category;
        cout << " | Doors: " << numDoors;
        cout << " | GPS: " << (hasGPS ? "Yes" : "No");
        cout << " | Rate: $" << getDailyRate() << "/day" << endl;
    }
};

// Derived class 2: Truck
class Truck : public Vehicle {
private:
    double payloadCapacity;  // in tons
    bool has4WD;
    char bedSize[20];  // "Short", "Standard", "Long"

public:
    Truck() : Vehicle(), payloadCapacity(1.0), has4WD(false) {
        strcpy(bedSize, "Standard");
    }
    
    Truck(int id, const char* make, const char* model, int year,
          double payload, bool fourWD, const char* bed)
        : Vehicle(id, make, model, year), payloadCapacity(payload), has4WD(fourWD)
    {
        strcpy(bedSize, bed);
    }
    
    // Getters
    double getPayloadCapacity() const { return payloadCapacity; }
    bool getHas4WD() const { return has4WD; }
    const char* getBedSize() const { return bedSize; }
    
    // Override virtual functions
    const char* getVehicleType() const override {
        return "Truck";
    }
    
    double getDailyRate() const override {
        double rate = 65.0;  // Base truck rate
        
        rate += payloadCapacity * 15.0;  // $15 per ton capacity
        
        if (has4WD) {
            rate += 20.0;  // 4WD premium
        }
        
        if (strcmp(bedSize, "Long") == 0) {
            rate += 10.0;
        }
        
        return rate;
    }
    
    void display() const override {
        cout << "[TRUCK] ";
        Vehicle::display();
        cout << "      Payload: " << payloadCapacity << " tons";
        cout << " | Bed: " << bedSize;
        cout << " | 4WD: " << (has4WD ? "Yes" : "No");
        cout << " | Rate: $" << getDailyRate() << "/day" << endl;
    }
};

// Derived class 3: Motorcycle
class Motorcycle : public Vehicle {
private:
    int engineCC;
    char style[20];  // "Sport", "Cruiser", "Touring"
    bool helmetIncluded;

public:
    Motorcycle() : Vehicle(), engineCC(600), helmetIncluded(true) {
        strcpy(style, "Sport");
    }
    
    Motorcycle(int id, const char* make, const char* model, int year,
               int cc, const char* bikeStyle, bool helmet)
        : Vehicle(id, make, model, year), engineCC(cc), helmetIncluded(helmet)
    {
        strcpy(style, bikeStyle);
    }
    
    // Getters
    int getEngineCC() const { return engineCC; }
    const char* getStyle() const { return style; }
    bool getHelmetIncluded() const { return helmetIncluded; }
    
    // Override virtual functions
    const char* getVehicleType() const override {
        return "Motorcycle";
    }
    
    double getDailyRate() const override {
        double rate = 40.0;  // Base motorcycle rate
        
        if (engineCC > 1000) {
            rate += 25.0;  // Big bike premium
        } else if (engineCC > 600) {
            rate += 10.0;
        }
        
        if (strcmp(style, "Touring") == 0) {
            rate += 15.0;
        }
        
        return rate;
    }
    
    void display() const override {
        cout << "[MOTORCYCLE] ";
        Vehicle::display();
        cout << "      Engine: " << engineCC << "cc";
        cout << " | Style: " << style;
        cout << " | Helmet: " << (helmetIncluded ? "Included" : "Not included");
        cout << " | Rate: $" << getDailyRate() << "/day" << endl;
    }
};

void demonstrateBasicPolymorphism() {
    cout << "=== Part 2: Basic Polymorphism ===" << endl;
    
    // Create different vehicle types
    Car car(101, "Toyota", "Camry", 2023, 4, true, "Standard");
    Truck truck(201, "Ford", "F-150", 2022, 2.5, true, "Long");
    Motorcycle bike(301, "Harley-Davidson", "Street 750", 2023, 749, "Cruiser", true);
    
    cout << "Individual display calls:" << endl;
    car.display();
    cout << endl;
    truck.display();
    cout << endl;
    bike.display();
    cout << endl;
    
    // THE MAGIC: Base class pointers can point to derived objects!
    cout << "Using base class pointers:" << endl;
    Vehicle* v1 = &car;
    Vehicle* v2 = &truck;
    Vehicle* v3 = &bike;
    
    // Each calls its OWN version of display() and getDailyRate()!
    v1->display();
    cout << endl;
    v2->display();
    cout << endl;
    v3->display();
    cout << endl;
    
    cout << "This is POLYMORPHISM - one interface, multiple behaviors!" << endl;
    cout << endl;
}

// ============================================================================
// PART 3: POLYMORPHIC ARRAYS
// ============================================================================

void demonstratePolymorphicArrays() {
    cout << "=== Part 3: Polymorphic Arrays ===" << endl;
    
    // Array of BASE CLASS POINTERS can hold ANY derived type!
    Vehicle* fleet[6];
    
    // Fill with different vehicle types
    fleet[0] = new Car(1, "Honda", "Civic", 2023, 4, false, "Economy");
    fleet[1] = new Car(2, "BMW", "530i", 2023, 4, true, "Luxury");
    fleet[2] = new Truck(3, "Chevy", "Silverado", 2022, 2.0, true, "Standard");
    fleet[3] = new Truck(4, "Toyota", "Tacoma", 2023, 1.5, false, "Short");
    fleet[4] = new Motorcycle(5, "Kawasaki", "Ninja 650", 2023, 649, "Sport", true);
    fleet[5] = new Motorcycle(6, "BMW", "R1250GS", 2022, 1254, "Touring", true);
    
    // Process ALL vehicles with ONE loop!
    cout << "Complete Fleet Inventory:" << endl;
    cout << "-------------------------" << endl;
    
    double totalDailyRevenue = 0;
    for (int i = 0; i < 6; i++) {
        fleet[i]->display();
        totalDailyRevenue += fleet[i]->getDailyRate();
        cout << endl;
    }
    
    cout << "Total potential daily revenue: $" << totalDailyRevenue << endl;
    cout << endl;
    
    // Count by type using polymorphism
    int carCount = 0, truckCount = 0, bikeCount = 0;
    for (int i = 0; i < 6; i++) {
        if (strcmp(fleet[i]->getVehicleType(), "Car") == 0) {
            carCount++;
        } else if (strcmp(fleet[i]->getVehicleType(), "Truck") == 0) {
            truckCount++;
        } else if (strcmp(fleet[i]->getVehicleType(), "Motorcycle") == 0) {
            bikeCount++;
        }
    }
    
    cout << "Fleet composition:" << endl;
    cout << "  Cars: " << carCount << endl;
    cout << "  Trucks: " << truckCount << endl;
    cout << "  Motorcycles: " << bikeCount << endl;
    cout << endl;
    
    // Clean up - delete all vehicles
    for (int i = 0; i < 6; i++) {
        delete fleet[i];
    }
}

// ============================================================================
// PART 4: ABSTRACT CLASSES AND PURE VIRTUAL FUNCTIONS
// ============================================================================

/*
 * Sometimes a base class should NEVER be instantiated directly.
 * It only exists to define an interface for derived classes.
 * 
 * ABSTRACT CLASS: Has at least one PURE VIRTUAL FUNCTION
 * PURE VIRTUAL FUNCTION: Declared with "= 0", has NO implementation in base
 * 
 * Rules:
 * 1. Cannot create objects of abstract class type
 * 2. Derived classes MUST implement all pure virtual functions
 * 3. If derived class doesn't implement all, it's also abstract
 */

// ABSTRACT BASE CLASS
class Shape {
protected:
    char name[30];
    char color[20];

public:
    Shape() {
        strcpy(name, "Shape");
        strcpy(color, "None");
    }
    
    Shape(const char* shapeName, const char* shapeColor) {
        strcpy(name, shapeName);
        strcpy(color, shapeColor);
    }
    
    virtual ~Shape() {}
    
    // Getters
    const char* getName() const { return name; }
    const char* getColor() const { return color; }
    
    // PURE VIRTUAL FUNCTIONS - derived classes MUST implement these
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual void draw() const = 0;
    
    // Regular virtual function with default implementation
    virtual void display() const {
        cout << color << " " << name;
        cout << " (Area: " << getArea();
        cout << ", Perimeter: " << getPerimeter() << ")" << endl;
    }
};

// Concrete class - implements ALL pure virtual functions
class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle() : Shape("Rectangle", "Red"), width(1), height(1) {}
    
    Rectangle(double w, double h, const char* color)
        : Shape("Rectangle", color), width(w), height(h) {}
    
    // Getters
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    
    // MUST implement all pure virtual functions!
    double getArea() const override {
        return width * height;
    }
    
    double getPerimeter() const override {
        return 2 * (width + height);
    }
    
    void draw() const override {
        cout << "Drawing rectangle:" << endl;
        for (int i = 0; i < height && i < 5; i++) {
            for (int j = 0; j < width && j < 10; j++) {
                cout << "* ";
            }
            cout << endl;
        }
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle() : Shape("Circle", "Blue"), radius(1) {}
    
    Circle(double r, const char* color)
        : Shape("Circle", color), radius(r) {}
    
    double getRadius() const { return radius; }
    
    // Implement pure virtual functions
    double getArea() const override {
        return 3.14159 * radius * radius;
    }
    
    double getPerimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    void draw() const override {
        cout << "Drawing circle with radius " << radius << ":" << endl;
        // Simple circle approximation
        cout << "    ***" << endl;
        cout << "  *     *" << endl;
        cout << " *       *" << endl;
        cout << "  *     *" << endl;
        cout << "    ***" << endl;
    }
};

class Triangle : public Shape {
private:
    double base;
    double height;
    double side1, side2, side3;

public:
    Triangle() : Shape("Triangle", "Green"), 
                 base(3), height(4), side1(3), side2(4), side3(5) {}
    
    Triangle(double b, double h, double s1, double s2, double s3, const char* color)
        : Shape("Triangle", color), base(b), height(h), side1(s1), side2(s2), side3(s3) {}
    
    // Implement pure virtual functions
    double getArea() const override {
        return 0.5 * base * height;
    }
    
    double getPerimeter() const override {
        return side1 + side2 + side3;
    }
    
    void draw() const override {
        cout << "Drawing triangle:" << endl;
        cout << "    *" << endl;
        cout << "   * *" << endl;
        cout << "  *   *" << endl;
        cout << " *     *" << endl;
        cout << "*********" << endl;
    }
};

void demonstrateAbstractClasses() {
    cout << "=== Part 4: Abstract Classes ===" << endl;
    
    // Shape shape;  // ERROR! Cannot instantiate abstract class!
    
    // But we CAN create derived class objects
    Rectangle rect(5, 3, "Red");
    Circle circ(4, "Blue");
    Triangle tri(6, 4, 5, 5, 6, "Green");
    
    // Polymorphic array of shapes
    Shape* shapes[3];
    shapes[0] = &rect;
    shapes[1] = &circ;
    shapes[2] = &tri;
    
    cout << "Processing all shapes polymorphically:" << endl;
    cout << "--------------------------------------" << endl;
    
    for (int i = 0; i < 3; i++) {
        shapes[i]->display();
        shapes[i]->draw();
        cout << endl;
    }
    
    // Calculate total area of all shapes
    double totalArea = 0;
    for (int i = 0; i < 3; i++) {
        totalArea += shapes[i]->getArea();
    }
    cout << "Total area of all shapes: " << totalArea << endl;
    cout << endl;
}

// ============================================================================
// PART 5: WHY VIRTUAL DESTRUCTORS MATTER
// ============================================================================

class Base {
public:
    Base() { cout << "  Base constructor" << endl; }
    
    // WITHOUT virtual: Only ~Base() is called when deleting through Base*
    // WITH virtual: Both ~Derived() AND ~Base() are called (correct!)
    virtual ~Base() { cout << "  Base destructor" << endl; }
};

class Derived : public Base {
private:
    int* data;  // Simulating dynamic memory

public:
    Derived() : Base() {
        data = new int[100];  // Allocate memory
        cout << "  Derived constructor (allocated memory)" << endl;
    }
    
    ~Derived() override {
        delete[] data;  // Free memory
        cout << "  Derived destructor (freed memory)" << endl;
    }
};

void demonstrateVirtualDestructor() {
    cout << "=== Part 5: Virtual Destructors ===" << endl;
    
    cout << "Creating Derived through Base pointer:" << endl;
    Base* ptr = new Derived();
    
    cout << "\nDeleting through Base pointer:" << endl;
    delete ptr;  // With virtual destructor, BOTH destructors run!
    
    cout << "\nWithout virtual destructor, only Base destructor would run," << endl;
    cout << "causing a MEMORY LEAK! The Derived memory wouldn't be freed." << endl;
    cout << endl;
}

// ============================================================================
// PART 6: COMPLETE RENTAL SYSTEM EXAMPLE
// ============================================================================

// Forward declaration
class Customer;

// Abstract payment class
class Payment {
protected:
    int paymentId;
    double amount;
    bool processed;

public:
    Payment(int id, double amt) : paymentId(id), amount(amt), processed(false) {}
    virtual ~Payment() {}
    
    double getAmount() const { return amount; }
    bool isProcessed() const { return processed; }
    
    // Pure virtual - each payment type processes differently
    virtual bool process() = 0;
    virtual const char* getType() const = 0;
    virtual void display() const = 0;
};

class CashPayment : public Payment {
private:
    double amountReceived;

public:
    CashPayment(int id, double amt, double received)
        : Payment(id, amt), amountReceived(received) {}
    
    bool process() override {
        if (amountReceived >= amount) {
            processed = true;
            cout << "  Cash payment processed. Change: $" 
                 << (amountReceived - amount) << endl;
            return true;
        }
        cout << "  Insufficient cash!" << endl;
        return false;
    }
    
    const char* getType() const override { return "Cash"; }
    
    void display() const override {
        cout << "  [CASH] Amount: $" << amount;
        cout << " | Received: $" << amountReceived;
        cout << " | Status: " << (processed ? "Paid" : "Pending") << endl;
    }
};

class CardPayment : public Payment {
private:
    char lastFour[5];

public:
    CardPayment(int id, double amt, const char* last4)
        : Payment(id, amt)
    {
        strncpy(lastFour, last4, 4);
        lastFour[4] = '\0';
    }
    
    bool process() override {
        // Simulate card authorization
        processed = true;
        cout << "  Card ****" << lastFour << " authorized for $" << amount << endl;
        return true;
    }
    
    const char* getType() const override { return "Credit Card"; }
    
    void display() const override {
        cout << "  [CARD] Amount: $" << amount;
        cout << " | Card: ****" << lastFour;
        cout << " | Status: " << (processed ? "Paid" : "Pending") << endl;
    }
};

// Rental record connecting everything
class RentalRecord {
private:
    int recordId;
    Vehicle* vehicle;    // Polymorphic - any vehicle type
    char customerName[50];
    int days;
    Payment* payment;    // Polymorphic - any payment type
    bool isActive;

public:
    RentalRecord(int id, Vehicle* v, const char* customer, int numDays)
        : recordId(id), vehicle(v), days(numDays), payment(nullptr), isActive(true)
    {
        strcpy(customerName, customer);
    }
    
    // Calculate total using polymorphic call to vehicle
    double calculateTotal() const {
        if (vehicle) {
            return vehicle->getDailyRate() * days;
        }
        return 0;
    }
    
    void attachPayment(Payment* p) {
        payment = p;
    }
    
    bool processRental() {
        if (!vehicle || !payment) return false;
        
        if (payment->process()) {
            vehicle->setAvailable(false);
            cout << "  Rental confirmed for " << days << " days!" << endl;
            return true;
        }
        return false;
    }
    
    void completeRental() {
        if (vehicle) {
            vehicle->setAvailable(true);
        }
        isActive = false;
        cout << "  Vehicle returned. Rental complete." << endl;
    }
    
    void display() const {
        cout << "=== Rental #" << recordId << " ===" << endl;
        cout << "  Customer: " << customerName << endl;
        cout << "  Duration: " << days << " days" << endl;
        cout << "  Vehicle: ";
        if (vehicle) {
            cout << vehicle->getVehicleType() << " - ";
            cout << vehicle->getMake() << " " << vehicle->getModel() << endl;
            cout << "  Daily Rate: $" << vehicle->getDailyRate() << endl;
        }
        cout << "  Total: $" << calculateTotal() << endl;
        if (payment) {
            payment->display();
        }
        cout << "  Status: " << (isActive ? "Active" : "Completed") << endl;
    }
};

void demonstrateCompleteSystem() {
    cout << "=== Part 6: Complete Rental System ===" << endl;
    
    // Create fleet (polymorphic array)
    Vehicle* fleet[3];
    fleet[0] = new Car(1, "Toyota", "Corolla", 2023, 4, true, "Economy");
    fleet[1] = new Truck(2, "Ford", "F-150", 2022, 2.0, true, "Standard");
    fleet[2] = new Motorcycle(3, "Honda", "CBR600", 2023, 599, "Sport", true);
    
    cout << "Available Fleet:" << endl;
    cout << "----------------" << endl;
    for (int i = 0; i < 3; i++) {
        fleet[i]->display();
        cout << endl;
    }
    
    // Create rentals
    cout << "\n--- Processing Rentals ---" << endl;
    
    // Rental 1: Cash payment for car
    RentalRecord rental1(1001, fleet[0], "Alice Smith", 3);
    double total1 = rental1.calculateTotal();
    Payment* pay1 = new CashPayment(1, total1, 150.0);
    rental1.attachPayment(pay1);
    rental1.display();
    cout << "\nProcessing rental..." << endl;
    rental1.processRental();
    
    cout << "\n";
    
    // Rental 2: Card payment for truck
    RentalRecord rental2(1002, fleet[1], "Bob Johnson", 5);
    double total2 = rental2.calculateTotal();
    Payment* pay2 = new CardPayment(2, total2, "4532");
    rental2.attachPayment(pay2);
    rental2.display();
    cout << "\nProcessing rental..." << endl;
    rental2.processRental();
    
    cout << "\n--- Updated Fleet Status ---" << endl;
    for (int i = 0; i < 3; i++) {
        fleet[i]->display();
    }
    
    // Cleanup
    delete pay1;
    delete pay2;
    for (int i = 0; i < 3; i++) {
        delete fleet[i];
    }
    
    cout << endl;
}

// ============================================================================
// PART 7: POLYMORPHISM PATTERNS SUMMARY
// ============================================================================

void printPolymorphismSummary() {
    cout << "=== Part 7: Polymorphism Patterns Summary ===" << endl;
    cout << endl;
    
    cout << "PATTERN 1: Polymorphic Array" << endl;
    cout << "----------------------------" << endl;
    cout << "Base* items[SIZE];" << endl;
    cout << "items[0] = new Derived1(...);" << endl;
    cout << "items[1] = new Derived2(...);" << endl;
    cout << "for (int i = 0; i < SIZE; i++) {" << endl;
    cout << "    items[i]->virtualMethod();  // Calls correct version!" << endl;
    cout << "}" << endl;
    cout << endl;
    
    cout << "PATTERN 2: Abstract Base Class" << endl;
    cout << "------------------------------" << endl;
    cout << "class Base {" << endl;
    cout << "    virtual void mustImplement() = 0;  // Pure virtual" << endl;
    cout << "};" << endl;
    cout << "class Derived : public Base {" << endl;
    cout << "    void mustImplement() override { ... }  // MUST implement" << endl;
    cout << "};" << endl;
    cout << endl;
    
    cout << "PATTERN 3: Polymorphic Parameter" << endl;
    cout << "--------------------------------" << endl;
    cout << "void processAny(Base* item) {" << endl;
    cout << "    item->virtualMethod();  // Works with ANY derived type" << endl;
    cout << "}" << endl;
    cout << "processAny(new Derived1());  // OK!" << endl;
    cout << "processAny(new Derived2());  // OK!" << endl;
    cout << endl;
    
    cout << "PATTERN 4: Factory-like Creation" << endl;
    cout << "--------------------------------" << endl;
    cout << "Base* create(const char* type) {" << endl;
    cout << "    if (strcmp(type, \"A\") == 0) return new DerivedA();" << endl;
    cout << "    if (strcmp(type, \"B\") == 0) return new DerivedB();" << endl;
    cout << "    return nullptr;" << endl;
    cout << "}" << endl;
    cout << endl;
}

// ============================================================================
// EXERCISES FOR STUDENTS
// ============================================================================

/*
 * EXERCISE 1: Add a "Van" class derived from Vehicle
 * - Add: passengerCapacity (int), hasWheelchairAccess (bool)
 * - Override getDailyRate(): base $75, +$10 per 4 passengers, +$20 wheelchair
 * - Override display() and getVehicleType()
 * 
 * EXERCISE 2: Create an abstract "Employee" class
 * - Pure virtual: calculatePay(), getRole()
 * - Derived: HourlyEmployee (hours * rate), SalariedEmployee (fixed salary)
 * - Test polymorphically in an array
 *
 * EXERCISE 3: Add "LoyaltyPayment" to the rental system
 * - Like your Hotel assignment's LoyaltyPointsPayment
 * - Track points used, check if customer has enough
 * - Process by deducting points
 */

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    cout << "========================================" << endl;
    cout << "  Week 6: Polymorphism Deep Dive" << endl;
    cout << "========================================" << endl << endl;
    
    // Uncomment each section as we cover it
    
    demonstrateBasicPolymorphism();
    
    demonstratePolymorphicArrays();
    
    demonstrateAbstractClasses();
    
    demonstrateVirtualDestructor();
    
    demonstrateCompleteSystem();
    
    printPolymorphismSummary();
    
    cout << "========================================" << endl;
    cout << "  Key Takeaways:" << endl;
    cout << "========================================" << endl;
    cout << "1. Virtual functions enable runtime polymorphism" << endl;
    cout << "2. Base pointers can point to derived objects" << endl;
    cout << "3. '= 0' makes a function pure virtual (abstract)" << endl;
    cout << "4. Abstract classes define interfaces" << endl;
    cout << "5. ALWAYS use virtual destructors with inheritance" << endl;
    cout << "6. Polymorphic arrays process different types uniformly" << endl;
    cout << "========================================" << endl;
    
    return 0;
}
