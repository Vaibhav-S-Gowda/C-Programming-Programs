#include <stdio.h>

int main() {
    void *labels[] = { &&start, &&middle, &&end };

    int i = 0;
    goto *labels[i];

start:
    printf("At start\n");
    i = 1;
    goto *labels[i];

middle:
    printf("At middle\n");
    i = 2;
    goto *labels[i];

end:
    printf("At end\n");
    return 0;
}
