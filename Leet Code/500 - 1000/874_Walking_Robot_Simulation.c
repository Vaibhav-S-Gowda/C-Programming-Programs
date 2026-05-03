#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 20003 // A prime number larger than the max obstacles

typedef struct Node {
    long key;
    struct Node* next;
} Node;

typedef struct {
    Node* buckets[HASH_SIZE];
} HashTable;

// Hash function
int hash(long key) {
    int h = key % HASH_SIZE;
    return h < 0 ? h + HASH_SIZE : h;
}

// Insert into hash table
void insert(HashTable* table, long key) {
    int h = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = table->buckets[h];
    table->buckets[h] = newNode;
}

// Check if key exists
int contains(HashTable* table, long key) {
    int h = hash(key);
    Node* curr = table->buckets[h];
    while (curr) {
        if (curr->key == key) return 1;
        curr = curr->next;
    }
    return 0;
}

// Main robot simulation logic
int robotSim(int* commands, int commandsSize, int** obstacles, int obstaclesSize) {
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    HashTable table = {0};

    // Insert obstacles into hash table
    for (int i = 0; i < obstaclesSize; i++) {
        long key = (long)(obstacles[i][0] + 30000) * 60001 + (obstacles[i][1] + 30000);
        insert(&table, key);
    }

    int x = 0, y = 0, dir = 0, maxDistSq = 0;

    for (int i = 0; i < commandsSize; i++) {
        if (commands[i] == -2) {
            dir = (dir + 3) % 4; // left
        } else if (commands[i] == -1) {
            dir = (dir + 1) % 4; // right
        } else {
            for (int k = 0; k < commands[i]; k++) {
                int nextX = x + dx[dir];
                int nextY = y + dy[dir];

                long key = (long)(nextX + 30000) * 60001 + (nextY + 30000);

                if (contains(&table, key)) break;

                x = nextX;
                y = nextY;

                int distSq = x * x + y * y;
                if (distSq > maxDistSq) maxDistSq = distSq;
            }
        }
    }

    // Free memory
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* curr = table.buckets[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    return maxDistSq;
}

// Driver code
int main() {
    int commands[] = {4, -1, 3};
    int commandsSize = sizeof(commands) / sizeof(commands[0]);

    int obs1[] = {2, 4};
    int* obstacles[] = {obs1};
    int obstaclesSize = 1;

    int result = robotSim(commands, commandsSize, obstacles, obstaclesSize);

    printf("Maximum distance squared: %d\n", result);

    return 0;
}