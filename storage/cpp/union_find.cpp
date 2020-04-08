// Union-Find木

class UnionFind {
public:
	// 親の番号を格納．親だった場合は-(その集合のサイズ)
	vector<int> Parent;
	// 重さの差を格納
	vector<ll> diffWeight;

	UnionFind(const int N) {
		Parent = vector<int>(N, -1);
		diffWeight = vector<ll>(N, 0);
	}

	// Aがどのグループに属しているか調べる
	int root(const int A) {
		if (Parent[A] < 0) return A;
		int Root = root(Parent[A]);
		diffWeight[A] += diffWeight[Parent[A]];
		return Parent[A] = Root;
	}

	// 自分のいるグループの頂点数を調べる
	int size(const int A) {
		return -Parent[root(A)];
	}

	// 自分の重さを調べる
	ll weight(const int A) {
		root(A); // 経路圧縮
		return diffWeight[A];
	}

	// 重さの差を計算する
	ll diff(const int A, const int B) {
		return weight(B) - weight(A);
	}

	// AとBをくっ付ける
	bool connect(int A, int B, ll W = 0) {
		// Wをrootとの重み差分に変更
		W += weight(A);
		W -= weight(B);

		// AとBを直接つなぐのではなく、root(A)にroot(B)をくっつける
		A = root(A);
		B = root(B);

		if (A == B) {
			//すでにくっついてるからくっ付けない
			return false;
		}

		// 大きい方(A)に小さいほう(B)をくっ付ける
		// 大小が逆だったらひっくり返す
		if (size(A) < size(B)) {
			swap(A, B);
			W = -W;
		}

		// Aのサイズを更新する
		Parent[A] += Parent[B];
		// Bの親をAに変更する
		Parent[B] = A;

		// AはBの親であることが確定しているのでBにWの重みを充てる
		diffWeight[B] = W;

		return true;
	}
};
