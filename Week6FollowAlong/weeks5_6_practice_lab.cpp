// ============================================================================
// Weeks 5-6 Practice Lab: Building a Restaurant System
// 
// This practice lab helps you prepare for the Hotel Management assignment.
// Complete these exercises to master the patterns you'll need!
//
// The Restaurant System parallels the Hotel System:
//   Restaurant      <->  Hotel
//   MenuItem        <->  Room (polymorphic)
//   Customer        <->  Guest
//   Server          <->  Employee
//   Order           <->  Reservation
//   PaymentMethod   <->  Payment (polymorphic)
// ============================================================================

#include <iostream>
#include <cstring>
using namespace std;

// ============================================================================
// WEEK 5 PRACTICE: Basic Classes and Inheritance
// ============================================================================

// ----------------------------------------------------------------------------
// EXERCISE 1: Complete the Person base class
// This is the foundation for Customer and Server classes
// ----------------------------------------------------------------------------

class Person {
private:
    int id;
    char name[50];
    char phone[15];

public:
    // TODO: Implement default constructor
    // Initialize id to 0, name and phone to empty strings
    Person() {
        // YOUR CODE HERE
    }
    
    // TODO: Implement parameterized constructor
    // Use strcpy for char arrays
    Person(int personId, const char* personName, const char* personPhone) {
        // YOUR CODE HERE
    }
    
    // TODO: Implement getters
    int getId() const {
        return 0;  // FIX THIS
    }
    
    const char* getName() const {
        return "";  // FIX THIS
    }
    
    const char* getPhone() const {
        return "";  // FIX THIS
    }
    
    // TODO: Implement setters
    void setName(const char* newName) {
        // YOUR CODE HERE
    }
    
    void setPhone(const char* newPhone) {
        // YOUR CODE HERE
    }
    
    // TODO: Implement display (virtual for overriding)
    virtual void display() const {
        // Print: "ID: [id] | Name: [name] | Phone: [phone]"
        // YOUR CODE HERE
    }
    
    virtual ~Person() {}
};

// ----------------------------------------------------------------------------
// EXERCISE 2: Complete the Customer class (derived from Person)
// Similar to Guest in your assignment
// ----------------------------------------------------------------------------

class Customer : public Person {
private:
    int rewardPoints;
    int visitCount;
    bool isVIP;

public:
    // TODO: Implement default constructor
    // Call Person() and initialize Customer-specific members
    Customer() : Person() {
        // YOUR CODE HERE - initialize rewardPoints=0, visitCount=0, isVIP=false
    }
    
    // TODO: Implement parameterized constructor
    Customer(int id, const char* name, const char* phone, int points = 0)
        : Person(id, name, phone)
    {
        // YOUR CODE HERE
    }
    
    // TODO: Implement getters
    int getRewardPoints() const { return 0; }  // FIX
    int getVisitCount() const { return 0; }    // FIX
    bool getIsVIP() const { return false; }    // FIX
    
    // TODO: Add reward points (only if positive)
    void addRewardPoints(int points) {
        // YOUR CODE HERE
    }
    
    // TODO: Redeem points (return false if insufficient)
    bool redeemPoints(int points) {
        // YOUR CODE HERE
        return false;
    }
    
    // TODO: Record a visit (increment visitCount, check VIP status)
    // Customer becomes VIP after 10 visits
    void recordVisit() {
        // YOUR CODE HERE
    }
    
    // TODO: Get discount based on status
    // Regular: 0%, VIP: 10%
    double getDiscount() const {
        // YOUR CODE HERE
        return 0.0;
    }
    
    // TODO: Override display to show Customer info
    void display() const override {
        // Call Person::display() first, then add:
        // "  Rewards: [points] pts | Visits: [count] | VIP: [Yes/No]"
        // YOUR CODE HERE
    }
};

// ----------------------------------------------------------------------------
// EXERCISE 3: Complete the Server class (derived from Person)
// Similar to Employee in your assignment
// ----------------------------------------------------------------------------

