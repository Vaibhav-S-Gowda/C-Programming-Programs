#include <stdio.h>
#include <string.h>

// helper to reverse a portion of string
void reverse(char *s, int l, int r) {
    while (l < r) {
        char temp = s[l];
        s[l++] = s[r];
        s[r--] = temp;
    }
}

char* reverseWords(char* s) {
    int n = strlen(s);
    
    // Step 1: Remove extra spaces
    int i = 0, j = 0;
    while (j < n) {
        while (j < n && s[j] == ' ') j++;            // skip spaces
        while (j < n && s[j] != ' ') s[i++] = s[j++]; // copy word
        while (j < n && s[j] == ' ') j++;            // skip spaces
        if (j < n) s[i++] = ' ';                     // add single space
    }
    s[i] = '\0';

    // Step 2: Reverse entire string
    reverse(s, 0, i - 1);

    // Step 3: Reverse each word
    int start = 0;
    for (int end = 0; end <= i; end++) {
        if (s[end] == ' ' || s[end] == '\0') {
            reverse(s, start, end - 1);
            start = end + 1;
        }
    }

    return s;
}

int main() {
    char s[1000];

    printf("Enter a string: ");
    fgets(s, sizeof(s), stdin);

    // remove newline from fgets
    s[strcspn(s, "\n")] = '\0';

    char *result = reverseWords(s);

    printf("Reversed words: %s\n", result);

    return 0;
}