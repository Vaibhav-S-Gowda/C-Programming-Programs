#include <stdio.h>
#include <stdlib.h>

typedef struct { int x, h; } Event;

static int cmpEvents(const void* a, const void* b) {
    const Event* e1 = (const Event*)a;
    const Event* e2 = (const Event*)b;
    if (e1->x != e2->x) return e1->x - e2->x;
    return e2->h - e1->h;
}

typedef struct { int* data; int size; } Heap;

static inline void push(Heap* h, int val) {
    int i = ++h->size;
    h->data[i] = val;
    while (i > 1 && h->data[i] > h->data[i >> 1]) {
        int tmp = h->data[i]; h->data[i] = h->data[i >> 1]; h->data[i >> 1] = tmp;
        i >>= 1;
    }
}

static inline void pop(Heap* h) {
    h->data[1] = h->data[h->size--];
    int i = 1;
    for (;;) {
        int c = i << 1;
        if (c > h->size) break;
        if (c + 1 <= h->size && h->data[c + 1] > h->data[c]) c++;
        if (h->data[i] >= h->data[c]) break;
        int tmp = h->data[i]; h->data[i] = h->data[c]; h->data[c] = tmp;
        i = c;
    }
}

int** getSkyline(int** buildings, int buildingsSize, int* buildingsColSize,
                 int* returnSize, int** returnColumnSizes) {
    int n = buildingsSize;

    Event* events = (Event*)malloc(sizeof(Event) * 2 * n);
    for (int i = 0; i < n; i++) {
        events[2*i]   = (Event){ buildings[i][0],  buildings[i][2] };
        events[2*i+1] = (Event){ buildings[i][1], -buildings[i][2] };
    }
    qsort(events, 2 * n, sizeof(Event), cmpEvents);

    /* Single flat allocation: all rows share one contiguous block */
    int*  flat = (int*)malloc(sizeof(int) * 4 * n);
    int** res  = (int**)malloc(sizeof(int*) * 2 * n);
    *returnColumnSizes = (int*)malloc(sizeof(int) * 2 * n);
    for (int i = 0; i < 2 * n; i++) res[i] = flat + 2 * i;

    Heap h1 = { (int*)malloc(sizeof(int) * (2*n + 2)), 0 };
    Heap h2 = { (int*)malloc(sizeof(int) * (2*n + 2)), 0 };
    push(&h1, 0);

    int count = 0, prevMax = 0;

    for (int i = 0; i < 2 * n; i++) {
        if (events[i].h > 0) push(&h1,  events[i].h);
        else                 push(&h2, -events[i].h);

        /* Drain all stale tops before reading the max */
        while (h2.size > 0 && h1.data[1] == h2.data[1]) {
            pop(&h1); pop(&h2);
        }

        int currMax = h1.data[1];
        if (currMax != prevMax) {
            res[count][0] = events[i].x;
            res[count][1] = currMax;
            (*returnColumnSizes)[count++] = 2;
            prevMax = currMax;
        }
    }

    *returnSize = count;
    free(events); free(h1.data); free(h2.data);
    /* Note: flat is kept alive — it backs every res[i] row */
    return res;
}

int main() {
    // Example 1: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
    int b1[] = {2, 9, 10};
    int b2[] = {3, 7, 15};
    int b3[] = {5, 12, 12};
    int b4[] = {15, 20, 10};
    int b5[] = {19, 24, 8};
    
    int* buildings[] = {b1, b2, b3, b4, b5};
    int buildingsSize = 5;
    int buildingsColSize[] = {3, 3, 3, 3, 3};

    int returnSize;
    int* returnColumnSizes;

    // Call the function
    int** result = getSkyline(buildings, buildingsSize, buildingsColSize, &returnSize, &returnColumnSizes);

    // Print the results
    printf("Skyline Key Points:\n[");
    for (int i = 0; i < returnSize; i++) {
        printf("[%d,%d]%s", result[i][0], result[i][1], i == returnSize - 1 ? "" : ",");
    }
    printf("]\n");

    // Cleanup
    // Note: In the provided code, result[0] points to the start of the 'flat' allocation
    free(result[0]); 
    free(result);
    free(returnColumnSizes);

    return 0;
}