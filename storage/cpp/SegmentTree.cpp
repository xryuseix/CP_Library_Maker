// セグメント木

class SegmentTree{
public:
	// [a,b)の最小値を求めるセグメント木
	int n;
	// セグメント木を持つ配列
	vector<int> dat;

	SegmentTree(vi &v) {
		n = 1 << (int)ceil(log2(v.size()));
		dat = vector<int>((n<<1) - 1);
		for(int i = 0; i < v.size(); i++) {
			update(i, v[i]);
		}
		for(int i = v.size(); i < n; i++) {
			update(i, INF);
		}
	}

	// k番目の値(0-indexed)をxに変更
	void update(int k, int x) {
		k += n;
		dat[k - 1] = x;
		for(k = k >> 1; k > 0; k >>= 1){
			dat[k - 1] = min(dat[2*k - 1], dat[2*k]);
		}
	}

	// [a, b)の最小値を求める．
	int query(int a, int b) { return query(a, b, 0, 0, n); }
	int query(int a, int b, int k, int l, int r) {
		// [a, b)と[l, r)が交差しなければINF
		if(r <= a || b <= l) {
			return INF;
		}
		// [a, b)が[l, r)を完全に含んでいれば接点の値を返す
		if(a <= l && r <= b) {
			return dat[k];
		} else {
			// そうでなければ２つの子の最小値を再帰的に求める
			int vl = query(a, b, k*2 + 1, l, (l + r)/2);
			int vr = query(a, b, k*2 + 2, (l + r)/2, r);
			return min(vl, vr);
		}
	}
	
}

	void show() {
		int ret = 2;
		for(int i = 1; i <= 2*n - 1; i++) {
			cout << dat[i - 1] << " ";
			if(i == ret - 1) {
				cout << "
";
				ret <<= 1;
			}
		}
		cout << endl;
	}
};
