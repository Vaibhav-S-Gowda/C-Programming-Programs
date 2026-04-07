#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
    int pos;     
    int moved;   
    int perimeter;
} Robot;

Robot* robotCreate(int width, int height) {
    Robot* obj = (Robot*)malloc(sizeof(Robot));
    obj->width = width;
    obj->height = height;
    obj->pos = 0;
    obj->moved = 0;
    obj->perimeter = (width + height - 2) * 2;
    return obj;
}

void robotStep(Robot* obj, int num) {
    obj->moved = 1;
    obj->pos = (obj->pos + num) % obj->perimeter;
}

int* robotGetPos(Robot* obj, int* retSize) {
    *retSize = 2;
    int* res = (int*)malloc(2 * sizeof(int));
    int curr = obj->pos;

    int w = obj->width;
    int h = obj->height;

    if (curr < w) {
        res[0] = curr;
        res[1] = 0;
    } 
    else if (curr < w + h - 1) {
        res[0] = w - 1;
        res[1] = curr - (w - 1);
    } 
    else if (curr < 2 * w + h - 2) {
        res[0] = (w - 1) - (curr - (w + h - 2));
        res[1] = h - 1;
    } 
    else {
        res[0] = 0;
        res[1] = (h - 1) - (curr - (2 * w + h - 3));
    }

    return res;
}

char* robotGetDir(Robot* obj) {
    if (obj->pos == 0 && !obj->moved) return "East";
    if (obj->pos == 0) return "South";

    int curr = obj->pos;
    int w = obj->width;
    int h = obj->height;

    if (curr < w) return "East";
    if (curr < w + h - 1) return "North";
    if (curr < 2 * w + h - 2) return "West";
    return "South";
}

void robotFree(Robot* obj) {
    free(obj);
}

/* ================= MAIN FUNCTION ================= */

int main() {
    Robot* robot = robotCreate(4, 3); // Grid: width=4, height=3

    int retSize;
    int* pos;

    // Initial state
    pos = robotGetPos(robot, &retSize);
    printf("Position: (%d, %d), Direction: %s\n", pos[0], pos[1], robotGetDir(robot));
    free(pos);

    // Step 2
    robotStep(robot, 2);
    pos = robotGetPos(robot, &retSize);
    printf("After 2 steps -> Position: (%d, %d), Direction: %s\n", pos[0], pos[1], robotGetDir(robot));
    free(pos);

    // Step 5
    robotStep(robot, 5);
    pos = robotGetPos(robot, &retSize);
    printf("After 5 more steps -> Position: (%d, %d), Direction: %s\n", pos[0], pos[1], robotGetDir(robot));
    free(pos);

    // Step full loop
    robotStep(robot, 100);
    pos = robotGetPos(robot, &retSize);
    printf("After 100 more steps -> Position: (%d, %d), Direction: %s\n", pos[0], pos[1], robotGetDir(robot));
    free(pos);

    robotFree(robot);
    return 0;
}