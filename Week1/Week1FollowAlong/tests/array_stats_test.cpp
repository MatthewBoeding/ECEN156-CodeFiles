#include <gtest/gtest.h>
#include "array_stats.h"

// Tests for findMax function
TEST(ArrayStatsTest, FindsMaxInArray) {
    int arr[] = {3, 7, 2, 9, 4};
    EXPECT_EQ(findMax(arr, 5), 9);
}

TEST(ArrayStatsTest, FindsMaxInDifferentArray) {
    int arr[] = {15, 2, 8, 23, 11};
    EXPECT_EQ(findMax(arr, 5), 23);
}

TEST(ArrayStatsTest, HandlesNegativeNumbers) {
    int arr[] = {-5, -2, -8, -1};
    EXPECT_EQ(findMax(arr, 4), -1);
}

TEST(ArrayStatsTest, HandlesSingleElement) {
    int arr[] = {42};
    EXPECT_EQ(findMax(arr, 1), 42);
}

TEST(ArrayStatsTest, FindsMaxWhenFirstElementIsMax) {
    int arr[] = {100, 50, 25, 10};
    EXPECT_EQ(findMax(arr, 4), 100);
}

TEST(ArrayStatsTest, FindsMaxWhenLastElementIsMax) {
    int arr[] = {10, 25, 50, 100};
    EXPECT_EQ(findMax(arr, 4), 100);
}

// Tests for calculateAverage function
TEST(ArrayStatsTest, CalculatesAverage) {
    int arr[] = {2, 4, 6, 8, 10};
    EXPECT_DOUBLE_EQ(calculateAverage(arr, 5), 6.0);
}

TEST(ArrayStatsTest, AverageHandlesNegatives) {
    int arr[] = {-10, 0, 10};
    EXPECT_DOUBLE_EQ(calculateAverage(arr, 3), 0.0);
}

TEST(ArrayStatsTest, AverageHandlesDecimals) {
    int arr[] = {1, 2, 3};
    EXPECT_DOUBLE_EQ(calculateAverage(arr, 3), 2.0);
}

TEST(ArrayStatsTest, AverageSingleElement) {
    int arr[] = {42};
    EXPECT_DOUBLE_EQ(calculateAverage(arr, 1), 42.0);
}

TEST(ArrayStatsTest, AverageAllSameValues) {
    int arr[] = {5, 5, 5, 5, 5};
    EXPECT_DOUBLE_EQ(calculateAverage(arr, 5), 5.0);
}

// Tests for countAbove function
TEST(ArrayStatsTest, CountsValuesAboveThreshold) {
    int arr[] = {1, 5, 3, 8, 2, 9, 4};
    EXPECT_EQ(countAbove(arr, 7, 5), 2);  // 8 and 9 are above 5
}

TEST(ArrayStatsTest, CountAboveReturnsZeroWhenNone) {
    int arr[] = {1, 2, 3};
    EXPECT_EQ(countAbove(arr, 3, 10), 0);
}

TEST(ArrayStatsTest, CountAboveReturnsAllWhenAllQualify) {
    int arr[] = {5, 6, 7, 8};
    EXPECT_EQ(countAbove(arr, 4, 4), 4);
}

TEST(ArrayStatsTest, CountAboveWithNegativeThreshold) {
    int arr[] = {-5, 0, 5, 10};
    EXPECT_EQ(countAbove(arr, 4, -1), 3);  // 0, 5, 10 are above -1
}

TEST(ArrayStatsTest, CountAboveWithNegativeNumbers) {
    int arr[] = {-10, -5, -3, -8};
    EXPECT_EQ(countAbove(arr, 4, -6), 2);  // -5 and -3 are above -6
}

TEST(ArrayStatsTest, CountAboveSingleElement) {
    int arr[] = {10};
    EXPECT_EQ(countAbove(arr, 1, 5), 1);
    EXPECT_EQ(countAbove(arr, 1, 15), 0);
}
