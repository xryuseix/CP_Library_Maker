// 配列の表示

template<class T>
void print_vector(vector<T> &v) {
	rep(i, v.size()) {
		if(!i) cout << v[i];
		else cout << " " << v[i];
	}
	cout << endl;
}
