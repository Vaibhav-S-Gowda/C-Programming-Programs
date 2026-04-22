#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Logic: Compare each query against all dictionary words.
 * Count differences (Hamming Distance). If diff <= 2, it's a match.
 */
char** twoEditWords(char** queries, int queriesSize, char** dictionary, int dictionarySize, int* returnSize) {
    char** result = (char**)malloc(queriesSize * sizeof(char*));
    int count = 0;
    int n = strlen(queries[0]);

    for (int i = 0; i < queriesSize; i++) {
        bool found = false;
        for (int j = 0; j < dictionarySize; j++) {
            int diff = 0;
            for (int k = 0; k < n; k++) {
                if (queries[i][k] != dictionary[j][k]) {
                    diff++;
                }
                if (diff > 2) break; // Optimization
            }
            if (diff <= 2) {
                found = true;
                break;
            }
        }
        
        if (found) {
            result[count] = (char*)malloc((n + 1) * sizeof(char));
            strcpy(result[count], queries[i]);
            count++;
        }
    }

    *returnSize = count;
    return result;
}

int main() {
    // Example 1 Inputs
    char* queries_arr[] = {"word", "note", "ants", "wood"};
    char* dictionary_arr[] = {"wood", "joke", "moat"};
    
    int queriesSize = 4;
    int dictionarySize = 3;
    int returnSize = 0;

    // Call the function
    char** result = twoEditWords(queries_arr, queriesSize, dictionary_arr, dictionarySize, &returnSize);

    // Print results
    printf("Words within 2 edits: [");
    for (int i = 0; i < returnSize; i++) {
        printf("%s%s", result[i], (i == returnSize - 1) ? "" : ", ");
    }
    printf("]\n");

    // Clean up memory
    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}