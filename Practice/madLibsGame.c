#include<stdio.h>
#include<string.h>

int main()
{
    // Mad Libs Game
    
    char noun[20] = "";
    char verb[20] = "";
    char adjective1[50] = "";
    char adjective2[50] = "";
    char adjective3[50] = "";

    printf("Enter as adjective (description): ");
    fgets(adjective1, sizeof(adjective1), stdin);
    adjective1[strlen(adjective1) - 1 ] = '\0'; // Remove newline character in the input buffer

    printf("Enter a noun  (animal or person): ");
    fgets(noun, sizeof(noun), stdin);
    noun[strlen(noun) - 1 ] = '\0'; // Remove newline character in the input buffer

    printf("Enter as adjective (description): ");
    fgets(adjective2, sizeof(adjective2), stdin);
    adjective2[strlen(adjective2) - 1 ] = '\0'; // Remove newline character in the input buffer

    printf("Enter as verb (ending with -ing): ");
    fgets(verb, sizeof(verb), stdin);
    verb[strlen(verb) - 1 ] = '\0'; // Remove newline character in the input buffer

    printf("Enter as adjective (description): ");
    fgets(adjective3, sizeof(adjective3), stdin);
    adjective3[strlen(adjective3) - 1 ] = '\0'; // Remove newline character in the input buffer 

    printf("\nHere is your story:\n");
    printf("The %s %s was %s %s through the forest.\n", adjective1, noun, adjective2, verb);
    printf("It was a %s day.\n", adjective3);

    return 0;
}