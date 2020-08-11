// 最大流

class MaximumFlow {

	int v;

	// 辺を表す構造体(行き先，容量，逆辺のインデックス)
	struct edge {
		int to;
		int cap;
		int rev;
	};

	vector<vector<edge>> G; // グラフの隣接リスト表現
	vector<bool> used; // DFSですでに調べたかのフラグ

	// 増加パスをDFSで探す(今いる頂点, ゴールの頂点, 今の頂点以降のフローの最小値)
	int dfs(int v, int t, int f) {
		if (v == t) return f;
		used[v] = true;
		for (int i = 0; i < G[v].size(); i++) {
			// vから行ける&&cap>0の頂点を全てたどる
			edge& e = G[v][i];
			if (!used[e.to] && e.cap > 0) {
				// 次の頂点(e.to)以降でtまで行けるパスを探索し，その時のフローの最小値をdとする
				int d = dfs(e.to, t, min(f, e.cap));
				if (d > 0) {
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

public:
	MaximumFlow(int _v) : v(_v) {
		used = vector<bool>(v);
		G = vector<vector<edge>>(v);
	}

	// fromからtoへ向かう容景capの辺をグラフに追加する
	void add(int from, int to, int cap) {
		G[from].push_back((edge){to, cap, (int)G[to].size()});
		G[to].push_back((edge){from, 0, (int)G[from].size() - 1});
	}

	// sからtへの最大流を求める
	int maxFlow(int s, int t) {
		int flow = 0;
		while (true) {
			used = vector<bool>(v);
			int f = dfs(s, t, INF);
			if (f == 0) {
				return flow;
			}
			flow += f;
		}
	}
};
