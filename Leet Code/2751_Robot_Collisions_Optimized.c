#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int pos;
    int health;
    char dir;
    int id; // Original index
} Robot;

// Comparator to sort robots by position
int compare(const void* a, const void* b) {
    return ((Robot*)a)->pos - ((Robot*)b)->pos;
}

int* survivedRobotsHealths(int* positions, int positionsSize, int* healths, int healthsSize, char* directions, int* returnSize) {
    Robot* robots = malloc(positionsSize * sizeof(Robot));
    for (int i = 0; i < positionsSize; i++) {
        robots[i] = (Robot){positions[i], healths[i], directions[i], i};
    }

    qsort(robots, positionsSize, sizeof(Robot), compare);

    int* stack = malloc(positionsSize * sizeof(int));
    int top = -1;

    for (int i = 0; i < positionsSize; i++) {
        if (robots[i].dir == 'R') {
            stack[++top] = i; // Push index of Right-moving robot
        } else {
            // Left-moving robot collision logic
            while (top >= 0 && robots[stack[top]].dir == 'R' && robots[i].health > 0) {
                if (robots[i].health > robots[stack[top]].health) {
                    robots[stack[top]].health = 0; // Destroyed
                    robots[i].health -= 1;
                    top--; // Pop
                } else if (robots[i].health < robots[stack[top]].health) {
                    robots[stack[top]].health -= 1;
                    robots[i].health = 0; // Destroyed
                } else {
                    robots[stack[top]].health = 0;
                    robots[i].health = 0;
                    top--; // Pop
                }
            }
        }
    }

    // Prepare result based on original indices
    int* res = malloc(positionsSize * sizeof(int));
    int count = 0;
    
    // Sort back to original order or use a map
    // Here, we filter robots that still have health > 0
    int* finalHealths = malloc(positionsSize * sizeof(int));
    for(int i = 0; i < positionsSize; i++) finalHealths[i] = -1;
    
    for(int i = 0; i < positionsSize; i++) {
        if(robots[i].health > 0) {
            finalHealths[robots[i].id] = robots[i].health;
        }
    }

    for(int i = 0; i < positionsSize; i++) {
        if(finalHealths[i] != -1) {
            res[count++] = finalHealths[i];
        }
    }

    *returnSize = count;
    free(robots);
    free(stack);
    free(finalHealths);
    return res;
}

int main() {
    int positions[] = {5, 4, 3, 2, 1};
    int healths[] = {2, 17, 9, 15, 10};
    char directions[] = {'R', 'R', 'R', 'R', 'R'};

    int n = sizeof(positions) / sizeof(positions[0]);
    int returnSize = 0;

    int* result = survivedRobotsHealths(
        positions, n,
        healths, n,
        directions,
        &returnSize
    );

    printf("Surviving robots' healths:\n");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}