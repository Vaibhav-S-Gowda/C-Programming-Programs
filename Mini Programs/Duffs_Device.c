#include <stdio.h>

void duffs_device_copy(char *to, char *from, int count)
{
    int n = (count + 7) / 8;

    switch (count % 8)
    {
        case 0: do { *to++ = *from++;
        case 7:      *to++ = *from++;
        case 6:      *to++ = *from++;
        case 5:      *to++ = *from++;
        case 4:      *to++ = *from++;
        case 3:      *to++ = *from++;
        case 2:      *to++ = *from++;
        case 1:      *to++ = *from++;
                } while (--n > 0);
    }
}

int main()
{
    char src[] = "HelloDuffDevice!";
    char dst[50];

    duffs_device_copy(dst, src, 16);
    dst[16] = '\0';

    printf("Copied: %s\n", dst);
    return 0;
}
