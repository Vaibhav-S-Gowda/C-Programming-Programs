#include <stdio.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int numWays(int steps, int arrLen) {
    int MOD = 1e9 + 7;
    
    // Optimization: You can't reach an index further than 'steps' away.
    // Also, you need to return to 0, so you can't go further than steps/2 
    // effectively, but 'steps' is a safe upper bound.
    int maxPos = MIN(steps, arrLen - 1);
    
    // dp[i] represents the number of ways to be at index i
    long dp[maxPos + 1];
    long next_dp[maxPos + 1];
    
    // Initialize DP table
    memset(dp, 0, sizeof(dp));
    dp[0] = 1; // Start at index 0

    for (int i = 1; i <= steps; i++) {
        memset(next_dp, 0, sizeof(next_dp));
        for (int j = 0; j <= maxPos; j++) {
            // Option 1: Stay in the same place
            next_dp[j] = dp[j];
            
            // Option 2: Move from the left (j-1)
            if (j > 0) {
                next_dp[j] = (next_dp[j] + dp[j - 1]) % MOD;
            }
            
            // Option 3: Move from the right (j+1)
            if (j < maxPos) {
                next_dp[j] = (next_dp[j] + dp[j + 1]) % MOD;
            }
        }
        // Copy next_dp to dp for the next iteration
        memcpy(dp, next_dp, sizeof(dp));
    }

    return (int)dp[0];
}

int main() {
    // Example 1
    int steps1 = 3, arrLen1 = 2;
    printf("Input: steps = %d, arrLen = %d\nOutput: %d\n\n", 
            steps1, arrLen1, numWays(steps1, arrLen1));

    // Example 2
    int steps2 = 2, arrLen2 = 4;
    printf("Input: steps = %d, arrLen = %d\nOutput: %d\n\n", 
            steps2, arrLen2, numWays(steps2, arrLen2));

    // Example 3
    int steps3 = 4, arrLen3 = 2;
    printf("Input: steps = %d, arrLen = %d\nOutput: %d\n", 
            steps3, arrLen3, numWays(steps3, arrLen3));

    return 0;
}