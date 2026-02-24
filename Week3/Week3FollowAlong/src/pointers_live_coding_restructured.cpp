// ============================================================================
// Week 3 Live Coding: Introduction to Pointers
// 
// Follow along with the instructor!
// We start with pointer basics, then work up to using them with structs.
// 
// Prerequisites: You know structs. Now let's learn pointers!
// ============================================================================

#include <iostream>
#include <cstring>
using namespace std;

// ============================================================================
// PART A: POINTER FUNDAMENTALS (Steps 1-4)
// No structs yet - just understanding what pointers ARE
// ============================================================================

// ============================================================================
// STEP 1: What is a pointer? Address-of (&) and dereference (*)
// ============================================================================

void step1_pointer_basics() {
    cout << "=== STEP 1: What is a Pointer? ===" << endl;
    
    // A regular variable holds a VALUE
    int age = 25;
    cout << "age holds the value: " << age << endl;
    cout << "age is stored at address: " << &age << endl;  // & = "address of"
    
    cout << endl;
    
    // A POINTER variable holds an ADDRESS
    int* ptr = &age;    // ptr now holds the address of age
    
    cout << "ptr holds the address: " << ptr << endl;
    cout << "The value AT that address: " << *ptr << endl;  // * = "dereference"
    Student* structure;
    (*structure).gpa;
    cout << endl;
    
    // Think of it like this:
    // age  = the actual house (holds the value 25)
    // &age = the street address of that house
    // ptr  = a piece of paper with the address written on it
    // *ptr = "go to that address and look inside" (gives us 25)
    
    // KEY INSIGHT: & and * are opposites!
    cout << "Proof that & and * are opposites:" << endl;
    cout << "  *(&age) = " << *(&age) << "  (same as age)" << endl;
    cout << "  &(*ptr) = " << &(*ptr) << "  (same as ptr)" << endl;
    
    cout << endl;
}

// ============================================================================
// STEP 2: Modifying values through pointers
// ============================================================================

void step2_modify_through_pointer() {
    cout << "=== STEP 2: Modifying Through Pointers ===" << endl;
    
    int score = 100;
    int* scorePtr = &score;
    
    cout << "Original score: " << score << endl;
    
    // We can CHANGE the value at an address using *
    *scorePtr = 150;    // Go to the address, change what's there
    
    cout << "After *scorePtr = 150:" << endl;
    cout << "  score = " << score << endl;        // Changed!
    cout << "  *scorePtr = " << *scorePtr << endl; // Same thing
    
    // This is POWERFUL - we changed 'score' without using 'score' directly!
    
    cout << endl;
}

// ============================================================================
// STEP 3: Pointers as function parameters (pass by pointer)
// ============================================================================

// TODO: Implement this function
// It should double the value at the address ptr points to
void doubleValue(int* ptr) {
    // Your code here - use * to access and modify the value
    //int temp = *ptr; 
    //temp = temp * 2; 
    //*ptr = temp; 

    *ptr = *ptr * 2;
}

// Compare: pass by value (makes a copy, doesn't affect original)
void doubleValueBroken(int x) {
    x = x * 2;  // Only changes the local copy!
}

void step3_pointer_parameters() {
    cout << "=== STEP 3: Pointers as Parameters ===" << endl;
    
    int num = 10;
    
    cout << "Starting value: " << num << endl;
    
    // Try the broken version first
    doubleValueBroken(num);
    cout << "After doubleValueBroken: " << num << endl;  // Still 10!
    
    // Now try the pointer version
    doubleValue(&num);  // Pass the ADDRESS of num
    cout << "After doubleValue: " << num << endl;  // Now 20!
    
    cout << endl;
}

// ============================================================================
// STEP 4: Multiple values through pointers & nullptr
// ============================================================================

// TODO: Implement swap
// Swap the values at two addresses
void swap(int* a, int* b) {
    // Your code here
    // Remember: *a is the value at address a
    int temp = *b; 
    *b = *a; 
    *a = temp;
}

// TODO: Implement safeDivide
// Divide x by y, store result at resultPtr
// Return false if y is zero OR if resultPtr is nullptr
bool safeDivide(int x, int y, double* resultPtr) {
    // Divide x by y, store in resultPtr
    // Cannot divide by 0
    // Make sure ptr is not nullptr
    // return true if valid result

    // if(!(y == 0 || resultPtr == nullptr))
    if(y != 0 && resultPtr != nullptr)
    {
        *resultPtr = x / y;
        return true;
    }
    return false;
}

