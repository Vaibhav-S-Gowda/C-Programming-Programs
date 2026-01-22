#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    srand(time(NULL));

    // printf("%d \n",rand());
    // printf("%d",RAND_MAX);

    int min = 0, max = 100;
    int randomNum = (rand() % (max - min + 1)) + min;

    printf("%d", randomNum);
    return 0;
}