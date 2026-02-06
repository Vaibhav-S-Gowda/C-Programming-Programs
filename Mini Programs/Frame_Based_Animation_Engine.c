#include <stdio.h>
#include <windows.h>

#define FPS 30

void clear() {
    printf("\033[2J\033[H");
}

void render(int frame) {
    clear();
    printf("Frame: %d\n", frame);

    int pos = frame % 40;
    for (int i = 0; i < pos; i++) printf(" ");
    printf("O\n");
}

int main() {
    int frame = 0;
    int running = 1;

    int frame_delay = 1000 / FPS;   // milliseconds per frame

    while (running) {
        render(frame++);
        Sleep(frame_delay);

        if (frame > 500) running = 0;
    }

    return 0;
}