void step4_multiple_and_null() {
    cout << "=== STEP 4: Multiple Pointers & nullptr ===" << endl;
    
    // Swap example
    int x = 5, y = 10;
    cout << "Before swap: x=" << x << ", y=" << y << endl;
    
    swap(&x, &y);
    
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    cout << endl;
    
    // nullptr example
    double result;
    
    if (safeDivide(10, 2, &result)) {
        cout << "10 / 2 = " << result << endl;
    }
    
    if (!safeDivide(10, 0, &result)) {
        cout << "Division by zero prevented!" << endl;
    }
    
    if (!safeDivide(10, 2, nullptr)) {
        cout << "nullptr check prevented crash!" << endl;
    }
    
    cout << endl;
}

// ============================================================================
// PART B: POINTERS AND ARRAYS (Steps 5-6)
// Understanding the pointer-array connection
// ============================================================================

// ============================================================================
// STEP 5: Arrays ARE pointers (sort of)
// ============================================================================

void step5_arrays_and_pointers() {
    cout << "=== STEP 5: Arrays and Pointers ===" << endl;
    
    int scores[5] = {90, 85, 78, 92, 88};
    
    // The array name IS a pointer to the first element!
    cout << "scores (array name) = " << scores << endl;
    cout << "&scores[0]          = " << &scores[0] << endl;  // Same address!
    
    cout << endl;
    
    // We can use a pointer to walk through an array
    int* ptr = scores;  // Points to first element
    
    cout << "Walking through array with pointer:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "  ptr + " << i << " points to value: " << *(ptr + i) << endl;
    }
    
    // *(ptr + i) is the same as ptr[i] is the same as scores[i]
    cout << endl;
    cout << "These are all equivalent:" << endl;
    cout << "  scores[2] = " << scores[2] << endl;
    cout << "  *(scores + 2) = " << *(scores + 2) << endl;
    cout << "  ptr[2] = " << ptr[2] << endl;
    cout << "  *(ptr + 2) = " << *(ptr + 2) << endl;
    
    cout << endl;
}

// ============================================================================
// STEP 6: Returning pointers - finding elements
// ============================================================================

// TODO: Implement findValue
// Search array for target value
// Return POINTER to the element if found, nullptr if not found
int* findValue(int arr[], int size, int target) {
    // Your code here
    // Hint: return &arr[i] when you find it
    for(int i =0; i<size; i++)
    {
        if(arr[i] == target){
            return &arr[i];
        }

    }
    for(int i = 0; i < size; i++)
    {
        if(*(arr + i) == target){
            return (arr + i);
        }
    }
    return nullptr;
}

// TODO: Implement findMax
// Return pointer to the largest element in the array
int* findMax(int arr[], int size) {
    // Your code here
    // What should you return if size is 0?
    // return nullptr
    if(size == 0)
    {
        return nullptr; 
    }
    int currentMax = arr[0];
    int* maxIndex = arr; //&arr[0] OR arr + i 
    for(int i =1; i<size; i++)
    {
        if(currentMax < arr[i])
        {
            currentMax = arr[i];
            maxIndex = &arr[i];   //(arr + i) 
        }
    }
    return maxIndex;
}

void step6_returning_pointers() {
    cout << "=== STEP 6: Returning Pointers ===" << endl;
    
    int numbers[5] = {30, 10, 50, 20, 40};
    int* numbersPtr = numbers; 
    // Find a value
    int* found = findValue(numbers, 5, 50);
    if (found != nullptr) {
        cout << "Found 50 at address " << found << endl;
        cout << "Value at that address: " << *found << endl;
        
        // We can even modify it!
        *found = 55;
        cout << "Changed it to: " << numbers[2] << endl;
    }
    
    // Try to find something that doesn't exist
    int* notFound = findValue(numbers, 5, 999);
    if (notFound == nullptr) {
        cout << "999 not found in array" << endl;
    }
    
    // Find max
    int* maxPtr = findMax(numbers, 5);
    if (maxPtr != nullptr) {
        cout << "Max value: " << *maxPtr << endl;
    }
    maxPtr = findMax(numbers, 0);
    if (maxPtr == nullptr)
    {
        cout << "Invalid Size" << endl;
    }

    cout << endl;
}

// ============================================================================
// PART C: POINTERS AND STRUCTS (Steps 7-9)
// Now we combine what we know!
// ============================================================================

