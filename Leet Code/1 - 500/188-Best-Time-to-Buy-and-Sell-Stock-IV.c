#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int max(int a, int b) { return a > b ? a : b; }

int maxProfit(int k, int* prices, int pricesSize) {
    if (pricesSize == 0) return 0;

    if (k >= pricesSize / 2) {
        int profit = 0;
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int* buy = (int*)malloc((k + 1) * sizeof(int));
    int* sell = (int*)malloc((k + 1) * sizeof(int));

    for (int i = 0; i <= k; i++) {
        buy[i] = INT_MIN;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        int price = prices[i];
        for (int t = 1; t <= k; t++) {
            buy[t] = max(buy[t], sell[t - 1] - price);
            sell[t] = max(sell[t], buy[t] + price);
        }
    }

    int result = sell[k];
    free(buy);
    free(sell);

    return result;
}

int main() {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;

    int profit = maxProfit(k, prices, n);

    printf("Maximum Profit: %d\n", profit);

    return 0;
}