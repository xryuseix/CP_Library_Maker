// 遅延評価セグメント木

template <typename T>
class Sum {
public:
	// 単位元
	T unit;
	
	Sum(void) {
		// 単位元
		unit = 0;
	}

	// 演算関数
	T calc(T a, T b) {
		return a + b; 
	}
};

template <typename T, class MONOID>
class LazySegmentTree {
public:
	// セグメント木の葉の要素数
	int n;

	// セグメント木
	vector<T> tree, lazy;

	// モノイド
	MONOID mono;

	LazySegmentTree(vector<T> &v) {
		n = 1 << (int)ceil(log2(v.size()));
		tree = vector<T>(n << 1);
		lazy = vector<T>(n << 1, mono.unit);
		for(int i = 0; i < v.size(); ++i) {
			update(i, v[i]);
		}
		for(int i = v.size(); i < n; ++i) {
			update(i, mono.unit);
		}
	}

	// k番目の値(0-indexed)をxに変更
	void update(int k, T x) {
		k += n;
		tree[k] = x;
		for(k = k >> 1; k > 0; k >>= 1){
			tree[k] = mono.calc(tree[k << 1 | 0], tree[k << 1 | 1]);
		}
	}

	// [l, r)の最小値(0-indexed)を求める．
	T query(int l, int r) {
		T res = mono.unit;
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

	// k番目のノードの遅延評価を行う
	void eval(int k, int l, int r) {
		// 遅延評価配列が空でない時，値を伝播する
		if(lazy[k] != mono.unit) {
			tree[k] += lazy[k];
			if(r - l > 1) {
				lazy[k<<1|0] += lazy[k]>>1;
				lazy[k<<1|1] += lazy[k]>>1;
			}

			// 伝播が終わったので自ノードの遅延配列を空にする
			lazy[k] = mono.unit;
		}
	}

	// 区間[l, r)にxを足す(遅延評価)
	void add(int l, int r, ll x) {
		add(l, r, x, 1, 0, n);
	}

	void add(int a, int b, ll x, int k, int l, int r) {
		// k番目のノードに対して遅延評価を行う
		eval(k, l, r);

		// 範囲外なら何もしない
		if(b <= l || r <= a) return;
		
		// 完全に被覆しているならば、遅延配列に値を入れた後に評価
		if(a <= l && r <= b) {
			lazy[k] += (r - l) * x;
			eval(k, l, r);
		} else {
			add(a, b, x, k<<1|0, l, (l + r)>>1);
			add(a, b, x, k<<1|1, (l + r)>>1, r);
			tree[k] = tree[k<<1|0] + tree[k<<1|1];
		}
	}

	// 区間[l, r)の合計を取得する
	ll getRange(int l, int r) {
		return getRange(l, r, 1, 0, n);
	}

	ll getRange(int a, int b, int k, int l, int r) {
		if(b <= l || r <= a) return mono.unit;
		// 関数が呼び出されたら評価！
		eval(k, l, r);
		if(a <= l && r <= b) return tree[k];
		ll vl = getRange(a, b, k<<1|0, l, (l + r)>>1);
		ll vr = getRange(a, b, k<<1|1, (l + r)>>1, r);
		return vl + vr;
	}

	T operator[](int k) {
		// st[i]で添字iの要素の値を返す
		if(k - n >= 0 || k < 0) {
			return -INF;
		}
		return tree[tree.size() - n + k];
	}

	void show(void) {
		showTree();
		showLazy();
	}

	void showTree(void) {
		int ret = 2;
		for(int i = 1; i < 2*n; ++i) {
			if(tree[i] == mono.unit) cout << "UNIT ";
			else cout << tree[i] << " ";
			if(i == ret - 1) {
				cout << endl;
				ret <<= 1;
			}
		}
		cout << endl;
	}

	void showLazy(void) {
		int ret = 2;
		for(int i = 1; i < 2*n; ++i) {
			if(lazy[i] == mono.unit) cout << "UNIT ";
			else cout << lazy[i] << " ";
			if(i == ret - 1) {
				cout << endl;
				ret <<= 1;
			}
		}
		cout << endl;
	}
};
