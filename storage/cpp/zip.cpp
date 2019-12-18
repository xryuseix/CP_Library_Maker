// 一次元座標圧縮

map<int,int> zip;
int compress(vector<int> &x) {
	int unzip[x.size()];
	sort(x.begin(), x.end());
	x.erase(unique(x.begin(),x.end()),x.end());
	for(int i = 0; i < x.size(); i++){
		zip[x[i]] = i;
		unzip[i] = x[i];
	}
	return x.size();
}
