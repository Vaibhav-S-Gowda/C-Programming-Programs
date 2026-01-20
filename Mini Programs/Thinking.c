#include <stdio.h>
#include <string.h>
#include <unistd.h>   // for sleep()

void useBrain(){
    printf("Thinking...");
    fflush(stdout);
    sleep(2);

    printf("\rAnalyzing...");
    fflush(stdout);
    sleep(2);

    printf("\rFinalizing...");
    fflush(stdout);
    sleep(2);
}

int main() {
    char b[50];
    printf("--- Check which person will find success in 2026!! ---\n");
    printf("Enter your name: ");
    scanf("%8s",b);

    useBrain();

    if (strcmp(b, "Hinduja") == 0) {
        printf("\rHey %s! A tremendous success awaits you in 2026.        \n",b);
    }
    else {
        printf("\rNo way Chance ye illa!         \n");
    }
    
    return 0;
}