// First, let's define a simple struct (you already know these!)
struct Student {
    int id;
    char name[50];
    double gpa;
    bool isEnrolled;
};

// ============================================================================
// STEP 7: The arrow operator (->) for struct pointers
// ============================================================================

void step7_arrow_operator() {
    cout << "=== STEP 7: The Arrow Operator ===" << endl;
    
    Student alice = {101, "Alice", 3.8, true};
    
    // Get a pointer to the struct
    Student* ptr = &alice;
    
    // Two ways to access members through a pointer:
    
    // Method 1: Dereference then dot (awkward)
    cout << "Using (*ptr).name: " << (*ptr).name << endl;
    
    // Method 2: Arrow operator (preferred!)
    cout << "Using ptr->name: " << ptr->name << endl;
    
    // The arrow is just shorthand: ptr->name means (*ptr).name
    
    cout << endl;
    
    // We can modify through the pointer too
    cout << "Original GPA: " << ptr->gpa << endl;
    ptr->gpa = 3.9;
    cout << "After ptr->gpa = 3.9: " << alice.gpa << endl;  // Changed!
    
    cout << endl;
}

// ============================================================================
// STEP 8: Struct pointers as parameters
// ============================================================================
/*
    int id;
    char name[50];
    double gpa;
    bool isEnrolled;
    */
// TODO: Implement displayStudent
// Print student info using arrow operator
// Handle nullptr case!
void displayStudent(const Student* s) {
    // Your code here
    // Remember: ALWAYS check for nullptr first!
    if(s != nullptr)
    {
        cout << "Student: " << s->name << endl;
        cout << "\t gpa: " << s->gpa << "\t Enrolled: " << s->isEnrolled << "\r\n";
    }
    return; 
}
/*
    int id;
    char name[50];
    double gpa;
    bool isEnrolled;
    */
// TODO: Implement giveBonus
// if a valid pointer and the student is enrolled
//      Add bonus points to student's GPA (max 4.0)
//      and return true
// Return false if student is nullptr or not enrolled
bool giveBonus(Student* s, double bonus) {
    // Your code here
    //(*s.gpa)
    // if(s!=nullptr && s->isEnrolled == true)
    bool isValid = false;
    if(s != nullptr)
    {
        if(s->isEnrolled == true)
        {
            s->gpa = s->gpa + bonus; 
            if(s->gpa > 4)
            {
                s->gpa = 4.0;
            }
            isValid = true;
        }
    }
    return isValid;
}

void step8_struct_pointer_params() {
    cout << "=== STEP 8: Struct Pointers as Parameters ===" << endl;
    
    Student students[2] = {
        {101, "Alice", 3.5, true},
        {102, "Bob", 3.2, false}  // Not enrolled
    };
    
    // Display student
    cout << "Alice's info:" << endl;
    displayStudent(&students[0]);
    
    // Give bonus to enrolled student
    cout << "\nGiving Alice a 0.3 bonus..." << endl;
    if (giveBonus(&students[0], 3.0)) {
        cout << "Success! New GPA: " << students[0].gpa << endl;
    }
    
    // Try to give bonus to non-enrolled student
    cout << "\nTrying to give Bob a bonus..." << endl;
    if (!giveBonus(&students[1], 0.3)) {
        cout << "Failed - Bob is not enrolled" << endl;
    }
    
    // Test nullptr handling
    cout << "\nTesting nullptr:" << endl;
    displayStudent(nullptr);
    
    cout << endl;
}

// ============================================================================
// STEP 9: Finding structs and returning pointers
// ============================================================================

// TODO: Implement findStudentById
// Search array for student with matching id
// Return pointer to student if found, nullptr if not
Student* findStudentById(Student students[], int size, int id) {
    // Your code here
    for(int i = 0; i<size; i++)
    {
        //students[i].id == id
        Student currentStudent = students[i];
        if(currentStudent.id == id)
        {
            return &(students[i]);   //students + i 
        }
    }
    return nullptr;
}

// TODO: Implement findTopStudent  
// Return pointer to student with highest GPA
// Only consider enrolled students!
Student* findTopStudent(Student students[], int size) {
    Student temp = {00, "Temp", 0.0, false};
    Student* currentStudent = &temp;   //students + i
    for(int i = 0; i<size; i++)
    {
            if((currentStudent->gpa < (students+i)->gpa) && ((students+i)->isEnrolled))
            {
                currentStudent = (students+i);
            }
    }
    if(currentStudent == &temp)
    {
        currentStudent = nullptr;
    }
    return currentStudent;
}

