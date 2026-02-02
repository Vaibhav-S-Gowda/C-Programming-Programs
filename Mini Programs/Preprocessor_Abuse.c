#define IF(x) _IF(x)
#define _IF(x) __IF_##x

#define __IF_1(...) __VA_ARGS__
#define __IF_0(...)

int main() {
    IF(1)(printf("Printed\n");)
    IF(0)(printf("Never printed\n");)
}
