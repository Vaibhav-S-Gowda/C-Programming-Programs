#include <stdio.h>
#include <string.h>

int lengthOfLongestSubstring(char *s) {
    int lastIndex[256];
    
    // Initialize all characters as not seen
    for (int i = 0; i < 256; i++) {
        lastIndex[i] = -1;
    }

    int maxLength = 0;
    int start = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (lastIndex[(unsigned char)s[i]] >= start) {
            start = lastIndex[(unsigned char)s[i]] + 1;
        }

        lastIndex[(unsigned char)s[i]] = i;

        int currentLength = i - start + 1;
        if (currentLength > maxLength) {
            maxLength = currentLength;
        }
    }

    return maxLength;
}

int main() {
    char s[] = "abcabcbb";

    int result = lengthOfLongestSubstring(s);

    printf("Length of longest substring without repeating characters: %d\n", result);  // Expected: 3

    return 0;
}