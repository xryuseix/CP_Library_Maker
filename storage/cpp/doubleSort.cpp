// 二つの配列をソート

template <class T, class U>
void doubleSort(vector<T>& v, vector<U>& w) {
	assert(v.size() == w.size());
	vector<pair<T, U>> p(v.size());
	rep(i, v.size()) { p[i] = mp(v[i], w[i]); }
	Sort(p);
	rep(i, p.size()) {
		v[i] = p[i].first;
		w[i] = p[i].second;
	}
}
