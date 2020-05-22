// 一次元座標圧縮

map<ll, ll> zip;
int compress(vector<ll> x) {
	int unzip[x.size()];
	sort(x.begin(), x.end());
	x.erase(unique(x.begin(),x.end()),x.end());
	for(int i = 0; i < x.size(); i++){
		zip[x[i]] = i;
		unzip[i] = x[i];
	}
	return x.size();
}
