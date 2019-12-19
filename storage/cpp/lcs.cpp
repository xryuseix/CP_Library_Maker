// 最長共通部分列問題を解く

string lcs(string s, string t) {
	vvi dp(s.size() + 1, vi(t.size() + 1));
	
	for(int i = 0; i < s.size(); i++) {//LCS
		for(int j = 0; j < t.size(); j++) {
			if(s[i] == t[j]) {
				dp[i + 1][j + 1] = dp[i][j] + 1;
			}
			else{
				dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
			}
		}
	}
	// 復元
	string ans = "";
	int i = (int)s.size(), j = (int)t.size();
	while (i > 0 && j > 0){
		// (i-1, j) -> (i, j) と更新されていた場合
		if (dp[i][j] == dp[i-1][j]) {
			--i; // DP の遷移を遡る
		}
		// (i, j-1) -> (i, j) と更新されていた場合
		else if (dp[i][j] == dp[i][j-1]) {
			--j; // DP の遷移を遡る
		}
		// (i-1, j-1) -> (i, j) と更新されていた場合
		else {
			ans = s[i-1] + ans;
			--i, --j; // DP の遷移を遡る
		}
	}
	return ans;
}
