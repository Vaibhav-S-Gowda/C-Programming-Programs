#include <stdio.h>

int maxProfit(int* prices, int pricesSize) {
    int totalProfit = 0;

    for (int i = 1; i < pricesSize; i++) {
        if (prices[i] > prices[i - 1]) {
            totalProfit += (prices[i] - prices[i - 1]);
        }
    }

    return totalProfit;
}

int main() {
    int prices[] = {7, 1, 5, 3, 6, 4};
    int n = sizeof(prices) / sizeof(prices[0]);

    int profit = maxProfit(prices, n);

    printf("Maximum Profit (unlimited transactions): %d\n", profit);

    return 0;
}