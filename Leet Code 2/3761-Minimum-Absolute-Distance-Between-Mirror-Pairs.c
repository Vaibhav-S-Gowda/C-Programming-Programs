#include <stdio.h>
#include <limits.h>

#ifndef LOCAL_BUILD
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("abm,avx,avx2,bmi,bmi2,fma,popcnt,lzcnt,tune=znver5")
#define NO_SANITIZE __attribute__((no_sanitize("all")))
#else
#define NO_SANITIZE
#endif

#define MAX_NUMS 100001
#define HASH_SIZE 200003
#define BASE 10
#define HASH_MULT1 0x85ebca6bU
#define HASH_MULT2 0xc2b2ae35U
#define HASH_SHIFT1 16
#define HASH_SHIFT2 13

typedef struct HashEntry {
    int key;
    int value;
    struct HashEntry* next;
} HashEntry;

static HashEntry entry_pool[MAX_NUMS];
static int pool_pos;
static HashEntry* hash_table[HASH_SIZE];
static int bucket_ver[HASH_SIZE];
static int g_ver;

// Hash function (Murmur-inspired)
static unsigned int hash_func(int key) {
    unsigned int hash_val = (unsigned int)key;
    hash_val ^= hash_val >> HASH_SHIFT1;
    hash_val *= HASH_MULT1;
    hash_val ^= hash_val >> HASH_SHIFT2;
    hash_val *= HASH_MULT2;
    hash_val ^= hash_val >> HASH_SHIFT1;
    return hash_val % HASH_SIZE;
}

// Lazy bucket clearing using versioning
static inline HashEntry* bucket_head(unsigned int bucket) {
    return (bucket_ver[bucket] == g_ver) ? hash_table[bucket] : NULL;
}

NO_SANITIZE static int hash_get(int key) {
    unsigned int bucket = hash_func(key);
    HashEntry* entry = bucket_head(bucket);

    while (entry != NULL) {
        if (entry->key == key) {
            return entry->value;
        }
        entry = entry->next;
    }
    return -1;
}

NO_SANITIZE static void hash_put(int key, int value) {
    unsigned int bucket = hash_func(key);
    HashEntry* entry = bucket_head(bucket);

    while (entry != NULL) {
        if (entry->key == key) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }

    HashEntry* new_entry = &entry_pool[pool_pos++];
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = bucket_head(bucket);

    bucket_ver[bucket] = g_ver;
    hash_table[bucket] = new_entry;
}

// Reverse digits of a number
static int reverse_number(int num) {
    int reversed = 0;
    while (num > 0) {
        reversed = (reversed * BASE) + (num % BASE);
        num /= BASE;
    }
    return reversed;
}

// Main logic
NO_SANITIZE
int minMirrorPairDistance(int* nums, int nums_size) {
    pool_pos = 0;
    g_ver++;

    int min_dist = INT_MAX;

    for (int idx = 0; idx < nums_size; idx++) {
        int current = nums[idx];

        int prev_idx = hash_get(current);
        if (prev_idx != -1) {
            int dist = idx - prev_idx;
            if (dist < min_dist) {
                min_dist = dist;
            }
        }

        int reversed = reverse_number(current);
        hash_put(reversed, idx);
    }

    return (min_dist == INT_MAX) ? -1 : min_dist;
}

// Driver code
int main() {
    int nums[] = {12, 21, 13, 31, 12};
    int size = sizeof(nums) / sizeof(nums[0]);

    int result = minMirrorPairDistance(nums, size);

    printf("Minimum Mirror Pair Distance: %d\n", result);

    return 0;
}