void step9_finding_structs() {
    cout << "=== STEP 9: Finding Structs ===" << endl;
    
    Student students[4] = {
        {101, "Alice", 3.8, true},
        {102, "Bob", 3.5, true},
        {103, "Carol", 3.9, false},  // Highest GPA but not enrolled!
        {104, "Dave", 3.7, true}
    };
    
    // Find by ID
    Student* found = findStudentById(students, 4, 102);
    if (found != nullptr) {
        cout << "Found student 102: " << found->name << endl;
    }
    
    // Try to find non-existent
    Student* notFound = findStudentById(students, 4, 999);
    if (notFound == nullptr) {
        cout << "Student 999 not found" << endl;
    }
    
    // Find top student (should be Alice, not Carol)
    Student* top = findTopStudent(students, 4);
    if (top != nullptr) {
        cout << "Top enrolled student: " << top->name 
             << " (GPA: " << top->gpa << ")" << endl;
    }
    
    cout << endl;
}

// ============================================================================
// PART D: POINTERS AS STRUCT MEMBERS (Steps 10-12)
// Structs can contain pointers to OTHER structs!
// ============================================================================

// Now we define structs that CONTAIN pointers
struct Course {
    int courseId;
    char name[50];
    int maxStudents;
};

struct Enrollment {
    Student* student;   // POINTER to a student
    Course* course;     // POINTER to a course
    char grade;
};

// ============================================================================
// STEP 10: Connecting structs with pointers
// ============================================================================

// TODO: Implement enrollStudent
// Set up the enrollment's student and course pointers
// Return false if any pointer is null
bool enrollStudent(Enrollment* enrollment, Student* student, Course* course) {
    // Your code here
    // Check ALL pointers before using!
    bool isValidEnrollment = false;
    if(enrollment != nullptr && student != nullptr && course != nullptr)
    {
        enrollment->course = course;    //(*enrollment).course = course; 
        (*enrollment).student = student;
        isValidEnrollment =  true;
    }
    return isValidEnrollment;
}

void step10_connecting_structs() {
    cout << "=== STEP 10: Connecting Structs with Pointers ===" << endl;
    
    Student alice = {101, "Alice", 3.8, true};
    Course cs101 = {1, "Intro to Programming", 30};
    
    Enrollment enrollment;
    enrollment.grade = ' ';  // No grade yet
    
    if (enrollStudent(&enrollment, &alice, &cs101)) {
        // Now we can access the connected data!
        cout << "Enrolled " << enrollment.student->name 
             << " in " << enrollment.course->name << endl;
    }
    
    // The power: enrollment doesn't COPY the student/course data
    // It just points to where they live
    // If we change alice's GPA, enrollment.student->gpa changes too!
    
    cout << "Alice's GPA via enrollment: " << enrollment.student->gpa << endl;
    alice.gpa = 3.9;
    cout << "After changing alice.gpa: " << enrollment.student->gpa << endl;
    
    cout << endl;
}

// ============================================================================
// STEP 11: Finding through pointer relationships
// ============================================================================

// TODO: Implement findEnrollmentByStudent
// Find which enrollment belongs to a given student
// Compare pointers, not IDs!
Enrollment* findEnrollmentByStudent(Enrollment enrollments[], int size, 
                                     const Student* student) {
    // Your code here
    // Hint: compare enrollment[i].student == student
    Enrollment* isEnrolled = nullptr; 
    for(int i = 0; i<size; i++)
    {
        //if(enrollments[i].student == student ? enrollee = &enrollments[i] : enrollee = nullptr)
        if(enrollments[i].student == student)
        {
            isEnrolled = &enrollments[i];
            break;
        }
    }
    return isEnrolled;
}

// TODO: Implement countEnrollmentsInCourse
// Count how many enrollments point to the given course
int countEnrollmentsInCourse(const Enrollment enrollments[], int size, 
                              const Course* course) {
    // Your code here
    int count = 0;
    for(int i = 0; i < size; i++)
    {
        if(enrollments[i].course == course)
        {
            count++;
        }
    }

    return count;
}

