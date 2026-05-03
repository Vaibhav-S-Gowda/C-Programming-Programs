#include <stdio.h>
#include <string.h>

int min(int a, int b, int c) {
    int m = a < b ? a : b;
    return m < c ? m : c;
}

int minDistance(char* word1, char* word2) {
    int m = strlen(word1);
    int n = strlen(word2);

    int dp[m+1][n+1];

    for (int i = 0; i <= m; i++)
        dp[i][0] = i;

    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (word1[i-1] == word2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = 1 + min(
                    dp[i-1][j],     // delete
                    dp[i][j-1],     // insert
                    dp[i-1][j-1]    // replace
                );
            }
        }
    }

    return dp[m][n];
}

int main() {
    char word1[] = "horse";
    char word2[] = "ros";

    int result = minDistance(word1, word2);

    printf("Minimum Edit Distance: %d\n", result);  // Expected: 3

    return 0;
}