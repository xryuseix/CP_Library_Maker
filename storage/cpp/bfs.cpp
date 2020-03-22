// 幅優先探索

// 各座標に格納したい情報を構造体にする
// 今回はX座標,Y座標,深さ(距離)を記述している
struct Corr {
	int x;
	int y;
	int depth;
};
queue<Corr> q;
int bfs(vector<vector<int>> grid) {
	// 既に探索の場所を1，探索していなかったら0を格納する配列
	vector<vector<int>> ispassed(grid.size(), vector<int>(grid[0].size(), false));
	// このような記述をしておくと，この後のfor文が綺麗にかける
	int dx[8] = {1, 0, -1, 0};
	int dy[8] = {0, 1, 0, -1};
	while(!q.empty()) {
		Corr now = q.front();q.pop();
		/*
			今いる座標は(x,y)=(now.x, now.y)で，深さ(距離)はnow.depthである
			ここで，今いる座標がゴール(探索対象)なのか判定する
		*/
		for(int i = 0; i < 4; i++) {
			int nextx = now.x + dx[i];
			int nexty = now.y + dy[i];

			// 次に探索する場所のX座標がはみ出した時
			if(nextx >= grid[0].size()) continue;
			if(nextx < 0) continue;

			// 次に探索する場所のY座標がはみ出した時
			if(nexty >= grid.size()) continue;
			if(nexty < 0) continue;

			// 次に探索する場所が既に探索済みの場合
			if(ispassed[nexty][nextx]) continue;

			ispassed[nexty][nextx] = true;
			Corr next = {nextx, nexty, now.depth+1};
			q.push(next);
		}
	}
}
