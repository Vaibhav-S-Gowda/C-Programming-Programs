#include <stdio.h>

struct {
    union {
        int x;
        float y;
    };
} obj;

int main() {
    obj.x = 65;
    printf("%f\n", obj.y);
}