void step11_finding_relationships() {
    cout << "=== STEP 11: Finding Through Relationships ===" << endl;
    
    Student students[2] = {
        {101, "Alice", 3.8, true},
        {102, "Bob", 3.5, true}
    };
    
    Course courses[2] = {
        {1, "CS 101", 30},
        {2, "Math 201", 25}
    };
    
    // Set up some enrollments
    Enrollment enrollments[3] = {
        {students, &courses[0], 'A'},  // (students + i)  // Alice in CS101
        {&students[1], (courses), 'B'},  // Bob in CS101
        {&students[0], (courses + 1), 'A'}   // Alice in Math201
    };
    
    // Find Alice's first enrollment
    Enrollment* aliceEnroll = findEnrollmentByStudent(enrollments, 3, &students[0]);
    if (aliceEnroll != nullptr) {
        cout << "Found Alice's enrollment in: " 
             << aliceEnroll->course->name << endl;
    } //(*aliceEnroll).(*course).name
    
    // Count students in CS101
    int cs101Count = countEnrollmentsInCourse(enrollments, 3, &courses[0]);
    cout << "Students in CS101: " << cs101Count << endl;
    
    cout << endl;
}

// ============================================================================
// STEP 12: Arrays of pointers
// ============================================================================

// TODO: Implement getEnrolledStudents
// Fill array with POINTERS to students who have isEnrolled == true
// Return count of enrolled students Student * enrolled[] == Student ** enrolled
int getEnrolledStudents(Student students[], int size, Student* enrolled[]) {
    // Your code here
    // Store &students[i] in enrolled array when student is enrolled 
    int count = 0;
    for(int i = 0; i < size; i++)
    {
        if(students[i].isEnrolled)
        {
            enrolled[count] = &students[i]; //(students+i)
            count++;
        }
    }
    //access element within enrolled
    //(*(*enrolled)).gpa = 
    return count;
}

void step12_pointer_arrays() {
    cout << "=== STEP 12: Arrays of Pointers ===" << endl;
    
    Student students[5] = {
        {101, "Alice", 3.8, true},
        {102, "Bob", 3.5, false},
        {103, "Carol", 3.9, true},
        {104, "Dave", 3.2, false},
        {105, "Eve", 3.7, true}
    };
    
    // Get only enrolled students
    Student* enrolled[5];  // Array of POINTERS
    int count = getEnrolledStudents(students, 5, enrolled);
    
    cout << "Enrolled students (" << count << "):" << endl;
    for (int i = 0; i < count; i++) {
        cout << "  - " << enrolled[i]->name 
             << " (GPA: " << (*enrolled[i]).gpa << ")" << endl;
    }
    
    // We can modify through these pointers!
    if (count > 0) {
        enrolled[0]->gpa = 4.0;
        cout << "\nAfter bonus, Alice's GPA: " << students[0].gpa << endl;
    }
    
    cout << endl;
}

// ============================================================================
// PART E: ADVANCED POINTER TECHNIQUES (Steps 13-14)
// Double pointers and sorting
// ============================================================================

// ============================================================================
// STEP 13: Double pointers (pointer to pointer)
// ============================================================================

// TODO: Implement swapStudentPointers
// Swap where two Student* variables point
void swapStudentPointers(Student** p1, Student** p2) {
    // Your code here
    // p1 is a pointer to a Student*
    // *p1 gives you the Student* itself
    
    Student * temp2 = *p1;
    *p1 = *p2;
    *p2 = temp2;
}

void step13_double_pointers() {
    cout << "=== STEP 13: Double Pointers ===" << endl;
    
    Student alice = {101, "Alice", 3.8, true};
    Student bob = {102, "Bob", 3.5, true};
    
    Student* ptr1 = &alice;
    Student* ptr2 = &bob;
    
    cout << "Before swap:" << endl;
    cout << "  ptr1 points to: " << ptr1->name << endl;
    cout << "  ptr2 points to: " << ptr2->name << endl;
    
    swapStudentPointers(&ptr1, &ptr2);
    
    cout << "After swap:" << endl;
    cout << "  ptr1 points to: " << ptr1->name << endl;
    cout << "  ptr2 points to: " << ptr2->name << endl;
    
    // Note: alice and bob haven't moved!
    // We just changed which pointers point to whom
    
    cout << endl;
}

// ============================================================================
// STEP 14: Sorting an array of fpointers
// ============================================================================

// TODO: Implement sortByGpaDescending
// Sort array of Student pointers by GPA (highest first)
// Use bubble sort and swapStudentPointers
void sortByGpaDescending(Student* ptrs[], int size) {
    // Your code here
    
}

