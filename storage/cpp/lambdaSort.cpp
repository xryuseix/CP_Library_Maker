// ラムダ式を使ったソート

template<class T>
void lambdaSort(vector<T> &v) {
	sort(all(v), [](auto const& l, auto const& r) {
		return l.fi > r.fi; // このbool式が成り立つ時入れ替える
	});
}
