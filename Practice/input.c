#include <stdio.h>
#include <string.h>

int main() {
    int age;
    float gpa;
    char grade;
    char name[30];
    
    printf("Enter your age: ");
    scanf("%d", &age);
    printf("You entered: %d\n", age);

    printf("Enter your gpa:");
    scanf("%f", &gpa);
    printf("Your gpa is: %.2f\n", gpa);

    printf("Enter your grade:");
    scanf(" %c", &grade); // space before %c to consume any leftover newline
    printf("Your grade is: %c\n", grade);

    printf("Enter your name:");
    scanf("    %s", name); // %s reads a string until whitespace
    printf("Your name is: %s\n", name);

    getchar(); // to consume the leftover newline character
    printf("Enter your name again:");
    fgets(name, sizeof(name), stdin); // stdin ,to consume the leftover newline character
    name[strlen(name) - 1] = '\0'; // remove the newline character at the end
    printf("Your name is: %s\n", name);

    return 0;
}