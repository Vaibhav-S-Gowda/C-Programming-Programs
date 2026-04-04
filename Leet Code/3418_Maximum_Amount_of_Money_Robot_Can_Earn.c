#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maximumAmount(int** coins, int coinsSize, int* coinsColSize) {
    int m = coinsSize;
    int n = coinsColSize[0];

    long long dp[505][505][3];

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < 3; k++)
                dp[i][j][k] = LLONG_MIN / 2;

    int start = coins[0][0];
    dp[0][0][0] = start;
    dp[0][0][1] = (start < 0) ? 0 : start;
    dp[0][0][2] = (start < 0) ? 0 : start;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) continue;

            int cv = coins[i][j];

            for (int k = 0; k < 3; k++) {
                long long best = LLONG_MIN / 2;

                if (i > 0 && dp[i-1][j][k] > best)
                    best = dp[i-1][j][k];

                if (j > 0 && dp[i][j-1][k] > best)
                    best = dp[i][j-1][k];

                if (best == LLONG_MIN / 2) continue;

                long long take = best + cv;
                if (take > dp[i][j][k])
                    dp[i][j][k] = take;

                if (cv < 0 && k < 2) {
                    if (best > dp[i][j][k+1])
                        dp[i][j][k+1] = best;
                }
            }
        }
    }

    long long ans = LLONG_MIN;
    for (int k = 0; k < 3; k++)
        if (dp[m-1][n-1][k] > ans)
            ans = dp[m-1][n-1][k];

    return (int)ans;
}

int main() {
    int m, n;

    printf("Enter rows and columns: ");
    scanf("%d %d", &m, &n);

    int** coins = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        coins[i] = (int*)malloc(n * sizeof(int));
    }

    int* coinsColSize = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        coinsColSize[i] = n;
    }

    printf("Enter grid values:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &coins[i][j]);
        }
    }

    int result = maximumAmount(coins, m, coinsColSize);

    printf("Maximum Amount: %d\n", result);

    for (int i = 0; i < m; i++) {
        free(coins[i]);
    }
    free(coins);
    free(coinsColSize);

    return 0;
}


// ---

// ## Walkthrough
// ```
// State:  dp[i][j][k]
//         │   │   └── neutralizations used so far (0, 1, or 2)
//         │   └────── column
//         └────────── row

// At every cell we make two choices:
// ┌─────────────────────────────────────────────────────┐
// │  Choice A │ Add coins[i][j] normally   → stay at k  │
// │  Choice B │ coins[i][j] < 0 AND k < 2              │
// │           │ Treat cell as 0            → move to k+1│
// └─────────────────────────────────────────────────────┘

// Transitions always come from:
//   • dp[i-1][j][k]  (moved down  into current cell)
//   • dp[i][j-1][k]  (moved right into current cell)

// Final answer = max(dp[m-1][n-1][0..2])