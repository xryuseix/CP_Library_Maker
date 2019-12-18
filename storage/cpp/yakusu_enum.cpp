// 約数列挙

vector<int> enum_div(int n){
	vector<int> ret;
	for(int i = 1 ; i*i <= n ; ++i){
		if(n%i == 0){
			ret.push_back(i);
			if(i != 1 && i*i != n){
				ret.push_back(n/i);
			}
		}
	}
	return ret;
}
