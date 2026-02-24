#include <gtest/gtest.h>
#include "array_functions.h"

// ============================================================================
// ASSIGNMENT: Implement the functions in array_functions.cpp to make all 
// tests pass. Use Test-Driven Development principles:
// 1. Read each test to understand what the function should do
// 2. Implement the function in array_functions.cpp
// 3. Run the tests to verify your implementation
// 4. Move to the next function
//
// DO NOT modify this test file!
// ============================================================================

// ----------------------------------------------------------------------------
// Tests for findMin - Find the minimum value in an array
// ----------------------------------------------------------------------------
TEST(ArrayFunctionsTest, FindsMinInArray) {
    int arr[] = {3, 7, 2, 9, 4};
    EXPECT_EQ(findMin(arr, 5), 2);
}

TEST(ArrayFunctionsTest, FindsMinInDifferentArray) {
    int arr[] = {15, 2, 8, 23, 11};
    EXPECT_EQ(findMin(arr, 5), 2);
}

TEST(ArrayFunctionsTest, FindMinHandlesNegativeNumbers) {
    int arr[] = {-5, -2, -8, -1};
    EXPECT_EQ(findMin(arr, 4), -8);
}

TEST(ArrayFunctionsTest, FindMinHandlesSingleElement) {
    int arr[] = {42};
    EXPECT_EQ(findMin(arr, 1), 42);
}

TEST(ArrayFunctionsTest, FindMinWhenFirstElementIsMin) {
    int arr[] = {10, 50, 25, 100};
    EXPECT_EQ(findMin(arr, 4), 10);
}

TEST(ArrayFunctionsTest, FindMinWhenLastElementIsMin) {
    int arr[] = {100, 50, 25, 10};
    EXPECT_EQ(findMin(arr, 4), 10);
}

// ----------------------------------------------------------------------------
// Tests for sumArray - Calculate the sum of all elements
// ----------------------------------------------------------------------------
TEST(ArrayFunctionsTest, SumsPositiveNumbers) {
    int arr[] = {1, 2, 3, 4, 5};
    EXPECT_EQ(sumArray(arr, 5), 15);
}

TEST(ArrayFunctionsTest, SumHandlesNegativeNumbers) {
    int arr[] = {-5, -3, -2};
    EXPECT_EQ(sumArray(arr, 3), -10);
}

TEST(ArrayFunctionsTest, SumHandlesMixedNumbers) {
    int arr[] = {10, -5, 3, -2, 4};
    EXPECT_EQ(sumArray(arr, 5), 10);
}

TEST(ArrayFunctionsTest, SumSingleElement) {
    int arr[] = {42};
    EXPECT_EQ(sumArray(arr, 1), 42);
}

TEST(ArrayFunctionsTest, SumWithZeros) {
    int arr[] = {0, 0, 0, 5};
    EXPECT_EQ(sumArray(arr, 4), 5);
}

// ----------------------------------------------------------------------------
// Tests for countEvens - Count how many even numbers are in the array
// ----------------------------------------------------------------------------
TEST(ArrayFunctionsTest, CountsEvenNumbers) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    EXPECT_EQ(countEvens(arr, 6), 3);  // 2, 4, 6
}

TEST(ArrayFunctionsTest, CountEvensAllOdd) {
    int arr[] = {1, 3, 5, 7, 9};
    EXPECT_EQ(countEvens(arr, 5), 0);
}

TEST(ArrayFunctionsTest, CountEvensAllEven) {
    int arr[] = {2, 4, 6, 8};
    EXPECT_EQ(countEvens(arr, 4), 4);
}

TEST(ArrayFunctionsTest, CountEvensIncludesZero) {
    int arr[] = {0, 1, 2, 3};
    EXPECT_EQ(countEvens(arr, 4), 2);  // 0 and 2
}

TEST(ArrayFunctionsTest, CountEvensWithNegatives) {
    int arr[] = {-4, -3, -2, -1, 0, 1, 2};
    EXPECT_EQ(countEvens(arr, 7), 4);  // -4, -2, 0, 2
}

