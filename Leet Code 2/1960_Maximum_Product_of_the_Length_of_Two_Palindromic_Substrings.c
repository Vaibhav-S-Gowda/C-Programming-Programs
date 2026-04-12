#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

long long maxProduct(char * s) {
    int n = strlen(s);
    int *p = (int *)malloc(n * sizeof(int)); // Manacher radii
    int center = 0, right = 0;

    // 1. Manacher's Algorithm for odd-length palindromes
    for (int i = 0; i < n; i++) {
        p[i] = (i < right) ? MIN(right - i, p[2 * center - i]) : 0;
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n && s[i - p[i] - 1] == s[i + p[i] + 1]) {
            p[i]++;
        }
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
    }

    // 2. Precompute max odd palindrome length ending at each prefix
    long long *left_max = (long long *)malloc(n * sizeof(long long));
    int curr_idx = 0;
    for (int i = 0; i < n; i++) {
        // Find the first center that covers index 'i' at its right boundary
        while (curr_idx < n && curr_idx + p[curr_idx] < i) {
            curr_idx++;
        }
        left_max[i] = (i - curr_idx) * 2 + 1;
        if (i > 0) left_max[i] = MAX(left_max[i], left_max[i - 1]);
    }

    // 3. Precompute max odd palindrome length starting at each suffix
    long long *right_max = (long long *)malloc(n * sizeof(long long));
    curr_idx = n - 1;
    for (int i = n - 1; i >= 0; i--) {
        // Find the last center that covers index 'i' at its left boundary
        while (curr_idx >= 0 && curr_idx - p[curr_idx] > i) {
            curr_idx--;
        }
        right_max[i] = (curr_idx - i) * 2 + 1;
        if (i < n - 1) right_max[i] = MAX(right_max[i], right_max[i + 1]);
    }

    // 4. Find the maximum product of non-intersecting substrings
    long long ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans = MAX(ans, left_max[i] * right_max[i + 1]);
    }

    free(p);
    free(left_max);
    free(right_max);
    return ans;
}

int main() {
    char s[] = "ababbb";
    printf("%lld\n", maxProduct(s)); // Expected: 9
    return 0;
}