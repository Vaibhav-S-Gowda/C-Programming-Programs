#include <stdio.h>

__attribute__((constructor))
void before_main() {
    printf("Runs before main!\n");
}

int main() {
    printf("Inside main\n");
}
