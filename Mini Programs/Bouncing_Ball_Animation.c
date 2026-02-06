#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#define delay(ms) Sleep(ms)
#else
#include <unistd.h>
#define delay(ms) usleep((ms) * 1000)
#endif

int main() {
    int pos = 0;
    int dir = 1;

    while (1) {
        printf("\r");

        for (int i = 0; i < pos; i++)
            printf(" ");

        printf("O");
        fflush(stdout);

        delay(40);

        pos += dir;

        if (pos == 40 || pos == 0)
            dir = -dir;
    }

    return 0;
}
