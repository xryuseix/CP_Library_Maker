// ナップサック問題

int knapsack(int n, int W, vi w, vi v) {
	vvi dp(n + 1, vi (W + 1, 0));
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= W; j++) {
			if(j - w[i] >= 0) {
				chmax(dp[i][j], dp[i - 1][j - w[i]] + v[i]);
			}
			chmax(dp[i][j], dp[i - 1][j]);
		}
	}
	return dp[n][W];
}
