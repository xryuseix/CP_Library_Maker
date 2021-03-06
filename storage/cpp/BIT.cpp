// BIT(Fenwick Tree)

template <typename T>
class BIT {
	int N;
	vector<T> tree;

public:
	BIT(vector<T>& v) : N(v.size()), tree(vector<T>(v.size() + 1)) {
		rep(i, v.size()) { add(i, v[i]); }
	}
	BIT(int n) : N(n), tree(vector<T>(n + 1)) {}

	void add(int i, T x = 1) {
		for (++i; i <= N; i += i & -i) {
			tree[i] += x;
		}
	}

	T sum(int l) {  // [0, l)の和
		T x = 0;
		for (; l; l -= l & -l) {
			x += tree[l];
		}
		return x;
	}

	T sum(int l, int r) {  // [l, r)の和
		return sum(r) - sum(l);
	}

	T sum_back(int l) {  // [l, N)の和
		return sum(N) - sum(l);
	}
};
