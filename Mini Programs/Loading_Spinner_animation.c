#include <stdio.h>
#include <windows.h>

int main() {
    char spinner[] = {'|', '/', '-', '\\'};

    for (int i = 0; i < 100; i++) {
        printf("\rLoading %c", spinner[i % 4]);
        fflush(stdout);
        Sleep(100);   // 100 ms delay
    }

    printf("\nDone!\n");
    return 0;
}
