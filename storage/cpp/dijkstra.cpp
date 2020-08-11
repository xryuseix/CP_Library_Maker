// ダイクストラ法

class DIJKSTRA {
public:
	int V;

	struct dk_edge {
		int to;
		ll cost;
	};

	typedef pair<ll, int> PI;  // firstは最短距離、secondは頂点の番号
	vector<vector<dk_edge> > G;
	vector<ll> d;      //これ答え。d[i]:=V[i]までの最短距離
	vector<int> prev;  //経路復元

	DIJKSTRA(int size) {
		V = size;
		G = vector<vector<dk_edge> >(V);
		prev = vector<int>(V, -1);
	}

	void add(int from, int to, ll cost) {
		dk_edge e = {to, cost};
		G[from].push_back(e);
	}

	void dijkstra(int s) {
		// greater<P>を指定することでfirstが小さい順に取り出せるようにする
		priority_queue<PI, vector<PI>, greater<PI> > que;
		d = vector<ll>(V, LLINF);
		d[s] = 0;
		que.push(PI(0, s));

		while (!que.empty()) {
			PI p = que.top();
			que.pop();
			int v = p.second;
			if (d[v] < p.first) continue;
			for (int i = 0; i < G[v].size(); i++) {
				dk_edge e = G[v][i];
				if (d[e.to] > d[v] + e.cost) {
					d[e.to] = d[v] + e.cost;
					prev[e.to] = v;
					que.push(PI(d[e.to], e.to));
				}
			}
		}
	}
	vector<int> get_path(int t) {
		vector<int> path;
		for (; t != -1; t = prev[t]) {
			// tがsになるまでprev[t]をたどっていく
			path.push_back(t);
		}
		//このままだとt->sの順になっているので逆順にする
		reverse(path.begin(), path.end());
		return path;
	}
	void show(void) {
		for (int i = 0; i < d.size() - 1; i++) {
			cout << d[i] << " ";
		}
		cout << d[d.size() - 1] << endl;
	}
};
