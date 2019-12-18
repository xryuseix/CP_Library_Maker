// セグメント木

class SegmentTree{
public:
	// [a,b)の最小値を求めるセグメント木
	int n;
	// セグメント木を持つ配列
	vector<int> dat;

	SegmentTree(vi v) {
		n = calc2(v.size());
		vector<int> tmp(n*2 - 1);
		dat = tmp;
		for(int i = 0; i < dat.size(); i++) {
			dat[i] = INF; // 最大値を求めるときはここを変える(1)
		}
		for(int i = 0; i < v.size(); i++) {
			update(i, v[i]);
		}
	}

	// Nより大きい２のべき乗数nを計算
	int calc2(int N){
		int n = 1;
		while(n < N) {
			n *= 2;
		}
		return n;
	}

	// k番目の値(0-indexed)をaに変更
	void update(int k, int a) {
		k += n - 1;
		dat[k] = a;
		//登りながら更新
		while(k > 0) {
			k = (k - 1)/2;
			dat[k] = min(dat[k*2 + 1], dat[k*2 + 2]); // 最大値を求めるときはここを変える(2)
		}
	}

	// [a, b)の最小値を求める．
	int query(int a, int b) { return query(a, b, 0, 0, n); }
	int query(int a, int b, int k, int l, int r) {
		// [a, b)と[l, r)が交差しなければINF
		if(r <= a || b <= l) {
			return INF; // 最大値を求めるときはここを変える(3)
		}
		// [a, b)が[l, r)を完全に含んでいれば接点の値を返す
		if(a <= l && r <= b) {
			return dat[k];
		} else {
			// そうでなければ２つの子の最小値を再帰的に求める
			int vl = query(a, b, k*2 + 1, l, (l + r)/2);
			int vr = query(a, b, k*2 + 2, (l + r)/2, r);
			return min(vl, vr); // 最大値を求めるときはここを変える(4)
		}
	}

	void show() {
		int ret = 2;
		for(int i = 1; i <= 2*n - 1; i++) {
			cout << dat[i - 1] << " ";
			if(i == ret - 1) {
				cout << "\n";
				ret *= 2;
			}
		}
		cout << endl;
	}
};
