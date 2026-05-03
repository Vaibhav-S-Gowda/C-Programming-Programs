#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1. Helper function
int get_gcd(int a, int b) {
    while (b) {
        a %= b;
        int temp = a;
        a = b;
        b = temp;
    }
    return a;
}

// 2. Logic function
char* gcdOfStrings(char* str1, char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // Concatenation check
    char* s1s2 = (char*)malloc(len1 + len2 + 1);
    char* s2s1 = (char*)malloc(len1 + len2 + 1);
    sprintf(s1s2, "%s%s", str1, str2);
    sprintf(s2s1, "%s%s", str2, str1);

    if (strcmp(s1s2, s2s1) != 0) {
        free(s1s2); free(s2s1);
        char* empty = (char*)malloc(1);
        empty[0] = '\0';
        return empty;
    }

    free(s1s2); free(s2s1);

    int commonLen = get_gcd(len1, len2);
    char* result = (char*)malloc(commonLen + 1);
    strncpy(result, str1, commonLen);
    result[commonLen] = '\0';

    return result;
}

// 3. ONLY ONE MAIN FUNCTION ALLOWED
int main() {
    char* res1 = gcdOfStrings("ABCABC", "ABC");
    char* res2 = gcdOfStrings("ABABAB", "ABAB");

    if (res1) {
        printf("Result 1: %s\n", res1);
        free(res1);
    }
    if (res2) {
        printf("Result 2: %s\n", res2);
        free(res2);
    }

    return 0;
}