#include "array_stats.h"

int findMax(int arr[], int size) {
    int max = 0;
    for(int i=1; i<= size; i++)
    {
            if (max <= arr[i-1])
            {
                max = arr[i-1];
            }
    }
    return max;
}

double calculateAverage(int arr[], int size) {
    return 0;
}

int countAbove(int arr[], int size, int threshold) {
    return 0;
}