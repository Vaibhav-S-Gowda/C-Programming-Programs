#include <stdio.h>

#define MAX 100

// Swap two integers using pointers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Up-heapify (heapify-up) for maintaining heap after insertion
void upheapify(int heap[], int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap[parent] < heap[index]) {
        swap(&heap[parent], &heap[index]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

// Insert a new value into the Max-Heap
void insert(int heap[], int *size, int value) {
    heap[*size] = value;       // Insert at next index
    upheapify(heap, *size);    // Fix heap upwards
    (*size)++;                 // Increase size
}

// Down-heapify (heapify-down) used in building heap & deletion
void downheapify(int heap[], int size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Compare with left child
    if (left < size && heap[left] > heap[largest])
        largest = left;

    // Compare with right child
    if (right < size && heap[right] > heap[largest])
        largest = right;

    // Swap & continue heapifying if needed
    if (largest != index) {
        swap(&heap[index], &heap[largest]);
        downheapify(heap, size, largest);
    }
}

// Build Max-Heap from an existing array
void buildMaxHeap(int heap[], int size) {
    for (int i = (size / 2) - 1; i >= 0; i--) {
        downheapify(heap, size, i);
    }
}

// Print heap contents
void printHeap(int heap[], int size) {
    printf("Max-Heap: ");
    for (int i = 0; i < size; i++)
        printf("%d ", heap[i]);
    printf("\n");
}

void heapSort(int heap[], int size) {
    // Step 1: Build Max-Heap
    buildMaxHeap(heap, size);
    {
        // Step 2: Extract elements one by one
        for (int i = size - 1; i > 0; i--) {
            // Swap the root (max element) with the last element
            swap (&heap [0], &heap[i]);
            // Reduce heap size and restore heap property
            downheapify (heap, i, 0);
        }
    }
}

// Main program demo
int main() {
    int heap[MAX];
    int size = 0;
    int choice, value;

    while (1) {
        printf("\n--- Max Heap Operations ---\n");
        printf("1. Insert\n");
        printf("2. Build Max Heap from input list\n");
        printf("3. Display\n");
        printf("4. Heap Sort\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            insert(heap, &size, value);
            printf("Inserted.\n");
            break;

        case 2:
            printf("Enter number of elements: ");
            scanf("%d", &size);
            printf("Enter elements: ");
            for (int i = 0; i < size; i++)
                scanf("%d", &heap[i]);
            buildMaxHeap(heap, size);
            printf("Max-Heap built.\n");
            break;

        case 3:
            printHeap(heap, size);
            break;

        case 4:
            heapSort(heap, size);
            break;
        
        case 5:
            return 0;
        }
    }

    return 0;
}
