// セグメント木

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
	T calc(T a, T b) { return a + b; }
};

template <typename T>
struct Min {
public:
	// 単位元
	T unit;

	Min(void) {
		// 単位元
		unit = INF;
	}

	// 演算関数
	T calc(T a, T b) { return min(a, b); }
};

template <typename T, class MONOID>
class SegmentTree {
public:
	// セグメント木の葉の要素数
	int n;

	// セグメント木
	vector<T> tree;

	// モノイド
	MONOID mono;

	SegmentTree(vector<T>& v) : n(1 << (int)ceil(log2(v.size()))) {
		tree = vector<T>(n << 1, mono.unit);
		for (int i = 0; i < v.size(); ++i) {
			tree[i + n] = v[i];
		}
		for (int i = n - 1; i > 0; --i) {
			tree[i] = mono.calc(tree[i << 1 | 0], tree[i << 1 | 1]);
		}
	}

	SegmentTree(int _n) : n(1 << (int)ceil(log2(_n))) {
		tree = vector<T>(n << 1, mono.unit);
	}

	// k番目の値(0-indexed)をxに変更
	void update(int k, T x) {
		k += n;
		tree[k] = x;
		for (k = k >> 1; k > 0; k >>= 1) {
			tree[k] = mono.calc(tree[k << 1 | 0], tree[k << 1 | 1]);
		}
	}

	// k番目の値(0-indexed)をxを加算
	void add(int k, T x) {
		k += n;
		tree[k] += x;
		for (k = k >> 1; k > 0; k >>= 1) {
			tree[k] = mono.calc(tree[k << 1 | 0], tree[k << 1 | 1]);
		}
	}

	// [l, r)の最小値(0-indexed)を求める．
	T query(int l, int r) {
		T res = mono.unit;
		l += n;
		r += n;
		while (l < r) {
			if (l & 1) {
				res = mono.calc(res, tree[l++]);
			}
			if (r & 1) {
				res = mono.calc(res, tree[--r]);
			}
			l >>= 1;
			r >>= 1;
		}
		return res;
	}

	T operator[](int k) {
		// st[i]で添字iの要素の値を返す
		if (k - n >= 0 || k < 0) {
			return -INF;
		}
		return tree[tree.size() - n + k];
	}

	void show(int elements = 31) {
		int ret = 2;
		for (int i = 1; i < min(2 * n, elements); ++i) {
			if (tree[i] == mono.unit)
				cout << "UNIT ";
			else
				cout << tree[i] << " ";
			if (i == ret - 1) {
				cout << endl;
				ret <<= 1;
			}
		}
		cout << endl;
	}
};
