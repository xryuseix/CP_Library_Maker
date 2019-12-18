// Union-Find木

class UnionFind {
public:
	// 親の番号を格納する。親だった場合は-(その集合のサイズ)
	vector<int> Parent;

	UnionFind(int N) {
		Parent = vector<int>(N, -1);
	}

	// Aがどのグループに属しているか調べる
	int root(int A) {
		if (Parent[A] < 0) return A;
		return Parent[A] = root(Parent[A]);
	}

	// 自分のいるグループの頂点数を調べる
	int size(int A) {
		return -Parent[root(A)];//親をとってきたい]
	}

	// AとBをくっ付ける
	bool connect(int A, int B) {
		//AとBを直接つなぐのではなく、root(A)にroot(B)をくっつける
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
		}

		// Aのサイズを更新する
		Parent[A] += Parent[B];
		// Bの親をAに変更する
		Parent[B] = A;

		return true;
	}
};
