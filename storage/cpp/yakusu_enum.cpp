// 約数列挙

// 約数を全て出力する
// 1 の場合は 1 しか出力しない
// N 自身は出力しない(15=1*3*5)
vector<ll> enum_div(ll n) {
	vector<ll> ret;
	for (ll i = 1 ; i * i <= n ; ++i) {
		if (n % i == 0) {
			ret.push_back(i);
			if (i != 1 && i * i != n) {
				ret.push_back(n / i);
			}
		}
	}
	return ret;
}