class Server : public Person {
private:
    char section[20];
    double tipTotal;
    int tablesServed;

public:
    // TODO: Implement constructors
    Server() : Person() {
        strcpy(section, "");
        tipTotal = 0.0;
        tablesServed = 0;
    }
    
    Server(int id, const char* name, const char* phone, const char* serverSection)
        : Person(id, name, phone)
    {
        // YOUR CODE HERE
    }
    
    // TODO: Implement getters
    const char* getSection() const { return ""; }  // FIX
    double getTipTotal() const { return 0.0; }      // FIX
    int getTablesServed() const { return 0; }       // FIX
    
    // TODO: Add tip and increment tables served
    void addTip(double amount) {
        // YOUR CODE HERE
    }
    
    // TODO: Calculate average tip per table
    double getAverageTip() const {
        // YOUR CODE HERE (avoid division by zero!)
        return 0.0;
    }
    
    // TODO: Reset for new shift
    void startNewShift() {
        // YOUR CODE HERE
    }
    
    // TODO: Override display
    void display() const override {
        // YOUR CODE HERE
    }
};

// Test function for Week 5 exercises
void testWeek5Classes() {
    cout << "=== Testing Week 5 Classes ===" << endl << endl;
    
    // Test Person
    cout << "Testing Person:" << endl;
    Person p1;
    Person p2(1, "John Doe", "555-1234");
    p1.display();
    p2.display();
    cout << endl;
    
    // Test Customer
    cout << "Testing Customer:" << endl;
    Customer c1(101, "Alice Smith", "555-5678", 100);
    c1.display();
    c1.addRewardPoints(50);
    cout << "After adding 50 points: " << c1.getRewardPoints() << endl;
    for (int i = 0; i < 10; i++) {
        c1.recordVisit();
    }
    cout << "After 10 visits:" << endl;
    c1.display();
    cout << "Discount: " << c1.getDiscount() * 100 << "%" << endl;
    cout << endl;
    
    // Test Server
    cout << "Testing Server:" << endl;
    Server s1(201, "Bob Jones", "555-9999", "Patio");
    s1.addTip(15.50);
    s1.addTip(22.00);
    s1.addTip(18.75);
    s1.display();
    cout << "Average tip: $" << s1.getAverageTip() << endl;
    cout << endl;
}

// ============================================================================
// WEEK 6 PRACTICE: Polymorphism and Abstract Classes
// ============================================================================

// ----------------------------------------------------------------------------
// EXERCISE 4: Complete the MenuItem abstract class
// Similar to Room in your assignment
// ----------------------------------------------------------------------------

class MenuItem {
protected:
    int itemId;
    char name[50];
    char description[100];
    bool isAvailable;

public:
    MenuItem() : itemId(0), isAvailable(true) {
        strcpy(name, "");
        strcpy(description, "");
    }
    
    MenuItem(int id, const char* itemName, const char* desc)
        : itemId(id), isAvailable(true)
    {
        strcpy(name, itemName);
        strcpy(description, desc);
    }
    
    virtual ~MenuItem() {}
    
    // Getters
    int getItemId() const { return itemId; }
    const char* getName() const { return name; }
    const char* getDescription() const { return description; }
    bool getIsAvailable() const { return isAvailable; }
    
    void setAvailable(bool status) { isAvailable = status; }
    
    // TODO: Declare pure virtual functions
    // These MUST be implemented by derived classes
    
    virtual double getPrice() const = 0;           // Price calculation
    virtual const char* getCategory() const = 0;   // "Appetizer", "Entree", "Dessert", etc.
    virtual int getPrepTime() const = 0;           // Preparation time in minutes
    
    // Virtual display with default implementation
    virtual void display() const {
        cout << itemId << ": " << name << " - $" << getPrice() << endl;
        cout << "   " << description << endl;
        cout << "   Category: " << getCategory();
        cout << " | Prep: " << getPrepTime() << " min";
        cout << " | " << (isAvailable ? "Available" : "Sold Out") << endl;
    }
};

