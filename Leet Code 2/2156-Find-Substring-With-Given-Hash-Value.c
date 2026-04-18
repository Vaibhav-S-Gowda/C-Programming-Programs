#include <stdio.h>
#include <string.h>

// Fast modular exponentiation: (power^k) % m
int getPow(int power, int k, int m) {
    int p = 1;
    long long v = power % m;

    while (k) {
        if (k & 1) {
            p = (p * v) % m;
        }
        v = (v * v) % m;
        k >>= 1;
    }
    return p;
}

// Returns substring of length k with given hashValue
char* subStrHash(char* s, int power, int modulo, int k, int hashValue) {
    long long kpow = getPow(power, k, modulo);
    int l = strlen(s);

    long long h = 0;
    int best = 0;

    for (int i = l - 1; i >= 0; --i) {
        // Add current character
        h = (h * power + (s[i] - 'a' + 1)) % modulo;

        // Remove character that goes out of window
        if (i + k < l) {
            h = (h - (long long)(s[i + k] - 'a' + 1) * kpow % modulo + modulo) % modulo;
        }

        // Check hash match
        if (h == hashValue) {
            best = i;
        }
    }

    // Terminate substring
    s[best + k] = '\0';

    return s + best;
}

// Driver code
int main() {
    char s[] = "leetcode";
    int power = 7;
    int modulo = 20;
    int k = 2;
    int hashValue = 0;

    char* result = subStrHash(s, power, modulo, k, hashValue);

    printf("Result substring: %s\n", result);

    return 0;
}