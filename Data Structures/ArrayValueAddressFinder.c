#include <stdio.h>

int main()
{
    int arr[5] = {1,2,3,4,5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int num;
    printf("Enter a number between 1-5: ");
    scanf("%d", &num);
    for (int i = 0; i < size; i++)
    {
        if (num == arr[i]){
            printf("Value : %d\n",arr[i]);
            printf("Address : %d\n",&arr[i]);
        }
    }
    return 0;
}