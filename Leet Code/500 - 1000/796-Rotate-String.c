#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool rotateString(char *s, char *goal) {
    int lenS = strlen(s);
    int lenG = strlen(goal);

    if (lenS != lenG) {
        return false;
    }

    if (lenS == 0) {
        return true;
    }

    char *temp = malloc(lenS * 2 + 1);
    if (temp == NULL) {
        return false;
    }

    strcpy(temp, s);
    strcat(temp, s);

    bool result = strstr(temp, goal) != NULL;

    free(temp);
    return result;
}

int main() {
    char s[] = "abcde";
    char goal[] = "cdeab";

    printf("%s\n", rotateString(s, goal) ? "True" : "False");
    return 0;
}