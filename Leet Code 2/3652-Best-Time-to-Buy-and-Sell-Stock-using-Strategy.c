#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

long long maxProfit(int* prices, int pricesSize, int* strategy, int strategySize, int k) {
    long long baseProfit = 0;
    int n = pricesSize;

    for (int i = 0; i < n; i++) {
        baseProfit += (long long)strategy[i] * prices[i];
    }

    long long currentDelta = 0;
    int halfK = k / 2;

    for (int i = 0; i < k; i++) {
        if (i < halfK) {
            currentDelta -= (long long)strategy[i] * prices[i];
        } else {
            currentDelta += (long long)(1 - strategy[i]) * prices[i];
        }
    }

    long long maxDelta = currentDelta;

    for (int i = 0; i < n - k; i++) {
        currentDelta += (long long)strategy[i] * prices[i];

        int midIdx = i + halfK;
        currentDelta -= (long long)(1 - strategy[midIdx]) * prices[midIdx];
        currentDelta -= (long long)strategy[midIdx] * prices[midIdx];

        int nextIdx = i + k;
        currentDelta += (long long)(1 - strategy[nextIdx]) * prices[nextIdx];

        maxDelta = MAX(maxDelta, currentDelta);
    }

    return baseProfit + MAX(0, maxDelta);
}

int main() {
    int prices[]   = {3, 5, 2, 6, 1, 4, 7, 3};
    int strategy[] = {1, 1, 0, 0, 1, 0, 1, 0};
    
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 4;  // must be even for correct behavior

    long long profit = maxProfit(prices, n, strategy, n, k);

    printf("Maximum Profit after strategy optimization: %lld\n", profit);

    return 0;
}