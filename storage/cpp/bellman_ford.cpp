// ベルマンフォード法

// 頂点fromから頂点toへのコストcostの辺
struct bf_edge {
	int from;
	int to;
	int cost;
};

class Bellman_Ford{
public:
	vector<bf_edge> es; // 辺
	vector<int> d; // d[i]...頂点sから頂点iまでの最短距離
	int V, E; // Vは頂点数、Eは辺数

	Bellman_Ford(int v, int e) {
		V = v;
		E = e;
		d = vector<int>(v);
	}

	void add(int from, int to, int cost) {
		bf_edge ed = {from, to, cost};
		es.push_back(ed);
	}

	// s番目の頂点から各頂点への最短距離を求める
	void shortest_path(int s) {
		for(int i = 0; i < V; i++) {
			d[i] = INF;
		}
		d[s] = 0;
		while(true) {
			bool update = false;
			for(int i = 0; i < E; i++) {
				bf_edge e = es[i];
				if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
					d[e.to] = d[e.from] + e.cost;
					update = true;
				}
			}
			if (!update) break;
		}
	}
	// trueなら負の閉路が存在する
	bool is_nagative_loop(void) {
		for(int i = 0; i < V; i++) {
			d[i] = 0;
		}
		for (int i = 0; i < 3*V; i++) {
			for(int j = 0; j < E; j++) {
				bf_edge e = es[j];
				if(d[e.to] > d[e.from] + e.cost) {
					d[e.to] = d[e.from] + e.cost;

					// 3n回目にも更新があるなら負の閉路が存在する
					if(i == V - 1)return true;
				}
			}
		}
		return false;
	}
};