void step14_sorting_pointers() {
    cout << "=== STEP 14: Sorting Pointer Arrays ===" << endl;
    
    Student students[4] = {
        {101, "Alice", 3.5, true},
        {102, "Bob", 3.9, true},
        {103, "Carol", 3.2, true},
        {104, "Dave", 3.7, true}
    };
    
    // Create array of pointers
    Student* ptrs[4];
    for (int i = 0; i < 4; i++) {
        ptrs[i] = &students[i];
    }
    
    cout << "Before sorting:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "  " << ptrs[i]->name << ": " << ptrs[i]->gpa << endl;
    }
    
    sortByGpaDescending(ptrs, 4);
    
    cout << "After sorting by GPA (descending):" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "  " << ptrs[i]->name << ": " << ptrs[i]->gpa << endl;
    }
    // Expected: Bob(3.9), Dave(3.7), Alice(3.5), Carol(3.2)
    
    // The original array is unchanged!
    cout << "\nOriginal array order unchanged:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "  " << students[i].name << endl;
    }
    
    cout << endl;
}

// ============================================================================
// PART F: PUTTING IT ALL TOGETHER (Step 15)
// ============================================================================

// ============================================================================
// STEP 15: A complete mini-system
// ============================================================================

// TODO: Implement registerForCourse
// Find student by ID, find course by name, create enrollment
// Return true if successful
bool registerForCourse(Student students[], int sSize, int studentId,
                        Course courses[], int cSize, const char* courseName,
                        Enrollment enrollments[], int& enrollCount) {
    // Your code here:
    // 1. Find the student by ID
    // 2. Find the course by name (use strcmp)
    // 3. Create the enrollment
    // 4. Increment enrollCount
    
    return false;
}

void step15_complete_system() {
    cout << "=== STEP 15: Putting It All Together ===" << endl;
    
    Student students[3] = {
        {101, "Alice", 3.8, true},
        {102, "Bob", 3.5, true},
        {103, "Carol", 3.9, true}
    };
    
    Course courses[2] = {
        {1, "CS 101", 30},
        {2, "Math 201", 25}
    };
    
    Enrollment enrollments[10];
    int enrollCount = 0;
    
    // Register some students
    if (registerForCourse(students, 3, 101, courses, 2, "CS 101", 
                          enrollments, enrollCount)) {
        cout << "Alice registered for CS 101!" << endl;
    }
    
    if (registerForCourse(students, 3, 102, courses, 2, "CS 101", 
                          enrollments, enrollCount)) {
        cout << "Bob registered for CS 101!" << endl;
    }
    
    if (registerForCourse(students, 3, 101, courses, 2, "Math 201", 
                          enrollments, enrollCount)) {
        cout << "Alice registered for Math 201!" << endl;
    }
    
    // Try invalid registrations
    if (!registerForCourse(students, 3, 999, courses, 2, "CS 101", 
                           enrollments, enrollCount)) {
        cout << "Failed: Student 999 not found" << endl;
    }
    
    if (!registerForCourse(students, 3, 101, courses, 2, "Physics", 
                           enrollments, enrollCount)) {
        cout << "Failed: Physics course not found" << endl;
    }
    
    // Show all enrollments
    cout << "\nAll enrollments (" << enrollCount << "):" << endl;
    for (int i = 0; i < enrollCount; i++) {
        cout << "  " << enrollments[i].student->name 
             << " in " << enrollments[i].course->name << endl;
    }
    
    cout << endl;
}

// ============================================================================
// MAIN - Uncomment steps as we progress through lecture
// ============================================================================

int main() {
    cout << "Week 3: Introduction to Pointers" << endl;
    cout << "=================================" << endl << endl;
    
    // ---- PART A: POINTER FUNDAMENTALS ----
    step1_pointer_basics();
    step2_modify_through_pointer();
    step3_pointer_parameters();
    step4_multiple_and_null();
    
    // ---- PART B: POINTERS AND ARRAYS ----
    step5_arrays_and_pointers();
    step6_returning_pointers();
    
    // ---- PART C: POINTERS AND STRUCTS ----
    step7_arrow_operator();
    step8_struct_pointer_params();
    step9_finding_structs();
    
    // ---- PART D: POINTERS AS STRUCT MEMBERS ----
    step10_connecting_structs();
    step11_finding_relationships();
    step12_pointer_arrays();
    
    // ---- PART E: ADVANCED TECHNIQUES ----
    step13_double_pointers();
    step14_sorting_pointers();
    
    // ---- PART F: COMPLETE SYSTEM ----
    // step15_complete_system();
    
    cout << "Lecture complete!" << endl;
    
    return 0;
}
