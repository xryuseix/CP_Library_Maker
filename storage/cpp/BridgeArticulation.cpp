// 無向グラフの橋を求める

class BridgeArticulation {
	int N, num = 0;
	vvi G;
	vi pre, low;
	vb isPassed;

	int culcLow(const int v, const int bef) {
		int nowLow = num;
		low[v] = pre[v] = nowLow;
		for(auto ne : G[v]) {
			if(ne == bef) continue;
			if(ne == 0) {
				low[0] = -1;
			}
			if(pre[ne] == -1) {
				num++;
				culcLow(ne, v);
			}
			chmin(nowLow, low[ne]);
		}
		return low[v] = nowLow;
	}

	void traceGraph(const int v, const int bef) {
		bool is_articulation = false;
		for(auto ne : G[v]) {
			if(ne == bef) continue;
			if(!isPassed[ne]) {
				if(low[ne] >= pre[v] && (bef != -1 || G[v].size() >= 2)) {
					is_articulation = true;
				}
				if(low[ne] == pre[ne]) {
					bridges.emplace_back(min(v, ne), max(v, ne));
				}
				isPassed[ne] = true;
				traceGraph(ne, v);
			}
		}
		if(is_articulation) {
			articulation.push_back(v);
		}
	}

public:
	vpii bridges; // 橋
	vi articulation; // 関節点

	BridgeArticulation(const int _n, const vvi _G) : N(_n), G(_G) {
		pre = vi(N, -1);
		low = vi(N, INF);
		isPassed = vb(N, false);
		isPassed[0] = true;
	}

	void findBridges() {
		culcLow(0, -1);
		traceGraph(0, -1);
		Sort(bridges);
	}

	void show() {
		for(auto p : bridges) {
			cout << p.fi << " " << p.se << endl; 
		}
	}
};