// ----------------------------------------------------------------------------
// EXERCISE 5: Implement Appetizer class (derived from MenuItem)
// ----------------------------------------------------------------------------

class Appetizer : public MenuItem {
private:
    bool isShareable;
    int servingSize;  // number of pieces

public:
    Appetizer() : MenuItem(), isShareable(true), servingSize(6) {}
    
    Appetizer(int id, const char* name, const char* desc, 
              bool shareable, int pieces)
        : MenuItem(id, name, desc), isShareable(shareable), servingSize(pieces) {}
    
    bool getIsShareable() const { return isShareable; }
    int getServingSize() const { return servingSize; }
    
    // TODO: Implement pure virtual functions
    
    double getPrice() const override {
        // Base price: $8 + $1 per piece over 4
        // YOUR CODE HERE
        return 0.0;
    }
    
    const char* getCategory() const override {
        return "Appetizer";
    }
    
    int getPrepTime() const override {
        // 5 minutes base + 1 minute per 2 pieces
        // YOUR CODE HERE
        return 0;
    }
    
    void display() const override {
        MenuItem::display();
        cout << "   Pieces: " << servingSize;
        cout << " | Shareable: " << (isShareable ? "Yes" : "No") << endl;
    }
};

// ----------------------------------------------------------------------------
// EXERCISE 6: Implement Entree class (derived from MenuItem)
// ----------------------------------------------------------------------------

class Entree : public MenuItem {
private:
    char protein[30];    // "Chicken", "Beef", "Fish", "Vegetarian"
    bool includesSide;
    bool isSpicy;

public:
    Entree() : MenuItem(), includesSide(true), isSpicy(false) {
        strcpy(protein, "Chicken");
    }
    
    Entree(int id, const char* name, const char* desc,
           const char* prot, bool side, bool spicy)
        : MenuItem(id, name, desc), includesSide(side), isSpicy(spicy)
    {
        strcpy(protein, prot);
    }
    
    const char* getProtein() const { return protein; }
    bool getIncludesSide() const { return includesSide; }
    bool getIsSpicy() const { return isSpicy; }
    
    // TODO: Implement pure virtual functions
    
    double getPrice() const override {
        // Base prices by protein:
        // Vegetarian: $14, Chicken: $18, Fish: $22, Beef: $24
        // Add $4 if includes side
        // YOUR CODE HERE
        return 0.0;
    }
    
    const char* getCategory() const override {
        return "Entree";
    }
    
    int getPrepTime() const override {
        // Vegetarian: 12min, Chicken: 15min, Fish: 18min, Beef: 20min
        // YOUR CODE HERE
        return 0;
    }
    
    void display() const override {
        MenuItem::display();
        cout << "   Protein: " << protein;
        cout << " | Side: " << (includesSide ? "Included" : "No");
        cout << " | Spicy: " << (isSpicy ? "Yes" : "No") << endl;
    }
};

// ----------------------------------------------------------------------------
// EXERCISE 7: Implement Dessert class (derived from MenuItem)
// ----------------------------------------------------------------------------

class Dessert : public MenuItem {
private:
    bool containsNuts;
    bool isGlutenFree;
    int calories;

public:
    Dessert() : MenuItem(), containsNuts(false), isGlutenFree(false), calories(300) {}
    
    Dessert(int id, const char* name, const char* desc,
            bool nuts, bool gf, int cal)
        : MenuItem(id, name, desc), containsNuts(nuts), isGlutenFree(gf), calories(cal) {}
    
    // TODO: Implement getters
    bool getContainsNuts() const { return false; }  // FIX
    bool getIsGlutenFree() const { return false; }  // FIX
    int getCalories() const { return 0; }           // FIX
    
    // TODO: Implement pure virtual functions
    
    double getPrice() const override {
        // Base: $9, +$2 if gluten-free (special ingredients)
        // YOUR CODE HERE
        return 0.0;
    }
    
