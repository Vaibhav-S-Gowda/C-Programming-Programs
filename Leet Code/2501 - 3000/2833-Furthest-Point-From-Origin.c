#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int furthestDistanceFromOrigin(char* moves) {
    int l_count = 0;
    int r_count = 0;
    int underscore_count = 0;

    for (int i = 0; moves[i] != '\0'; i++) {
        if (moves[i] == 'L') {
            l_count++;
        } else if (moves[i] == 'R') {
            r_count++;
        } else if (moves[i] == '_') {
            underscore_count++;
        }
    }

    int diff = abs(l_count - r_count);

    return diff + underscore_count;
}

int main() {
    char moves[] = "L_RL__R";

    int result = furthestDistanceFromOrigin(moves);

    printf("Furthest Distance: %d\n", result);

    return 0;
}