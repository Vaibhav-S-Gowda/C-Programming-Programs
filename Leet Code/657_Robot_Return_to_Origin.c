#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool judgeCircle(char* str) {
    int x = 0;
    int y = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        // Using a switch statement or else-if is faster than 4 separate if's
        switch (str[i]) {
            case 'U': y++; break;
            case 'D': y--; break;
            case 'L': x--; break;
            case 'R': x++; break;
        }
    }
    
    // Direct return of the boolean condition is slightly cleaner
    return (x == 0 && y == 0);
}

int main() {
    char moves[1000];

    printf("Enter moves: ");
    scanf("%s", moves);

    if (judgeCircle(moves)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}