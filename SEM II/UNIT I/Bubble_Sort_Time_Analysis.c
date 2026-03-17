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

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
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
    fp = fopen("Bubble_Time.txt", "w");

    for (int n = 100; n <= 10000; n += 100) {
        generate_random(a, n);

        start = clock();
        bubble_sort(a, n);
        end = clock();

        time_taken = (double)(end - start) / CLOCKS_PER_SEC;

        // Theoretical O(n^2)
        theoretical_time = (double)n * n;

        fprintf(fp, "%d\t%lf\t%lf\n", n, time_taken, theoretical_time);
        // fprintf(fp, "n actual theoretical\n");
        // fprintf(fp, "%d %lf %lf\n", n, time_taken, theoretical_time);
    }

    fclose(fp);
    return 0;
}