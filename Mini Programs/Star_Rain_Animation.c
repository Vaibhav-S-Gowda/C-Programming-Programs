#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define WIDTH 60
#define HEIGHT 20

int main() {
    srand(time(NULL));

    while (1) {
        printf("\033[2J\033[H");

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (rand() % 25 == 0)
                    printf("*");
                else
                    printf(" ");
            }
            printf("\n");
        }

        Sleep(80);   // 80 ms (was 80000 microseconds)
    }
}
