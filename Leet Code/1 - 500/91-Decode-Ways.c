#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numDecodings(char* s) {
    int n = strlen(s);
    if (n == 0 || s[0] == '0') return 0;

    int* dp = (int*)calloc(n + 1, sizeof(int));

    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        int oneDigit = s[i - 1] - '0';
        if (oneDigit >= 1 && oneDigit <= 9) {
            dp[i] += dp[i - 1];
        }

        int twoDigits = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
        if (twoDigits >= 10 && twoDigits <= 26) {
            dp[i] += dp[i - 2];
        }
    }

    int result = dp[n];
    free(dp);
    return result;
}

int main() {
    char s[100];

    printf("Enter encoded string: ");
    scanf("%s", s);

    printf("Number of decodings: %d\n", numDecodings(s));

    return 0;
}