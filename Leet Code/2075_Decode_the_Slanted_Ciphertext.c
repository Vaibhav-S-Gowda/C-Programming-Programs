#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* decodeCiphertext(char* encodedText, int rows) {
    int n = strlen(encodedText);
    if (n == 0) return "";
    
    int cols = n / rows;
    char* result = (char*)malloc((n + 1) * sizeof(char));
    int k = 0;

    // Traverse the diagonals
    // i represents the starting column of each diagonal in the first row
    for (int i = 0; i < cols; i++) {
        for (int j = i; j < n; j += (cols + 1)) {
            // Check to ensure we don't 'wrap around' to the next row incorrectly
            // Each step in the diagonal must be in the next row
            result[k++] = encodedText[j];
            
            // If the next jump would exceed the current column constraints 
            // (since diagonals move right), we stop for this diagonal.
            if ((j % cols) + 1 >= cols) break;
        }
    }
    result[k] = '\0';

    // Remove trailing spaces
    int end = k - 1;
    while (end >= 0 && result[end] == ' ') {
        result[end] = '\0';
        end--;
    }

    return result;
}

int main() {
    char encodedText[] = "ch   ie   pr";
    int rows = 3;

    char* decoded = decodeCiphertext(encodedText, rows);

    printf("Decoded text: %s\n", decoded);

    free(decoded);  // Important to free allocated memory
    return 0;
}