// ----------------------------------------------------------------------------
// Tests for findIndex - Find the index of a value in the array
// Return -1 if not found
// ----------------------------------------------------------------------------
TEST(ArrayFunctionsTest, FindsIndexOfValue) {
    int arr[] = {10, 20, 30, 40, 50};
    EXPECT_EQ(findIndex(arr, 5, 30), 2);
}

TEST(ArrayFunctionsTest, FindsIndexAtBeginning) {
    int arr[] = {5, 10, 15, 20};
    EXPECT_EQ(findIndex(arr, 4, 5), 0);
}

TEST(ArrayFunctionsTest, FindsIndexAtEnd) {
    int arr[] = {5, 10, 15, 20};
    EXPECT_EQ(findIndex(arr, 4, 20), 3);
}

TEST(ArrayFunctionsTest, FindIndexReturnsNegativeOneWhenNotFound) {
    int arr[] = {1, 2, 3, 4, 5};
    EXPECT_EQ(findIndex(arr, 5, 99), -1);
}

TEST(ArrayFunctionsTest, FindIndexWithNegativeNumbers) {
    int arr[] = {-10, -5, 0, 5, 10};
    EXPECT_EQ(findIndex(arr, 5, -5), 1);
}

TEST(ArrayFunctionsTest, FindIndexReturnsFirstOccurrence) {
    int arr[] = {3, 7, 3, 9, 3};
    EXPECT_EQ(findIndex(arr, 5, 3), 0);  // Returns first occurrence
}

// ----------------------------------------------------------------------------
// Tests for countRange - Count values within a range [min, max] (inclusive)
// ----------------------------------------------------------------------------
TEST(ArrayFunctionsTest, CountsValuesInRange) {
    int arr[] = {1, 5, 3, 8, 2, 9, 4};
    EXPECT_EQ(countRange(arr, 7, 3, 6), 3);  // 3, 4, 5
}

TEST(ArrayFunctionsTest, CountRangeIncludesBoundaries) {
    int arr[] = {1, 2, 3, 4, 5};
    EXPECT_EQ(countRange(arr, 5, 2, 4), 3);  // 2, 3, 4
}

TEST(ArrayFunctionsTest, CountRangeNoneInRange) {
    int arr[] = {1, 2, 3};
    EXPECT_EQ(countRange(arr, 3, 10, 20), 0);
}

TEST(ArrayFunctionsTest, CountRangeAllInRange) {
    int arr[] = {5, 6, 7, 8};
    EXPECT_EQ(countRange(arr, 4, 5, 8), 4);
}

TEST(ArrayFunctionsTest, CountRangeWithNegatives) {
    int arr[] = {-10, -5, 0, 5, 10};
    EXPECT_EQ(countRange(arr, 5, -6, 1), 2);  // -5, 0
}

