#include <stdio.h>

/**
 * Logic: The maximum distance must involve either the first house 
 * or the last house to maximize the span. We check both scenarios.
 */
int maxDistance(int* colors, int colorsSize) {
    int n = colorsSize;
    
    // Scenario 1: Distance from the first house to the last different color house
    int right = n - 1;
    while (colors[right] == colors[0]) {
        right--;
    }
    int dist1 = right;

    // Scenario 2: Distance from the last house to the first different color house
    int left = 0;
    while (colors[left] == colors[n - 1]) {
        left++;
    }
    int dist2 = (n - 1) - left;

    return dist1 > dist2 ? dist1 : dist2;
}

int main() {
    // Example 1 from LeetCode: colors = [1, 1, 1, 6, 1, 1, 1]
    int houses1[] = {1, 1, 1, 6, 1, 1, 1};
    int size1 = sizeof(houses1) / sizeof(houses1[0]);
    printf("Example 1 Max Distance: %d\n", maxDistance(houses1, size1));

    // Example 2: colors = [1, 8, 3, 8, 3]
    int houses2[] = {1, 8, 3, 8, 3};
    int size2 = sizeof(houses2) / sizeof(houses2[0]);
    printf("Example 2 Max Distance: %d\n", maxDistance(houses2, size2));

    return 0;
}