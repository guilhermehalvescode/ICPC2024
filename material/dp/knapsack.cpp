#define NMAX 10000
int weights[NMAX], values[NMAX], dp[NMAX+1][NMAX+1];

// Mochileiro basico com Peso e Valor em cada objeto
int knapsack(int maxWeight, int n) {
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= maxWeight; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][maxWeight];
}