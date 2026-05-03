#include <stdio.h>
#include <math.h>
#include <limits.h>

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize == 0) return 0;

    int buy1 = INT_MIN, sell1 = 0;
    int buy2 = INT_MIN, sell2 = 0;

    for (int i = 0; i < pricesSize; i++) {
        if (-prices[i] > buy1) buy1 = -prices[i];
        if (buy1 + prices[i] > sell1) sell1 = buy1 + prices[i];
        if (sell1 - prices[i] > buy2) buy2 = sell1 - prices[i];
        if (buy2 + prices[i] > sell2) sell2 = buy2 + prices[i];
    }

    return sell2;
}

int main() {
    int prices[] = {3, 3, 5, 0, 0, 3, 1, 4};
    int n = sizeof(prices) / sizeof(prices[0]);

    int profit = maxProfit(prices, n);

    printf("Maximum Profit (at most 2 transactions): %d\n", profit);

    return 0;
}