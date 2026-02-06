#include<stdio.h>
#include<string.h>

struct school{  //Declaration
    char section;
    int rollNum;
    char name[50]; 
}s1 = {'A',23,"Hinduja"};

int main(){

    printf("%c %d %s",s1.section,s1.rollNum,s1.name);
    return 0;
}