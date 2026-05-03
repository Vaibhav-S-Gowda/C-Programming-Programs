#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Manhattan distance on a 6-column keyboard grid
int getDist(int a, int b) {
    if (a == 26 || b == 26) return 0; // "Hovering" state costs 0 to move to any key
    int r1 = a / 6, c1 = a % 6;
    int r2 = b / 6, c2 = b % 6;
    return abs(r1 - r2) + abs(c1 - c2);
}

int minimumDistance(char * word) {
    int n = strlen(word);
    int dp[27]; 
    
    // Initialize with a large value (infinity)
    for (int i = 0; i < 27; i++) dp[i] = 1000000;
    
    // Starting state: one finger at first char, other finger is 'unplaced' (26)
    dp[26] = 0;
    int prev = word[0] - 'A';
    
    for (int i = 1; i < n; i++) {
        int curr = word[i] - 'A';
        int next_dp[27];
        for (int j = 0; j < 27; j++) next_dp[j] = 1000000;

        for (int other = 0; other < 27; other++) {
            if (dp[other] == 1000000) continue;

            // Option 1: Move the finger that was at 'prev' to 'curr'
            next_dp[other] = MIN(next_dp[other], dp[other] + getDist(prev, curr));

            // Option 2: Move the 'other' finger to 'curr'
            // The finger previously at 'prev' now becomes the new 'other'
            next_dp[prev] = MIN(next_dp[prev], dp[other] + getDist(other, curr));
        }
        memcpy(dp, next_dp, sizeof(dp));
        prev = curr;
    }

    int result = 1000000;
    for (int i = 0; i < 27; i++) result = MIN(result, dp[i]);
    return result;
}

int main() {
    char *test1 = "CAKE";
    char *test2 = "HAPPY";
    char *test3 = "NEWYEAR";

    printf("Word: %s | Min Distance: %d\n", test1, minimumDistance(test1)); // Expected: 3
    printf("Word: %s | Min Distance: %d\n", test2, minimumDistance(test2)); // Expected: 6
    printf("Word: %s | Min Distance: %d\n", test3, minimumDistance(test3)); // Expected: 7

    return 0;
}