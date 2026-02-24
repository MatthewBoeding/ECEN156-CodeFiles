#include "array_functions.h"

// ============================================================================
// ASSIGNMENT: Week 1 lab
// NAME: Titus
// COURSE: Computer Science 2
// DATE:  1/15/26
// ============================================================================

int findMin(int arr[], int size) {
    int min = arr[0];
    //for loop to iterate through array
    for(int i = 0; i < size; i++){
        //check if newest number is less than current min, if true set numeber to min
        if(min > arr[i]){
            min = arr[i];
        }
    }
    return min;
}

int sumArray(int arr[], int size) {
    int sum = 0;
    //for loop to iterate through array
    for(int i = 0; i < size; i++){
        //add latest numer to the sum
        sum = sum + arr[i];
    }
    return sum;
}

int countEvens(int arr[], int size) {
    int total = 0;
    //for loop to iterate through array
    for(int i = 0; i < size; i++){
        //check if num is even if true add to counter
        if(arr[i] % 2 == 0){
            total++;
        }
    }
    return total;
}

int findIndex(int arr[], int size, int value) {
    //for loop to iterate through array
    for(int i = 0; i < size; i++){
        if(arr[i] == value){
            return i;
        }
    }
    return -1;
}

int countRange(int arr[], int size, int min, int max) {
    int total = 0;
    //for loop to iterate through array
    for(int i = 0; i < size; i++){
        //
        if(min <= arr[i] && max >= arr[i]){
            total++;
        }

    }
    return total;
}

void reverseArray(int arr[], int size) {
    //create a array and set to NULL
    int temp[size] = {0};
    //set temp array to arr array
    for(int i = 0; i < size; i++){
        temp[i] = arr[i];
    }
    //sets arr array to temp array backwards
    for(int i = 0; i < size; i++)
        arr[i] = temp[size-1-i];

}

bool isPalindrome(int arr[], int size) {
    //for loop to iterate through array
    for(int i = 0; i < size; i++){
        //checks to see if each side are un-equal if true return false
        if(arr[i] != arr[size - 1 - i]){
            return false;
        }
    }
    return true;
}

void rotateLeft(int arr[], int size, int n) {
    //create a array and set to NULL
    int temp[size] = {0};
    //set temp array to arr array
    for(int i = 0; i < size; i++){
        temp[i] = arr[i];
    }

    //for loop to iterate through array
    for(int i = 0; i < size - n; i++){
        // this shifts ie arr[1] = arr[2], arr[2] = arr[3], ect.
        arr[i] = arr[i + n];
    }
    //sets the last digits to the begining ones
    for(int i = 0; i < n; i++){
        arr[size-n+i] = temp[i];
    }
}

int removeDuplicates(int arr[], int size) {
    int total = 1;
    int j = 1;

    //for loop to iterate through array
    for(int i = 1; i < size; i++){
        //checks to see if last number is = to this number
        if(arr[i] != arr[i-1]){
            //increase counter
            total++;
            //stores unique num in begining of array
            arr[j] = arr[i];
            j++;
        }
    }
    return total;
}