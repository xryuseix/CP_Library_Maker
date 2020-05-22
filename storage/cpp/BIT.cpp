// BIT(Fenwick Tree)

template <typename T>
class BIT {
	int N;
	vector<T> tree;
public:
	BIT(vector<T> &v) : N(v.size()), tree(vector<T>(v.size() + 1)) {
		rep(i, v.size()) {
			add(i, v[i]);
		}
	}

	void add(int i, T x = 1) {
		for (++i; i <= N; i += i&-i) {
			tree[i] += x;
		}
	}

	T sum(int i) { // [0,i)の和
		T x = 0;
		for (; i; i -= i&-i) {
			x += tree[i];
		}
		return x;
	}

	T sum(int l, int r) { // [l,r)の和
		return sum(r) - sum(l);
	}
};
