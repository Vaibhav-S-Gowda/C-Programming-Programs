#include <stdio.h>

#define MAKEVAR(x) int var_##x = x;

int main() {
    MAKEVAR(10)
    printf("%d\n", var_10);
}
