// セグメント木

class Monoid {
public:
	// 単位元
	int unit;
	
	Monoid(void) {
		// 単位元
		unit = INF;
	}

	// 演算関数
	int calc(int a, int b) {
		return min(a, b); 
	}
};

class SegmentTree {
public:
	// セグメント木の葉の要素数
	int n;

	// セグメント木
	vector<int> tree;

	// モノイド
	Monoid mono;

	SegmentTree(vector<int> &v) {
		n = 1 << (int)ceil(log2(v.size()));
		tree = vector<int>(n << 1);
		for(int i = 0; i < v.size(); i++) {
			update(i, v[i]);
		}
		for(int i = v.size(); i < n; i++) {
			update(i, mono.unit);
		}
	}

	// k番目の値(0-indexed)をxに変更
	void update(int k, int x) {
		k += n;
		tree[k] = x;
		for(k = k >> 1; k > 0; k >>= 1){
			tree[k] = mono.calc(tree[k << 1 | 0], tree[k << 1 | 1]);
		}
	}

	// [l, r)の最小値(0-indexed)を求める．
	int query(int l, int r) {
		int res = mono.unit;
		l += n;
		r += n;
		while(l < r) {
			if(l & 1) {
				res = mono.calc(res, tree[l++]);
			}
			if(r & 1) {
				res = mono.calc(res, tree[--r]);
			}
			l >>= 1;
			r >>= 1;
		}
		return res;
	}
	int operator[](int k) {
		// st[i]で添字iの要素の値を返す
		if(k - n >= 0 || k < 0) {
			return -INF;
		}
		return tree[tree.size()-n+k];
	}

	void show(void) {
		int ret = 2;
		for(int i = 1; i < 2*n; i++) {
			cout << tree[i] << " ";
			if(i == ret - 1) {
				cout << endl;
				ret <<= 1;
			}
		}
		cout << endl;
	}
};
