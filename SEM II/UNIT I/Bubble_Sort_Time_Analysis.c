#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    /*------------------ File Handling ------------------*/
    fp = fopen("Bubble_Time.txt", "w");
    if (fp == NULL) {
        printf("Error creating file!\n");
        return 1;
    }

    /* Optional header (gnuplot can ignore with 'skip 1') */
    fprintf(fp, "# n actual_time theoretical_time\n");

    /*------------------ Time Measurement ------------------*/
    for (int n = 100; n <= 10000; n += 100) {
        generate_random(a, n);

        start = clock();
        bubble_sort(a, n);
        end = clock();

        time_taken = (double)(end - start) / CLOCKS_PER_SEC;

        /* Scaled O(n^2) for visual comparison */
        theoretical_time = (double)(n * n) * 1e-8;

        fprintf(fp, "%d %lf %lf\n", n, time_taken, theoretical_time);
    }

    fclose(fp);

    /*------------------ Gnuplot Section ------------------*/
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    if (gnuplotPipe == NULL) {
        printf("Error opening gnuplot!\n");
        return 1;
    }

    fprintf(gnuplotPipe, "set title 'Bubble Sort Time Efficiency'\n");
    fprintf(gnuplotPipe, "set xlabel 'Input Size (n)'\n");
    fprintf(gnuplotPipe, "set ylabel 'Time (seconds)'\n");
    fprintf(gnuplotPipe, "set grid\n");

    /* Output image */
    fprintf(gnuplotPipe, "set terminal png size 800,600\n");
    fprintf(gnuplotPipe, "set output 'bubble_sort_graph.png'\n");

    /* Ignore header line */
    fprintf(gnuplotPipe,
        "plot 'Bubble_Time.txt' using 1:2 with linespoints title 'Actual Time', "
        "'Bubble_Time.txt' using 1:3 with lines lw 2 title 'Theoretical O(n^2)'\n"
    );

    fflush(gnuplotPipe);
    pclose(gnuplotPipe);

    printf("Graph generated: bubble_sort_graph.png\n");

    return 0;
}