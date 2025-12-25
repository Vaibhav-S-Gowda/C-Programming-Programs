#include<stdio.h>
#include<math.h>

int square(int num){
    return (float)pow(num,2); // Explicit type casting
}
int sq(int num)
{
    return num * num;
}
int main()
{

    int x = square(2);
    int y = square(4);
    int z = sq(5);
    int m = sq(10);
    int n = square(50);

    printf("Square of 2 is : %d\n",x);
    printf("Square of 3 is : %d\n",y);
    printf("Square of 5 is : %d\n",z);
    printf("Square of 10 is : %d\n",m);
    printf("Square of 50 is : %d\n",n);
    return 0;
}