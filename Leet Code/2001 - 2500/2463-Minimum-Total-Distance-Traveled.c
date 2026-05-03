#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

// Comparison function for sorting robots
int compare(const void* a, const void* b) {
    long long arg1 = *(int*)a;
    long long arg2 = *(int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

// Comparison function for sorting factories by position
int compareFactories(const void* a, const void* b) {
    int* f1 = *(int**)a;
    int* f2 = *(int**)b;
    return f1[0] - f2[0];
}

long long minimumTotalDistance(int* robot, int robotSize, int** factory, int factorySize, int* factoryColSize) {
    qsort(robot, robotSize, sizeof(int), compare);
    qsort(factory, factorySize, sizeof(int*), compareFactories);

    // Flatten factory slots into a single array of positions
    long long* positions = (long long*)malloc(10001 * sizeof(long long));
    int totalSlots = 0;
    for (int i = 0; i < factorySize; i++) {
        for (int j = 0; j < factory[i][1]; j++) {
            positions[totalSlots++] = factory[i][0];
        }
    }

    // DP array (Space optimized to 1D)
    long long* dp = (long long*)malloc((totalSlots + 1) * sizeof(long long));
    for (int j = 0; j <= totalSlots; j++) dp[j] = 0;

    for (int i = 0; i < robotSize; i++) {
        long long prev = dp[0];
        dp[0] = 1e15; // Represents infinity
        for (int j = 1; j <= totalSlots; j++) {
            long long temp = dp[j];
            long long val = prev + llabs((long long)robot[i] - positions[j - 1]);
            if (dp[j - 1] < val) val = dp[j - 1];
            dp[j] = val;
            prev = temp;
        }
    }

    long long result = dp[totalSlots];
    free(positions);
    free(dp);
    return result;
}

int main() {
    // Example Case
    int robot[] = {0, 4, 6};
    int robotSize = 3;

    // Factory data: {position, limit}
    int f1[] = {2, 2};
    int f2[] = {6, 2};
    int* factory[] = {f1, f2};
    int factorySize = 2;
    int factoryColSize[] = {2, 2};

    long long result = minimumTotalDistance(robot, robotSize, factory, factorySize, factoryColSize);

    printf("Minimum Total Distance: %lld\n", result);

    return 0;
}