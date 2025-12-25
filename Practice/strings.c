#include <stdio.h>
#include <string.h>

int main()
{

    char names[3][25] = {0};
    int size = sizeof(names) / sizeof(names[0]); 
    for (int i = 0; i < size; i++)
    {
        printf("Enter a name: ");
        fgets(names[i], sizeof(names[i]), stdin);
        names[i][strlen(names[i]) - 1] = '\0'; 
    }
    
    for (int i = 0; i < 3; i++)
    {
        printf("The names are: %s \n",names[i]);
    }
    return 0;
}