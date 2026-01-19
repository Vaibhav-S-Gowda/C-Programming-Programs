#include <stdio.h>

/*
   Function: maxArea
   Purpose : Finds the maximum amount of water that can be stored
             between two vertical lines.
   Input   :
       height     -> array containing heights of vertical lines
       heightSize -> number of elements in the array
   Output  :
       Maximum water area (integer)
*/

int maxArea(int* height, int heightSize) {

    // max_water stores the maximum area found so far
    int max_water = 0;
    int lp = 0;
    int rp = heightSize - 1;

    while (lp < rp) {

        int width = rp - lp;
        int heightValue = height[lp] < height[rp] ? height[lp] : height[rp];
        int currentWater = width * heightValue;

        // Update maximum water if current is greater
        if (currentWater > max_water) {
            max_water = currentWater;
        }

        height[lp] < height[rp] ? lp++ : rp--;
    }
    return max_water;
}

int main() {
    int height[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int size = sizeof(height) / sizeof(height[0]);

    printf("Maximum water area: %d\n", maxArea(height, size));
    return 0;
}