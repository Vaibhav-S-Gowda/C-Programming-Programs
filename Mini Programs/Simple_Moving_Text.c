#include <stdio.h>
#include <windows.h>

int main() {
    for (int i = 0; i < 50; i++) {
        printf("\r");   // Move cursor to start of line

        for (int j = 0; j < i; j++) {
            printf(" ");
        }

        printf("🚀");
        fflush(stdout);

        Sleep(50);   // 50 ms delay
    }

    printf("\n");
    return 0;
}
