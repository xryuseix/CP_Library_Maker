// 最小費用流

class MinCostFlow {

	int V; // 頂点数

	// 辺を表す構造体(行き先，容量，逆辺のインデックス)
	struct edge {
		int to;
		int cap;
		int cost;
		int rev;
	};

	vector<vector<edge>> G; // グラフの隣接リスト表現
	vector<int> h; // ポテンシャル
	vector<int> prevV; // 直前の頂点
	vector<int> prevE; // 直前の辺
	vector<int> dist; // 最短距離
	typedef pair<int, int> PI;

public:
	MinCostFlow(int _v) : V(_v) {
		G = vector<vector<edge>>(V);
		h = vector<int>(V);
		prevV = vector<int>(V);
		prevE = vector<int>(V);
	}

	// fromからtoへ向かう容景capの辺をグラフに追加する
	void add(int from, int to, int cap, int cost) {
		G[from].push_back((edge){to, cap, cost, (int)G[to].size()});
		G[to].push_back((edge){from, 0, -cost, (int)G[from].size() - 1});
	}

	// sからtへの最大流を求める
	int minCostFlow(int s, int t, int f) {
		int res = 0;
		while (f > 0) {
			// ダイクストラ法を用いてhを更新する
			priority_queue<PI, vector<PI>, greater<PI>> que;
			dist = vector<int>(V, INF);
			dist[s] = 0;
			que.push(PI(0, s));
			while(!que.empty()) {
				PI p = que.top();
				que.pop();
				int v = p.second;
				if(dist[v] < p.first) continue;
				for (int i = 0; i < G[v].size(); i++) {
					edge e = G[v][i];
					if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
						dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
						prevV[e.to] = v;
						prevE[e.to] = i;
						que.push(PI(dist[e.to], e.to));
					}
				}
			}
			if(dist[t] == INF) {
				// これ以上流せない
				return -1;
			}
			for(int v = 0; v < V; v++) {
				h[v] += dist[v];
			}
			// s-t問最短路に沿って目一杯流す
			int d = f;
			for(int v = t; v != s; v = prevV[v] ) {
				d = min(d, G[prevV[v]][prevE[v]].cap);
			}
			f -= d;
			res += d*h[t];
			for(int v = t; v != s; v = prevV[v]) {
				edge& e = G[prevV[v]][prevE[v]];
				e.cap -= d;
				G[v][e.rev].cap += d;
			}
		}
		return res;
	}
};
