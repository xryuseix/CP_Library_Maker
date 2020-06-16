// LCA(最近共通祖先)

class LCA {
	int n;
	int MAX;
	vvi doubling, v;

	void init() {
		rep(i, n) {
			for(auto j : v[i]) {
				doubling[0][j] = i;
			}
		}
		for(int i = 1; i < MAX; i++) {
			rep(j, n) {
				doubling[i][j] = doubling[i - 1][doubling[i - 1][j]];
			}
		}
		depth[0] = 0;
		dfs(0, -1);
	}

	void dfs(const int crrPos, const int befPos) {
		for(auto i : v[crrPos]) {
			if(i == befPos || depth[i] != -1) {
				continue;
			}
			depth[i] = depth[crrPos] + 1;
			dfs(i, crrPos);
		}
	}

public:
	vi depth;

	// vは0が根のbfs木にする．親->子のように辺を張る．
	LCA(vvi &_v) : v(_v), n(_v.size()) {
		MAX = ceil(log2(n));
		doubling = vvi(MAX, vi(n, 0));
		depth = vi(n, -1);
		init();
	}

	void show(const int height = 0) {
		rep(i, ((!height)?MAX:height)) {
			dump(doubling[i]);
		}
		dump(depth);
	}

	// ダブリングでVのnum個親の祖先を調べる
	int doublingNode(int V, const int num) {
		rep(i, MAX) {
			if((1LL<<i) & num) {
				V = doubling[i][V];
			}
		}
		return V;
	}

	int lca(int A, int B) {
		// Aのが深い位置にあるようにする
		if(depth[A] < depth[B]) {
			swap(A, B);
		}
		A = doublingNode(A, depth[A] - depth[B]);
		if(A == B) {
			return A;
		}

		for (int k = MAX - 1; k >= 0; k--) {
			if (doubling[k][A] != doubling[k][B]) {
				A = doubling[k][A];
				B = doubling[k][B];
			}
		}
		return doubling[0][A];
	}
};
