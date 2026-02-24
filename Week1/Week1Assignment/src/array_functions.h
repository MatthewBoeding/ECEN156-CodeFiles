#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H

// ============================================================================
// ASSIGNMENT: Implement these functions in array_functions.cpp
// Read the tests in array_functions_test.cpp to understand what each 
// function should do.
// ============================================================================

/**
 * Find the minimum value in an integer array
 * @param arr - the array to search
 * @param size - the number of elements in the array
 * @return the minimum value found
 */
int findMin(int arr[], int size);

/**
 * Calculate the sum of all elements in an integer array
 * @param arr - the array to sum
 * @param size - the number of elements in the array
 * @return the sum of all elements
 */
int sumArray(int arr[], int size);

/**
 * Count how many even numbers are in the array
 * @param arr - the array to search
 * @param size - the number of elements in the array
 * @return the count of even numbers
 */
int countEvens(int arr[], int size);

/**
 * Find the index of a value in the array
 * @param arr - the array to search
 * @param size - the number of elements in the array
 * @param value - the value to search for
 * @return the index of the first occurrence, or -1 if not found
 */
int findIndex(int arr[], int size, int value);

/**
 * Count how many values fall within a range [min, max] (inclusive)
 * @param arr - the array to search
 * @param size - the number of elements in the array
 * @param min - the minimum value of the range (inclusive)
 * @param max - the maximum value of the range (inclusive)
 * @return the count of values in range
 */
int countRange(int arr[], int size, int min, int max);

/**
 * Reverse the array in place
 * @param arr - the array to reverse (modified in place)
 * @param size - the number of elements in the array
 */
void reverseArray(int arr[], int size);

/**
 * Check if an array is a palindrome (reads same forwards and backwards)
 * @param arr - the array to check
 * @param size - the number of elements in the array
 * @return true if palindrome, false otherwise
 */
bool isPalindrome(int arr[], int size);

/**
 * Rotate array left by n positions
 * Example: [1,2,3,4,5] rotated left by 2 becomes [3,4,5,1,2]
 * @param arr - the array to rotate (modified in place)
 * @param size - the number of elements in the array
 * @param n - number of positions to rotate
 */
void rotateLeft(int arr[], int size, int n);

/**
 * Remove duplicates from a SORTED array
 * Unique elements will be at the beginning of the array
 * @param arr - the sorted array (modified in place)
 * @param size - the number of elements in the array
 * @return the new length (number of unique elements)
 */
int removeDuplicates(int arr[], int size);

#endif
