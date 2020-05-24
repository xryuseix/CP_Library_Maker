// 拡張ユークリッドの互助法

// x,y に ax + by = gcd(a, b) を満たす値が格納される
ll extgcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll d = extgcd(b, a%b, y, x);
	y -= a/b * x;
	return d;
}
