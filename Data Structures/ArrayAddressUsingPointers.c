#include <stdio.h>

int main()
{
    int arr[5] = {1,2,3,4,5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int num;
    printf("Enter a number between 1-5: ");
    scanf("%d", &num);
    int* ptr[size];
    for (int i = 0; i < size; i++)
    {
        ptr[i] = &arr[i];
    
        if (num == arr[i])
        {
            printf("Address : %p",ptr[i]);
        }
    }
    
    return 0;
}