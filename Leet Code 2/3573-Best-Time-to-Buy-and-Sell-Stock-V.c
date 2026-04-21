#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long maxProfit;
    long long buyHold;
    long long sellHold;
} State;

long long maximumProfit(int* prices, int pricesSize, int k) {
    int firstPrice = prices[0];

    State* dp = (State*)malloc((k + 1) * sizeof(State));

    for (int idx = 0; idx <= k; idx++) {
        dp[idx].maxProfit = 0;
        dp[idx].buyHold = -firstPrice;
        dp[idx].sellHold = firstPrice;
    }

    for (int day = 1; day < pricesSize; day++) {
        int currPrice = prices[day];

        for (int trans = k; trans > 0; trans--) {
            long long prevProfit = dp[trans - 1].maxProfit;
            long long profit = dp[trans].maxProfit;
            long long buy = dp[trans].buyHold;
            long long sell = dp[trans].sellHold;

            profit = (profit > buy + currPrice) ? profit : (buy + currPrice);
            profit = (profit > sell - currPrice) ? profit : (sell - currPrice);

            buy = (buy > prevProfit - currPrice) ? buy : (prevProfit - currPrice);
            sell = (sell > prevProfit + currPrice) ? sell : (prevProfit + currPrice);

            dp[trans].maxProfit = profit;
            dp[trans].buyHold = buy;
            dp[trans].sellHold = sell;
        }
    }

    long long result = dp[k].maxProfit;
    free(dp);
    return result;
}

int main() {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;

    long long profit = maximumProfit(prices, n, k);

    printf("Maximum Profit (k transactions): %lld\n", profit);

    return 0;
}