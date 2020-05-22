// LIS(最長増加部分列)を解く

int lis(vi& v) {
	vi dp(1, v[0]);
	for(int i = 1; i < v.size(); i++) {
		if(v[i] > dp[dp.size() - 1]) {
			dp.push_back(v[i]);
		} else {
			int pos = distance(dp.begin(), lower_bound(dp.begin(), dp.end(), v[i]));
			dp[pos] = v[i];
		}
	}
	return dp.size();
}
