#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* mergeAlternately(char* word1, char* word2) {
    int n1 = strlen(word1);
    int n2 = strlen(word2);

    // Allocate memory for result (+1 for null terminator)
    char* result = (char*)malloc((n1 + n2 + 1) * sizeof(char));

    int i = 0, j = 0, k = 0;

    // Alternate characters
    while (i < n1 && j < n2) {
        result[k++] = word1[i++];
        result[k++] = word2[j++];
    }

    // Append remaining characters
    while (i < n1) {
        result[k++] = word1[i++];
    }

    while (j < n2) {
        result[k++] = word2[j++];
    }

    // Null terminate the string
    result[k] = '\0';

    return result;
}

int main() {
    char word1[] = "abc";
    char word2[] = "pqr";

    char* merged = mergeAlternately(word1, word2);
    printf("%s\n", merged);

    free(merged); // Always free allocated memory
    return 0;
}