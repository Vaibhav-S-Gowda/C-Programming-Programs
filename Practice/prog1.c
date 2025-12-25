#include<stdio.h>
int main()
{
    char ch = 'A';
    char c[] = "Hello Broo!!!";
    printf("%c\n",ch);
    printf("%s\n",c);
    printf("%d",sizeof(c));
    printf("\n %c",c[1]);
 
    for (int i = 0; i < sizeof(c) - 1; i++)
    {
        /* code */
        printf("%c %d",c[i],i);
    }
    
    return 0;   
}