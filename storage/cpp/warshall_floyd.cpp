// ワーシャルフロイド法

class WAR_FLY {
public:
	vvi d; //辺の数
	int V; //頂点の数
	
	WAR_FLY(int n) {
		V = n;
		d = vector<vector<int> > (n,vector<int>(n));
		for(int i = 0; i < V; i++) {
			for(int j = 0; j < V; j++) {
				if(i == j) {
					d[i][j] = 0;
				}
				else {
					d[i][j] = INF;
				}
			}
		}
	}

	void warshall_floyd() {
		for(int k = 0; k < V; k++) {
			for(int i = 0; i < V; i++) {
				for(int j = 0; j < V; j++) {
					d[i][j] = min((ll)d[i][j], (ll)d[i][k] + (ll)d[k][j]);
				}
			}
		}
	}

	void add(int from, int to, int cost) {
		d[from][to] = cost;
	}

	bool is_negative_loop() {
		for(int i = 0; i < V; i++) {
			if(d[i][i] < 0) return true;
		}
		return false;
	}

	void show() {
		for(int i = 0; i < V; i++) {
			for(int j = 0; j < V; j++) {
				cout << d[i][j] << " ";
			}
			cout << endl;
		}
	}
};
