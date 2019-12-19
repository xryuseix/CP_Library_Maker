// 要素数がnの最大公約数

// gcdも呼ぶ！！！
ll ngcd(vector<ll> a){
	ll d;
	d = a[0];
	for(int i = 1; i < a.size() && d != 1; i++) d = gcd(a[i], d);
	return d;
}
