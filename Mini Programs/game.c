#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define W 30
#define H 20

int x = 10, y = 10;
int foodX, foodY;
int score = 0;

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void spawnFood() {
    do {
        foodX = rand() % W;
        foodY = rand() % H;
    } while (foodX == x && foodY == y);
}

void draw() {

    gotoXY(0, 0);

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {

            if (i == y && j == x)
                printf("O");
            else if (i == foodY && j == foodX)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("Score: %d\n", score);
    printf("Use WASD to move\n");
}

void input() {
    if (_kbhit()) {
        char c = _getch();

        if (c == 'w' || c == 'W') y--;
        if (c == 's' || c == 'S') y++;
        if (c == 'a' || c == 'A') x--;
        if (c == 'd' || c == 'D') x++;
    }
}

void logic() {

    if (x < 0) x = 0;
    if (x >= W) x = W - 1;
    if (y < 0) y = 0;
    if (y >= H) y = H - 1;

    if (x == foodX && y == foodY) {
        score++;
        spawnFood();
    }
}

int main() {

    srand(time(NULL));
    spawnFood();

    while (1) {
        draw();
        input();
        logic();
        Sleep(80);
    }

    return 0;
}
