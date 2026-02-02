#include <stdio.h>

#define FRUITS \
    X(APPLE)   \
    X(BANANA)  \
    X(MANGO)

#define X(name) name,
enum Fruit { FRUITS };
#undef X

#define X(name) #name,
const char *fruit_names[] = { FRUITS };
#undef X

int main() {
    for(int i=0; i<3; i++)
        printf("%s\n", fruit_names[i]);
}
