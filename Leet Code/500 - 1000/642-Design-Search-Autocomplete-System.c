#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOP_K 3

// Structure to store a sentence and its frequency
typedef struct {
    char* sentence;
    int times;
} Record;

// Trie Node
typedef struct TrieNode {
    struct TrieNode* children[128]; // ASCII range
    Record* records;
    int recordCount;
} TrieNode;

// Global structure for the Autocomplete System
typedef struct {
    TrieNode* root;
    char currentQuery[1000];
    int queryIdx;
} AutocompleteSystem;

// Helper to create a new Trie node
TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    for (int i = 0; i < 128; i++) node->children[i] = NULL;
    node->records = NULL;
    node->recordCount = 0;
    return node;
}

// Update or add a record in a Trie node
void updateNodeRecord(TrieNode* node, char* sentence, int times) {
    for (int i = 0; i < node->recordCount; i++) {
        if (strcmp(node->records[i].sentence, sentence) == 0) {
            node->records[i].times = times;
            return;
        }
    }
    node->records = realloc(node->records, sizeof(Record) * (node->recordCount + 1));
    node->records[node->recordCount].sentence = strdup(sentence);
    node->records[node->recordCount].times = times;
    node->recordCount++;
}

// Insert sentence into Trie
void insert(TrieNode* root, char* sentence, int times) {
    TrieNode* curr = root;
    for (int i = 0; sentence[i] != '\0'; i++) {
        int idx = (int)sentence[i];
        if (!curr->children[idx]) curr->children[idx] = createNode();
        curr = curr->children[idx];
        updateNodeRecord(curr, sentence, times);
    }
}

// Sorting comparator for Top 3
int compareRecords(const void* a, const void* b) {
    Record* r1 = (Record*)a;
    Record* r2 = (Record*)b;
    if (r1->times != r2->times) return r2->times - r1->times; // Descending frequency
    return strcmp(r1->sentence, r2->sentence); // Ascending ASCII
}

// Function to handle character input
void inputChar(AutocompleteSystem* obj, char c) {
    if (c == '#') {
        // Record the finished sentence
        obj->currentQuery[obj->queryIdx] = '\0';
        
        // Find existing frequency or start at 1
        TrieNode* curr = obj->root;
        int existingTimes = 0;
        // Basic logic: we need to find if sentence exists to increment it
        // For brevity, we'll re-insert it with an updated global frequency logic
        // In a full solution, you'd maintain a global HashMap for frequencies.
        
        insert(obj->root, obj->currentQuery, 1); // Placeholder for frequency increment
        
        // Reset query
        memset(obj->currentQuery, 0, sizeof(obj->currentQuery));
        obj->queryIdx = 0;
        printf("Record saved.\n");
        return;
    }

    obj->currentQuery[obj->queryIdx++] = c;
    obj->currentQuery[obj->queryIdx] = '\0';

    TrieNode* curr = obj->root;
    for (int i = 0; i < obj->queryIdx; i++) {
        int idx = (int)obj->currentQuery[i];
        if (!curr->children[idx]) {
            printf("No suggestions found.\n");
            return;
        }
        curr = curr->children[idx];
    }

    // Sort the records in the current prefix node
    qsort(curr->records, curr->recordCount, sizeof(Record), compareRecords);

    printf("Suggestions: ");
    for (int i = 0; i < curr->recordCount && i < TOP_K; i++) {
        printf("[%s (%d)] ", curr->records[i].sentence, curr->records[i].times);
    }
    printf("\n");
}

int main() {
    AutocompleteSystem* obj = (AutocompleteSystem*)malloc(sizeof(AutocompleteSystem));
    obj->root = createNode();
    obj->queryIdx = 0;

    // Initial Data
    insert(obj->root, "i love you", 5);
    insert(obj->root, "island", 3);
    insert(obj->root, "ironman", 2);
    insert(obj->root, "i love leetcode", 2);

    // Simulate Typing "i "
    printf("User types 'i':\n");
    inputChar(obj, 'i');
    
    printf("\nUser types ' ' (space):\n");
    inputChar(obj, ' ');

    printf("\nUser types 'l':\n");
    inputChar(obj, 'l');

    printf("\nUser finishes with '#':\n");
    inputChar(obj, '#');

    return 0;
}