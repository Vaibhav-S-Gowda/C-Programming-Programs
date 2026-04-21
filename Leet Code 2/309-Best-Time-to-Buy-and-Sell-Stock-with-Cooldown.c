#include <stdio.h>
#include <math.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize <= 1) {
        return 0;
    }

    int hold = -prices[0];
    int sold = 0;
    int rest = 0;

    for (int i = 1; i < pricesSize; i++) {
        int prev_hold = hold;
        int prev_sold = sold;
        int prev_rest = rest;

        hold = MAX(prev_hold, prev_rest - prices[i]);
        sold = prev_hold + prices[i];
        rest = MAX(prev_rest, prev_sold);
    }

    return MAX(sold, rest);
}

int main() {
    int prices[] = {1, 2, 3, 0, 2};
    int n = sizeof(prices) / sizeof(prices[0]);

    int profit = maxProfit(prices, n);

    printf("Maximum Profit (with cooldown): %d\n", profit);

    return 0;
}