// 遅延評価セグメント木

template <class X, class MONOID, class M, class MANAGE>
class LazySegmentTree {
public:
	// セグメント木の葉の要素数
	int n;

	// セグメント木
	vector<X> tree;
	vector<M> lazy;

	// モノイド
	MONOID mono;
	MANAGE manage;

	LazySegmentTree(const vector<X>& v) : n(1 << (int)ceil(log2(v.size()))) {
		tree = vector<X>(n << 1, mono.unit);
		lazy = vector<M>(n << 1, manage.unit);
		for (int i = 0; i < v.size(); ++i) {
			tree[i + n] = v[i];
		}
		for (int i = n - 1; i > 0; --i) {
			tree[i] = mono.calc(tree[i << 1 | 0], tree[i << 1 | 1]);
		}
	}

	LazySegmentTree(const int _n) : n(1 << (int)ceil(log2(_n))) {
		tree = vector<X>(n << 1, mono.unit);
		lazy = vector<M>(n << 1, manage.unit);
	}

	// k 番目のノードの遅延評価を行う
	void eval(const int k, int l, int r) {
		// 遅延評価配列が空でない時，値を伝播する
		if (lazy[k] == manage.unit) {
			return;
		}
		if (k < n) {
			lazy[k << 1 | 0] = manage.fm(lazy[k << 1 | 0], lazy[k]);
			lazy[k << 1 | 1] = manage.fm(lazy[k << 1 | 1], lazy[k]);
		}
		tree[k] = manage.fa(tree[k], lazy[k], r - l);
		// 伝播が終わったので自ノードの遅延配列を空にする
		lazy[k] = manage.unit;
	}

	// 区間 [l, r) の値を全て更新する(遅延評価)
	void updateRange(const int l, const int r, const X x) {
		updateRange(l, r, x, 1, 0, n);
	}

	void updateRange(const int a, const int b, const X x, const int k,
					const int l, const int r) {
		// k 番目のノードに対して遅延評価を行う
		eval(k, l, r);

		// 完全に被覆しているならば、遅延配列に値を入れた後に評価
		if (a <= l && r <= b) {
			lazy[k] = manage.fm(lazy[k], x);
			eval(k, l, r);
		} else if (a < r && l < b) {
			updateRange(a, b, x, k << 1 | 0, l, (l + r) >> 1);
			updateRange(a, b, x, k << 1 | 1, (l + r) >> 1, r);
			tree[k] = mono.calc(tree[k << 1 | 0], tree[k << 1 | 1]);
		}
	}

	// 区間 [l, r) の merge 結果を取得する
	X getRange(const int l, const int r) { return getRange(l, r, 1, 0, n); }

	X getRange(const int a, const int b, const int k, const int l,
			const int r) {
		// 関数が呼び出されたら評価！
		eval(k, l, r);
		if (r <= a || b <= l) {  // 完全に外側の時
			return mono.unit;
		} else if (a <= l && r <= b) {  // 完全に内側の時
			return tree[k];
		} else {  // 一部区間が被る時
			X vl = getRange(a, b, k << 1 | 0, l, (l + r) >> 1);
			X vr = getRange(a, b, k << 1 | 1, (l + r) >> 1, r);
			return mono.calc(vl, vr);
		}
	}

	X operator[](const int k) {
		// st[i] で添字 i の要素の値を返す
		if (k - n >= 0 || k < 0) {
			return -INF;
		}
		return tree[tree.size() - n + k];
	}

	void show(void) {
		this->showTree(tree);
		this->showLazy(lazy);
	}

	template <class T>
	void showTree(vector<T>& tree) {
		int ret = 2;
		for (int i = 1; i < 2 * n; ++i) {
			if (tree[i] == mono.unit) {
				cout << "UNIT ";
			} else {
				cout << tree[i] << " ";
			}
			if (i == ret - 1) {
				cout << endl;
				ret <<= 1;
			}
		}
		cout << endl;
	}
};

using X = ll;
using M = ll;

struct Monoid {
	Monoid(void) {}

	struct Sum {
		const X unit = 0;
		static X calc(X a, X b) { return a + b; }
	};
	struct Min {
		const X unit = INF;
		static X calc(X a, X b) { return min(a, b); }
	};

	// モノイド
	Sum monoid;

	// 単位元
	X unit = monoid.unit;

	// 演算関数
	function<X(X, X)> calc = monoid.calc;
};

struct Manage {
	Manage(void) {}

	struct Add {
		const M unit = 0;
		static M fa(X x, M m, size_t size) { return x + m * size; }  // RSQ+RAQ
		static M fa2(X x, M m, size_t size) { return x + m; }        // RMQ+RAQ
		static M fm(M m1, M m2) { return m1 + m2; }
	};
	struct Update {
		const M unit = INF;
		static M fa(X x, M m, size_t size) { return m * size; }  // RSQ+RUQ
		static M fa2(X x, M m, size_t size) { return m; }        // RMQ+RUQ
		static M fm(M m1, M m2) { return m2; }
	};

	// 作用構造体
	Update manage;

	// 単位元
	M unit = manage.unit;

	// 演算関数
	function<M(X, M, size_t)> fa = manage.fa;
	function<M(M, M)> fm = manage.fm;
};
