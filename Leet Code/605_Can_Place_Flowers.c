#include <stdio.h>
#include <stdbool.h>

/**
 * Problem 605: Can Place Flowers
 * Logic: Iterate through the array and plant a flower if the current, 
 * previous, and next plots are all 0 (handling boundaries as 0).
 */
bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n) {
    int count = 0;
    
    // If n is 0, we've already technically succeeded
    if (n <= 0) return true;

    for (int i = 0; i < flowerbedSize; i++) {
        if (flowerbed[i] == 0) {
            // Check left: True if we are at index 0 OR the previous plot is 0
            bool leftEmpty = (i == 0) || (flowerbed[i - 1] == 0);
            
            // Check right: True if we are at the last index OR the next plot is 0
            bool rightEmpty = (i == flowerbedSize - 1) || (flowerbed[i + 1] == 0);

            if (leftEmpty && rightEmpty) {
                flowerbed[i] = 1; // Plant the flower
                count++;
                
                if (count >= n) {
                    return true;
                }
                
                // Optimization: If we plant here, we know the next index 
                // cannot have a flower, so we can skip it.
                i++; 
            }
        }
    }
    
    return count >= n;
}

int main() {
    // Test Case 1: Should be true (can plant 1 flower at index 0 or 4)
    int bed1[] = {1, 0, 0, 0, 1};
    int size1 = 5;
    int n1 = 1;
    printf("Test Case 1: %s\n", canPlaceFlowers(bed1, size1, n1) ? "true" : "false");

    // Test Case 2: Should be false (cannot plant 2 flowers in these gaps)
    int bed2[] = {1, 0, 0, 0, 1};
    int size2 = 5;
    int n2 = 2;
    printf("Test Case 2: %s\n", canPlaceFlowers(bed2, size2, n2) ? "true" : "false");

    // Test Case 3: Edge case (empty bed) - Should be true
    int bed3[] = {0, 0, 0};
    int size3 = 3;
    int n3 = 2;
    printf("Test Case 3: %s\n", canPlaceFlowers(bed3, size3, n3) ? "true" : "false");

    return 0;
}