// ----------------------------------------------------------------------------
// Tests for reverseArray - Reverse the array in place
// ----------------------------------------------------------------------------
TEST(ArrayFunctionsTest, ReversesArray) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {5, 4, 3, 2, 1};
    reverseArray(arr, 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(ArrayFunctionsTest, ReversesEvenLengthArray) {
    int arr[] = {1, 2, 3, 4};
    int expected[] = {4, 3, 2, 1};
    reverseArray(arr, 4);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(ArrayFunctionsTest, ReversesSingleElement) {
    int arr[] = {42};
    reverseArray(arr, 1);
    EXPECT_EQ(arr[0], 42);
}

TEST(ArrayFunctionsTest, ReversesTwoElements) {
    int arr[] = {1, 2};
    reverseArray(arr, 2);
    EXPECT_EQ(arr[0], 2);
    EXPECT_EQ(arr[1], 1);
}

// ----------------------------------------------------------------------------
// Tests for isPalindrome - Check if array is a palindrome
// (reads the same forwards and backwards)
// ----------------------------------------------------------------------------
TEST(ArrayFunctionsTest, DetectsPalindrome) {
    int arr[] = {1, 2, 3, 2, 1};
    EXPECT_TRUE(isPalindrome(arr, 5));
}

TEST(ArrayFunctionsTest, DetectsEvenLengthPalindrome) {
    int arr[] = {1, 2, 2, 1};
    EXPECT_TRUE(isPalindrome(arr, 4));
}

TEST(ArrayFunctionsTest, DetectsNonPalindrome) {
    int arr[] = {1, 2, 3, 4, 5};
    EXPECT_FALSE(isPalindrome(arr, 5));
}

TEST(ArrayFunctionsTest, SingleElementIsPalindrome) {
    int arr[] = {42};
    EXPECT_TRUE(isPalindrome(arr, 1));
}

TEST(ArrayFunctionsTest, TwoSameElementsIsPalindrome) {
    int arr[] = {7, 7};
    EXPECT_TRUE(isPalindrome(arr, 2));
}

TEST(ArrayFunctionsTest, TwoDifferentElementsIsNotPalindrome) {
    int arr[] = {7, 8};
    EXPECT_FALSE(isPalindrome(arr, 2));
}

// ----------------------------------------------------------------------------
// Tests for rotateLeft - Rotate array left by n positions
// Example: [1,2,3,4,5] rotated left by 2 becomes [3,4,5,1,2]
// ----------------------------------------------------------------------------
TEST(ArrayFunctionsTest, RotatesLeftByOne) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {2, 3, 4, 5, 1};
    rotateLeft(arr, 5, 1);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(ArrayFunctionsTest, RotatesLeftByMultiple) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {3, 4, 5, 1, 2};
    rotateLeft(arr, 5, 2);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(ArrayFunctionsTest, RotateLeftByZero) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    rotateLeft(arr, 5, 0);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(ArrayFunctionsTest, RotateLeftByFullLength) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    rotateLeft(arr, 5, 5);  // Full rotation returns to original
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(ArrayFunctionsTest, RotateLeftMoreThanLength) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {3, 4, 5, 1, 2};
    rotateLeft(arr, 5, 7);  // Same as rotating by 2 (7 % 5 = 2)
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// ----------------------------------------------------------------------------
// Tests for removeDuplicates - Remove duplicates from sorted array
// Returns the new length (unique elements are at the beginning)
// ----------------------------------------------------------------------------
TEST(ArrayFunctionsTest, RemovesDuplicatesFromSortedArray) {
    int arr[] = {1, 1, 2, 2, 3, 4, 4, 5};
    int newLength = removeDuplicates(arr, 8);
    EXPECT_EQ(newLength, 5);
    // First 5 elements should be: 1, 2, 3, 4, 5
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
    EXPECT_EQ(arr[4], 5);
}

TEST(ArrayFunctionsTest, RemoveDuplicatesNoDuplicates) {
    int arr[] = {1, 2, 3, 4, 5};
    int newLength = removeDuplicates(arr, 5);
    EXPECT_EQ(newLength, 5);
}

TEST(ArrayFunctionsTest, RemoveDuplicatesAllSame) {
    int arr[] = {7, 7, 7, 7, 7};
    int newLength = removeDuplicates(arr, 5);
    EXPECT_EQ(newLength, 1);
    EXPECT_EQ(arr[0], 7);
}

TEST(ArrayFunctionsTest, RemoveDuplicatesSingleElement) {
    int arr[] = {42};
    int newLength = removeDuplicates(arr, 1);
    EXPECT_EQ(newLength, 1);
    EXPECT_EQ(arr[0], 42);
}

TEST(ArrayFunctionsTest, RemoveDuplicatesWithNegatives) {
    int arr[] = {-5, -5, -3, -3, 0, 0, 2, 2};
    int newLength = removeDuplicates(arr, 8);
    EXPECT_EQ(newLength, 4);
    EXPECT_EQ(arr[0], -5);
    EXPECT_EQ(arr[1], -3);
    EXPECT_EQ(arr[2], 0);
    EXPECT_EQ(arr[3], 2);
}
