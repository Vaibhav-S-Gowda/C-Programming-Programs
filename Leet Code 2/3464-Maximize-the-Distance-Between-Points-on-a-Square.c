#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmp_ll(const void* a, const void* b) {
    ll x = *(const ll*)a;
    ll y = *(const ll*)b;
    return x < y ? -1 : x > y;
}

int ok(int side, ll* a, int n, int k, int d, ll* b, int* nx) {
    ll p = 4LL * side;

    for (int i = 0; i < n; ++i) {
        b[i] = a[i];
        b[i + n] = a[i] + p;
    }

    int j = 1;
    for (int i = 0; i < 2 * n; ++i) {
        if (j < i + 1)
            j = i + 1;
        while (j < 2 * n && b[j] - b[i] < d)
            ++j;
        nx[i] = j;
    }

    for (int i = 0; i < n; ++i) {
        int x = i;
        int t = 1;
        for (; t < k; ++t) {
            x = nx[x];
            if (x >= 2 * n)
                break;
        }
        if (t == k && b[x] - b[i] <= p - d)
            return 1;
    }

    return 0;
}

int maxDistance(int side, int** points, int pointsSize, int* pointsColSize, int k) {
    ll* a = malloc(sizeof(ll) * pointsSize);
    ll* b = malloc(sizeof(ll) * pointsSize * 2);
    int* nx = malloc(sizeof(int) * pointsSize * 2);

    for (int i = 0; i < pointsSize; ++i) {
        int x = points[i][0];
        int y = points[i][1];
        if (y == 0)
            a[i] = x;
        else if (x == side)
            a[i] = (ll)side + y;
        else if (y == side)
            a[i] = 3LL * side - x;
        else
            a[i] = 4LL * side - y;
    }

    qsort(a, pointsSize, sizeof(ll), cmp_ll);

    int l = 0, r = side; 
    while (l < r) {
        int m = l + (r - l + 1) / 2;
        if (ok(side, a, pointsSize, k, m, b, nx))
            l = m;
        else
            r = m - 1;
    }

    free(a);
    free(b);
    free(nx);
    return l;
}

int main() {
    int side = 10;

    int pointsSize = 4;
    int k = 2;

    // Allocate 2D array for points
    int** points = (int**)malloc(pointsSize * sizeof(int*));
    for (int i = 0; i < pointsSize; i++) {
        points[i] = (int*)malloc(2 * sizeof(int));
    }

    // Example points on boundary of square
    points[0][0] = 0;  points[0][1] = 0;
    points[1][0] = 10; points[1][1] = 0;
    points[2][0] = 10; points[2][1] = 10;
    points[3][0] = 0;  points[3][1] = 10;

    int* pointsColSize = (int*)malloc(pointsSize * sizeof(int));
    for (int i = 0; i < pointsSize; i++) {
        pointsColSize[i] = 2;
    }

    int result = maxDistance(side, points, pointsSize, pointsColSize, k);
    printf("Maximum Distance: %d\n", result);

    // Free memory
    for (int i = 0; i < pointsSize; i++) {
        free(points[i]);
    }
    free(points);
    free(pointsColSize);

    return 0;
}