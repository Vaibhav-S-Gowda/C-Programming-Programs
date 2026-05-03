#include <stdio.h>

int trap(int* height, int heightSize) {
    if (heightSize == 0) return 0;

    int left = 0, right = heightSize - 1;
    int leftMax = 0, rightMax = 0;
    int totalWater = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                totalWater += (leftMax - height[left]);
            }
            left++;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                totalWater += (rightMax - height[right]);
            }
            right--;
        }
    }

    return totalWater;
}

int main() {
    int height[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    int size = sizeof(height) / sizeof(height[0]);

    int result = trap(height, size);

    printf("Trapped water: %d\n", result);  // Expected: 6

    return 0;
}