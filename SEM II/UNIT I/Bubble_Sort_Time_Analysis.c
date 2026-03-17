#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*------------------ Generate Random Numbers ------------------*/
void generate_random(int a[], int n) {
    for (int i = 0; i < n; i++)
        a[i] = rand() % 10000;
}

/*------------------ Bubble Sort ------------------*/
void bubble_sort(int a[], int n) {
    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; i < n; i++)
        {
            /* code */
        }
        
    }
}

int main() {
    int a[10000];
    clock_t start, end;
    double time_taken;
    double theoretical_time;
    FILE *fp;

    srand(time(NULL));
    fp = fopen("Bubble_Time.txt","w");

    for (int n = 100; n <= 10000; n += 100)
    {
        generate_random(a, n);
        start = clock();
        bubble_sort(a, n);
        end = clock();
        time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        theoretical_time = (double)(end + start);
    }
    
}