#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct {
    char* key;
    char** sentences;
    int count;
} MemoEntry;

MemoEntry memo[301];
int memoCount = 0;

// Custom strdup
char* my_strdup(const char* s) {
    char* result = (char*)malloc(strlen(s) + 1);
    strcpy(result, s);
    return result;
}

// Custom strndup
char* my_strndup(const char* s, int n) {
    char* result = (char*)malloc(n + 1);
    strncpy(result, s, n);
    result[n] = '\0';
    return result;
}

bool isInDict(char* word, char** wordDict, int wordDictSize) {
    for (int i = 0; i < wordDictSize; i++) {
        if (strcmp(word, wordDict[i]) == 0) return true;
    }
    return false;
}

char** dfs(char* s, char** wordDict, int wordDictSize, int* returnSize) {
    int n = strlen(s);

    // Check memo
    for (int i = 0; i < memoCount; i++) {
        if (strcmp(memo[i].key, s) == 0) {
            *returnSize = memo[i].count;
            return memo[i].sentences;
        }
    }

    char** result = NULL;
    int count = 0;

    // Base case
    if (n == 0) {
        result = (char**)malloc(sizeof(char*));
        result[0] = my_strdup("");
        *returnSize = 1;
        return result;
    }

    for (int i = 1; i <= n; i++) {
        char* prefix = my_strndup(s, i);

        if (isInDict(prefix, wordDict, wordDictSize)) {
            int subSize = 0;
            char** subSentences = dfs(s + i, wordDict, wordDictSize, &subSize);

            for (int j = 0; j < subSize; j++) {
                result = (char**)realloc(result, sizeof(char*) * (count + 1));

                if (strlen(subSentences[j]) == 0) {
                    result[count++] = my_strdup(prefix);
                } else {
                    char* combined = (char*)malloc(strlen(prefix) + strlen(subSentences[j]) + 2);
                    sprintf(combined, "%s %s", prefix, subSentences[j]);
                    result[count++] = combined;
                }
            }
        }

        free(prefix);
    }

    // Store in memo
    memo[memoCount].key = my_strdup(s);
    memo[memoCount].sentences = result;
    memo[memoCount].count = count;
    memoCount++;

    *returnSize = count;
    return result;
}

char** wordBreak(char* s, char** wordDict, int wordDictSize, int* returnSize) {
    memoCount = 0;
    return dfs(s, wordDict, wordDictSize, returnSize);
}

int main() {
    char s[] = "catsanddog";

    char* wordDict[] = {"cat", "cats", "and", "sand", "dog"};
    int wordDictSize = sizeof(wordDict) / sizeof(wordDict[0]);

    int returnSize;
    char** result = wordBreak(s, wordDict, wordDictSize, &returnSize);

    printf("Possible sentences:\n");
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", result[i]);
    }

    // Free memory
    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}


// The Decision Tree Trace
//
// Input: "catsanddog"
//
// Level 1: Try prefixes
// ├── "cat" (Valid) 
// │   └── Level 2: Remaining "sanddog"
// │       └── "sand" (Valid)
// │           └── Level 3: Remaining "dog"
// │               └── "dog" (Valid) -> FOUND: "cat sand dog"
// │
// ├── "cats" (Valid)
// │   └── Level 2: Remaining "anddog"
// │       └── "and" (Valid)
// │           └── Level 3: Remaining "dog"
// │               └── "dog" (Valid) -> FOUND: "cats and dog"
// │
// └── "catsa..." (Invalid)


// ASCII Memoization Table
//
// +----------------+----------------------------------+
// | Substring Key  | Found Sentences                  |
// +----------------+----------------------------------+
// | "dog"          | ["dog"]                          |
// | "sanddog"      | ["sand dog"]                     |
// | "anddog"       | ["and dog"]                      |
// | "catsanddog"   | ["cat sand dog", "cats and dog"] |
// +----------------+----------------------------------+


// Visualization of the Pointer "Slide"
//
// s = "catsanddog"
//        ^
//        |-- (cat) + dfs("sanddog")
//        |            ^
//        |            |-- (sand) + dfs("dog") -> "dog"
//        |
//        |-- (cats) + dfs("anddog")
//                     ^
//                     |-- (and) + dfs("dog") -> "dog"