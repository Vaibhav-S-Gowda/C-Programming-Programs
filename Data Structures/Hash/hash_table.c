#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Node for separate chaining */
typedef struct Node {
    int key;
    struct Node* next;
} Node;

/* Hash table structure */
typedef struct {
    Node** table;   // array of linked-list heads
    int size;       // number of buckets
    int count;      // number of stored keys
} HashTable;

/* Create hash table */
HashTable* createHashTable(int size) {
    HashTable* ht = malloc(sizeof(HashTable));
    if (ht == NULL) return NULL;

    ht->size = size;
    ht->count = 0;
    ht->table = calloc(size, sizeof(Node*));
    if (ht->table == NULL) {
        free(ht);
        return NULL;
    }
    return ht;
}

/* Hash function */
int hash(int key, int size) {
    return key % size;
}

/* Insert key */
void insert(HashTable* ht, int key) {
    int index = hash(key, ht->size);
    Node* current = ht->table[index];

    /* Prevent duplicates */
    while (current != NULL) {
        if (current->key == key)
            return;
        current = current->next;
    }

    /* Insert at head */
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) return;

    newNode->key = key;
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
    ht->count++;
}

/* Search key */
bool search(HashTable* ht, int key) {
    int index = hash(key, ht->size);
    Node* current = ht->table[index];

    while (current != NULL) {
        if (current->key == key)
            return true;
        current = current->next;
    }
    return false;
}

/* Delete key */
bool delete(HashTable* ht, int key) {
    int index = hash(key, ht->size);
    Node* current = ht->table[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL)
                ht->table[index] = current->next;
            else
                prev->next = current->next;

            free(current);
            ht->count--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

/* Free entire hash table */
void destroyHashTable(HashTable* ht) {
    if (ht == NULL) return;

    for (int i = 0; i < ht->size; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

/* Test the hash table */
int main(void) {
    HashTable* ht = createHashTable(10);

    insert(ht, 10);
    insert(ht, 20);
    insert(ht, 15);
    insert(ht, 25);

    printf("Search 15: %s\n", search(ht, 15) ? "Found" : "Not Found");
    printf("Search 30: %s\n", search(ht, 30) ? "Found" : "Not Found");

    delete(ht, 15);
    printf("Search 15 after delete: %s\n",
           search(ht, 15) ? "Found" : "Not Found");

    destroyHashTable(ht);
    return 0;
}


// Hash Table
// Average: O(1)
// Worst: O(n)
// Space: O(n)


/*
    How Hash Tables Work
        A Hash Table is a data structure that implements an associative array, mapping keys to values using a hash function. 
        It provides fast insertion, deletion, and lookup operations by computing an index into an array of buckets.

    The key components are:

    Hash Function: Maps keys to array indices (e.g., key % table_size)
    Collision Resolution: Handles when multiple keys hash to the same index
    Chaining: Uses linked lists to store multiple elements at same index
    Load Factor: Ratio of elements to table size, affects performance
*/

/*

    Hash Functions
        • Division: h(k) = k mod m
        • Multiplication: h(k) = ⌊m(kA mod 1)⌋
        • Universal hashing: Randomized functions
        • Cryptographic: MD5, SHA for security

*/


/*

    Collision Resolution
        • Chaining: Linked lists at each index
        • Linear Probing: Check next available slot
        • Quadratic Probing: Check slots at quadratic intervals
        • Double Hashing: Use second hash function
        
*/