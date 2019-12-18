// Continue LIS(最長連続増加部分列)を解く

int conlis(vector<int>& v) {
	vi dp(v.size() + 1, 0);
	int ans = 0;
	for(int i = 0; i < v.size(); i++) {
		dp[v[i]] = dp[v[i] - 1] + 1;
		ans = max(ans, dp[v[i]]);
	}
	return ans;
}