    const char* getCategory() const override {
        return "Dessert";
    }
    
    int getPrepTime() const override {
        // All desserts: 8 minutes (pre-made, just plating)
        return 8;
    }
    
    void display() const override {
        MenuItem::display();
        cout << "   Calories: " << calories;
        cout << " | Nuts: " << (containsNuts ? "Yes" : "No");
        cout << " | GF: " << (isGlutenFree ? "Yes" : "No") << endl;
    }
};

// Test function for Week 6 exercises
void testWeek6Classes() {
    cout << "=== Testing Week 6 Polymorphism ===" << endl << endl;
    
    // Create menu items
    Appetizer app(1, "Loaded Nachos", "Tortilla chips with cheese and toppings", true, 8);
    Entree ent1(2, "Grilled Salmon", "Atlantic salmon with lemon butter", "Fish", true, false);
    Entree ent2(3, "Spicy Tofu Stir-fry", "Crispy tofu with vegetables", "Vegetarian", true, true);
    Dessert des(4, "Chocolate Lava Cake", "Warm chocolate cake with molten center", true, false, 650);
    
    // Polymorphic array
    MenuItem* menu[4];
    menu[0] = &app;
    menu[1] = &ent1;
    menu[2] = &ent2;
    menu[3] = &des;
    
    cout << "===== RESTAURANT MENU =====" << endl << endl;
    
    double totalIfOrderedAll = 0;
    int totalPrepTime = 0;
    
    for (int i = 0; i < 4; i++) {
        menu[i]->display();
        totalIfOrderedAll += menu[i]->getPrice();
        totalPrepTime += menu[i]->getPrepTime();
        cout << endl;
    }
    
    cout << "============================" << endl;
    cout << "Total if ordered all: $" << totalIfOrderedAll << endl;
    cout << "Total prep time: " << totalPrepTime << " minutes" << endl;
    cout << endl;
    
    // Count by category using polymorphism
    int appCount = 0, entreeCount = 0, dessertCount = 0;
    for (int i = 0; i < 4; i++) {
        if (strcmp(menu[i]->getCategory(), "Appetizer") == 0) appCount++;
        else if (strcmp(menu[i]->getCategory(), "Entree") == 0) entreeCount++;
        else if (strcmp(menu[i]->getCategory(), "Dessert") == 0) dessertCount++;
    }
    
    cout << "Menu composition:" << endl;
    cout << "  Appetizers: " << appCount << endl;
    cout << "  Entrees: " << entreeCount << endl;
    cout << "  Desserts: " << dessertCount << endl;
    cout << endl;
}

// ----------------------------------------------------------------------------
// EXERCISE 8: Payment hierarchy (like your Hotel assignment)
// ----------------------------------------------------------------------------

class PaymentMethod {
protected:
    double amount;
    bool processed;

public:
    PaymentMethod(double amt) : amount(amt), processed(false) {}
    virtual ~PaymentMethod() {}
    
    double getAmount() const { return amount; }
    bool isProcessed() const { return processed; }
    
    // TODO: Declare pure virtual functions
    virtual bool process() = 0;
    virtual const char* getType() const = 0;
    virtual double getTip() const { return 0; }  // Default: no tip
    virtual void display() const = 0;
};

class CashPaymentMethod : public PaymentMethod {
private:
    double cashGiven;
    double tipAmount;

public:
    CashPaymentMethod(double amt, double given, double tip)
        : PaymentMethod(amt), cashGiven(given), tipAmount(tip) {}
    
    // TODO: Implement all pure virtual functions
    bool process() override {
        // Process if cashGiven >= amount + tipAmount
        // YOUR CODE HERE
        return false;
    }
    
    const char* getType() const override {
        return "Cash";
    }
    
    double getTip() const override {
        return tipAmount;
    }
    
