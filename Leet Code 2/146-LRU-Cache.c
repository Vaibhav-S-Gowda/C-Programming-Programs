#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key, val;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int cap;
    int size;
    Node** map;
} LRUCache;

void removeNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void addToHead(LRUCache* obj, Node* node) {
    node->prev = obj->head;
    node->next = obj->head->next;
    obj->head->next->prev = node;
    obj->head->next = node;
}

void moveToHead(LRUCache* obj, Node* node) {
    removeNode(node);
    addToHead(obj, node);
}

Node* removeTail(LRUCache* obj) {
    Node* node = obj->tail->prev;
    removeNode(node);
    return node;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* obj = malloc(sizeof(LRUCache));
    obj->cap = capacity;
    obj->size = 0;

    obj->map = calloc(10001, sizeof(Node*));

    obj->head = malloc(sizeof(Node));
    obj->tail = malloc(sizeof(Node));

    obj->head->prev = NULL;
    obj->head->next = obj->tail;
    obj->tail->prev = obj->head;
    obj->tail->next = NULL;

    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    if (!obj->map[key]) return -1;
    moveToHead(obj, obj->map[key]);
    return obj->map[key]->val;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if (obj->map[key]) {
        obj->map[key]->val = value;
        moveToHead(obj, obj->map[key]);
        return;
    }

    Node* node = malloc(sizeof(Node));
    node->key = key;
    node->val = value;

    obj->map[key] = node;
    addToHead(obj, node);
    obj->size++;

    if (obj->size > obj->cap) {
        Node* removed = removeTail(obj);
        obj->map[removed->key] = NULL;
        free(removed);
        obj->size--;
    }
}

void lRUCacheFree(LRUCache* obj) {
    Node* curr = obj->head;
    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(obj->map);
    free(obj);
}

int main() {
    LRUCache* cache = lRUCacheCreate(2);

    lRUCachePut(cache, 1, 10);
    lRUCachePut(cache, 2, 20);

    printf("%d\n", lRUCacheGet(cache, 1)); // 10

    lRUCachePut(cache, 3, 30); // evicts key 2

    printf("%d\n", lRUCacheGet(cache, 2)); // -1

    lRUCacheFree(cache);
    return 0;
}