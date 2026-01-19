#include<stdio.h>
#include<stdbool.h>

bool validUtf8(int* data, int dataSize) {
    int remainingBytes = 0;

    for (int i = 0; i < dataSize; i++) {
        int byte = data[i] & 0xFF;  // use only last 8 bits

        if (remainingBytes == 0) {
            if ((byte >> 7) == 0b0) {
                // 1-byte character: 0xxxxxxx
                continue;
            } 
            else if ((byte >> 5) == 0b110) {
                // 2-byte character
                remainingBytes = 1;
            } 
            else if ((byte >> 4) == 0b1110) {
                // 3-byte character
                remainingBytes = 2;
            } 
            else if ((byte >> 3) == 0b11110) {
                // 4-byte character
                remainingBytes = 3;
            } 
            else {
                return false; // invalid leading byte
            }
        } 
        else {
            // continuation byte must be 10xxxxxx
            if ((byte >> 6) != 0b10) {
                return false;
            }
            remainingBytes--;
        }
    }

    // all characters must be fully processed
    return remainingBytes == 0;
}

int main() {
    int data1[] = {197, 130, 1};      // valid UTF-8
    int data2[] = {235, 140, 4};      // invalid UTF-8

    int size1 = sizeof(data1) / sizeof(data1[0]);
    int size2 = sizeof(data2) / sizeof(data2[0]);

    printf("Test case 1: %s\n",
           validUtf8(data1, size1) ? "Valid UTF-8" : "Invalid UTF-8");

    printf("Test case 2: %s\n",
           validUtf8(data2, size2) ? "Valid UTF-8" : "Invalid UTF-8");
    return 0;
}

// sizeof(array) / sizeof(array[0]) safely computes array length.