    void display() const override {
        cout << "[CASH] Total: $" << amount;
        cout << " | Tip: $" << tipAmount;
        cout << " | Given: $" << cashGiven;
        cout << " | Change: $" << (cashGiven - amount - tipAmount);
        cout << " | " << (processed ? "Paid" : "Pending") << endl;
    }
};

class CardPaymentMethod : public PaymentMethod {
private:
    char lastFour[5];
    double tipPercent;

public:
    CardPaymentMethod(double amt, const char* last4, double tipPct)
        : PaymentMethod(amt), tipPercent(tipPct)
    {
        strncpy(lastFour, last4, 4);
        lastFour[4] = '\0';
    }
    
    // TODO: Implement all pure virtual functions
    bool process() override {
        // YOUR CODE HERE
        return false;
    }
    
    const char* getType() const override {
        return "Credit Card";
    }
    
    double getTip() const override {
        return amount * (tipPercent / 100.0);
    }
    
    void display() const override {
        double tip = getTip();
        cout << "[CARD] Total: $" << amount;
        cout << " | Tip (" << tipPercent << "%): $" << tip;
        cout << " | Card: ****" << lastFour;
        cout << " | " << (processed ? "Paid" : "Pending") << endl;
    }
};

// Test payments
void testPayments() {
    cout << "=== Testing Payment Polymorphism ===" << endl << endl;
    
    PaymentMethod* payments[2];
    payments[0] = new CashPaymentMethod(45.50, 60.00, 8.00);
    payments[1] = new CardPaymentMethod(72.30, "1234", 20);
    
    double totalTips = 0;
    for (int i = 0; i < 2; i++) {
        payments[i]->display();
        payments[i]->process();
        payments[i]->display();
        totalTips += payments[i]->getTip();
        cout << endl;
    }
    
    cout << "Total tips collected: $" << totalTips << endl;
    
    // Cleanup
    for (int i = 0; i < 2; i++) {
        delete payments[i];
    }
    cout << endl;
}

// ============================================================================
// MAPPING TO YOUR HOTEL ASSIGNMENT
// ============================================================================

void printAssignmentMapping() {
    cout << "==========================================" << endl;
    cout << "  How This Maps to Your Assignment" << endl;
    cout << "==========================================" << endl;
    cout << endl;
    cout << "Restaurant System     ->  Hotel System" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Person               ->  Person" << endl;
    cout << "Customer             ->  Guest" << endl;
    cout << "  rewardPoints       ->  loyaltyPoints" << endl;
    cout << "  getDiscount()      ->  getTierDiscount()" << endl;
    cout << "Server               ->  Employee" << endl;
    cout << "  tipTotal           ->  calculatePay()" << endl;
    cout << endl;
    cout << "MenuItem (abstract)  ->  Room (abstract)" << endl;
    cout << "Appetizer            ->  StandardRoom" << endl;
    cout << "Entree               ->  DeluxeRoom" << endl;
    cout << "Dessert              ->  Suite" << endl;
    cout << "  getPrice()         ->  getBasePrice()" << endl;
    cout << "  getCategory()      ->  getRoomType()" << endl;
    cout << "  getPrepTime()      ->  getMaxOccupancy()" << endl;
    cout << endl;
    cout << "PaymentMethod        ->  Payment" << endl;
    cout << "CashPaymentMethod    ->  CashPayment" << endl;
    cout << "CardPaymentMethod    ->  CreditCardPayment" << endl;
    cout << "(not shown)          ->  LoyaltyPointsPayment" << endl;
    cout << endl;
    cout << "The PATTERNS are the same - just different data!" << endl;
    cout << "==========================================" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "===========================================" << endl;
    cout << "  Weeks 5-6 Practice Lab" << endl;
    cout << "  Restaurant System" << endl;
    cout << "===========================================" << endl << endl;
    
    // Week 5 exercises
    testWeek5Classes();
    
    // Week 6 exercises
    testWeek6Classes();
    
    // Payment exercises
    testPayments();
    
    // Show mapping
    printAssignmentMapping();
    
    return 0;
}
