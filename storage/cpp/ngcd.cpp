// 要素数がnの最大公約数

ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a;}
ll ngcd(vector<ll> a){
	ll d;
	d = a[0];
	for(int i = 1; i < a.size() && d != 1; i++) d = gcd(a[i], d);
	return d;
}
