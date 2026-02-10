// ============================================================================
// STUDENT VERSION: Student Class (Guided Code-Along)
// 
// Follow the TODO prompts with your instructor.
// By the end of class, this file will match the completed solution.
// ============================================================================

#include <iostream>
#include <cstring>
using namespace std;

// ============================================================================
// STEP 1: Declare the Student class
// ============================================================================

class Student {
private:
    // TODO STEP 1:
    // Add the following private data members:
    // - int studentId
    // - char name[50]
    // - double gpa
    // - int credits



public:
    // ========================================================================
    // STEP 2: Default Constructor
    // ========================================================================
    
    // TODO STEP 2:
    // Create a default constructor that:
    // - Prints "[Default Student constructor called]"
    // - Sets studentId to 0
    // - Sets name to an empty string
    // - Sets gpa to 0.0
    // - Sets credits to 0



    // ========================================================================
    // STEP 3: Parameterized Constructor
    // ========================================================================
    
    // TODO STEP 3:
    // Create a constructor with parameters:
    // (int id, const char* studentName, double studentGpa, int studentCredits)
    //
    // Inside the constructor:
    // - Print "[Creating student: <name>]"
    // - Copy id and name
    // - Validate GPA (0.0–4.0)
    // - Validate credits (>= 0)



    // ========================================================================
    // STEP 4: Getters (all must be const)
    // ========================================================================

    // TODO STEP 4:
    // Write getters for:
    // - studentId
    // - name
    // - gpa
    // - credits
    //
    // Remember: getters should NOT modify the object!



    // ========================================================================
    // STEP 5: Setters with Validation
    // ========================================================================

    // TODO STEP 5A:
    // setName(const char*)
    // - Reject empty or null names
    // - Print success or error messages



    // TODO STEP 5B:
    // setGpa(double)
    // - Accept only values between 0.0 and 4.0
    // - Print success or error messages



    // TODO STEP 5C:
    // setCredits(int)
    // - Reject negative values
    // - Print success or error messages



    // ========================================================================
    // STEP 6: display() member function
    // ========================================================================

    // TODO STEP 6:
    // Create a display() function that prints:
    // - Student ID and name
    // - GPA and credits
    // - Full-time or Part-time status
    //
    // This function should NOT modify the object (hint: const)



    // ========================================================================
    // STEP 7: isFullTime()
    // ========================================================================

    // TODO STEP 7:
    // Create a function that returns true if credits >= 12
    // Otherwise, return false



    // ========================================================================
    // STEP 8: addCredits()
    // ========================================================================

    // TODO STEP 8:
    // Create a function that:
    // - Adds positive credits
    // - Rejects zero or negative values
    // - Prints success or error messages
};

// ============================================================================
// TESTING FUNCTION (DO NOT MODIFY)
// This will work correctly once your class is finished.
// ============================================================================

void testStudentClass() {
    cout << "=== Testing Our Student Class ===" << endl << endl;

    cout << "Test 1: Default Constructor" << endl;
    Student s1;
    s1.display();
    cout << endl;

    cout << "Test 2: Parameterized Constructor" << endl;
    Student s2(101, "Alice Johnson", 3.8, 15);
    s2.display();
    cout << endl;

    cout << "Test 3: Using Getters" << endl;
    cout << "  Student ID: " << s2.getStudentId() << endl;
    cout << "  Name: " << s2.getName() << endl;
    cout << "  GPA: " << s2.getGpa() << endl;
    cout << "  Credits: " << s2.getCredits() << endl;
    cout << endl;

    cout << "Test 4: Setters (Valid Data)" << endl;
    s2.setGpa(3.9);
    s2.setCredits(18);
    s2.display();
    cout << endl;

    cout << "Test 5: Setters (Invalid Data)" << endl;
    s2.setGpa(5.0);
    s2.setCredits(-5);
    s2.display();
    cout << endl;

    cout << "Test 6: Full-Time Status" << endl;
    Student partTime(102, "Bob Smith", 3.5, 9);
    Student fullTime(103, "Carol White", 3.7, 16);
    partTime.display();
    fullTime.display();
    cout << endl;

    cout << "Test 7: Adding Credits" << endl;
    partTime.addCredits(6);
    partTime.display();
    cout << endl;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    cout << "========================================" << endl;
    cout << "  GUIDED EXERCISE: Student Class" << endl;
    cout << "========================================" << endl << endl;

    testStudentClass();

    return 0;
}
