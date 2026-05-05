#include <stdio.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    static char prefix[201]; 

    if (strsSize == 0) return "";

    strcpy(prefix, strs[0]);

    for (int i = 1; i < strsSize; i++) {
        int j = 0;

        while (prefix[j] != '\0' && strs[i][j] != '\0' && prefix[j] == strs[i][j]) {
            j++;
        }

        prefix[j] = '\0';

        if (prefix[0] == '\0') break;
    }

    return prefix;
}

int main() {
    char* input[] = {"flower", "flow", "flight"};
    int size = 3;

    char* result = longestCommonPrefix(input, size);
    
    printf("Input: [\"flower\", \"flow\", \"flight\"]\n");
    printf("Longest Common Prefix: \"%s\"\n", result);

    return 0;
}