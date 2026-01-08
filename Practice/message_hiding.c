#include<stdio.h>
int main(){
    char *msg = "This looks innocent!";
    while (*msg)putchar(*msg++);
    return 0; 
}