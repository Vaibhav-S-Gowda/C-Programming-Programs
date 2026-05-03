#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CHARS 26

char* alienOrder(char** words, int wordsSize) {
    int adj[MAX_CHARS][MAX_CHARS] = {0};
    int inDegree[MAX_CHARS];
    
    // Initialize in-degree with -1 (not present)
    for (int i = 0; i < MAX_CHARS; i++) inDegree[i] = -1;

    // Mark characters that actually appear in the input
    int totalChars = 0;
    for (int i = 0; i < wordsSize; i++) {
        for (int j = 0; words[i][j] != '\0'; j++) {
            int c = words[i][j] - 'a';
            if (inDegree[c] == -1) {
                inDegree[c] = 0;
                totalChars++;
            }
        }
    }

    // Build the graph by comparing adjacent words
    for (int i = 0; i < wordsSize - 1; i++) {
        char* w1 = words[i];
        char* w2 = words[i + 1];
        int len1 = strlen(w1), len2 = strlen(w2);
        bool foundDifference = false;
        
        for (int j = 0; j < len1 && j < len2; j++) {
            if (w1[j] != w2[j]) {
                int u = w1[j] - 'a';
                int v = w2[j] - 'a';
                if (!adj[u][v]) {
                    adj[u][v] = 1;
                    inDegree[v]++;
                }
                foundDifference = true;
                break;
            }
        }
        // Prefix check: "abc" cannot come before "ab"
        if (!foundDifference && len1 > len2) return "";
    }

    // BFS (Kahn's Algorithm)
    char* result = (char*)malloc((totalChars + 1) * sizeof(char));
    int queue[MAX_CHARS], head = 0, tail = 0, resIdx = 0;

    // Add all nodes with 0 in-degree to the queue
    for (int i = 0; i < MAX_CHARS; i++) {
        if (inDegree[i] == 0) queue[tail++] = i;
    }

    while (head < tail) {
        int u = queue[head++];
        result[resIdx++] = u + 'a';

        for (int v = 0; v < MAX_CHARS; v++) {
            if (adj[u][v]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    queue[tail++] = v;
                }
            }
        }
    }

    result[resIdx] = '\0';

    // If we couldn't visit all characters, there's a cycle
    if (resIdx < totalChars) {
        free(result);
        return "";
    }

    return result;
}

int main() {
    // Example 1: Standard case
    char* words1[] = {"wrt", "wrf", "er", "ett", "rftt"};
    int size1 = 5;
    char* result1 = alienOrder(words1, size1);
    printf("Example 1: %s\n", (strlen(result1) > 0) ? result1 : "Invalid Order");
    free(result1);

    // Example 2: Cycle case (invalid)
    char* words2[] = {"z", "x", "z"};
    int size2 = 3;
    char* result2 = alienOrder(words2, size2);
    printf("Example 2: %s\n", (strlen(result2) > 0) ? result2 : "Invalid Order");
    // Only free if it wasn't a literal return of ""
    if (strlen(result2) > 0) free(result2); 

    return 0;
}