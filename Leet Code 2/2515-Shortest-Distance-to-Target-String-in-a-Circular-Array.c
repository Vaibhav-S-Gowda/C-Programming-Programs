#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Logic:
 * 1. Iterate through the array.
 * 2. When 'target' is found at index 'i', calculate:
 * - Direct distance: |i - startIndex|
 * - Circular distance: totalSize - |i - startIndex|
 * 3. The minimum of these two is the shortest path for that specific index.
 */
int closetTarget(char** words, int wordsSize, char* target, int startIndex) {
    int minDistance = -1;

    for (int i = 0; i < wordsSize; i++) {
        if (strcmp(words[i], target) == 0) {
            // Absolute difference between indices
            int absDist = abs(i - startIndex);
            
            // The shortest path in a circle is either the direct distance 
            // or the distance going the "long way" around the wrap-around point.
            int currentDist = absDist < (wordsSize - absDist) ? absDist : (wordsSize - absDist);
            
            if (minDistance == -1 || currentDist < minDistance) {
                minDistance = currentDist;
            }
        }
    }

    return minDistance;
}

int main() {
    // Example Data
    char* words[] = {"hello", "i", "am", "leetcode", "hello"};
    char* target = "hello";
    int startIndex = 1;
    int wordsSize = 5;

    // Call the function
    int result = closetTarget(words, wordsSize, target, startIndex);

    // Output Result
    printf("Target: %s\n", target);
    printf("Start Index: %d\n", startIndex);
    printf("Shortest Distance: %d\n", result);

    return 0;
}