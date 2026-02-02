#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int (*getFunc())(int, int) {
    return add;
}

int main() {
    int (*f)(int,int) = getFunc();
    printf("%d\n", f(5,7));
}
