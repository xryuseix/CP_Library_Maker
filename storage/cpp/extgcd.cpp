// 拡張ユークリッドの互助法

// x,y に ax + by = gcd(a, b) を満たす値が格納される
// 返り値は<gcd(a, b), x, y>
// auto [g, x, y] = extgcd(a, b);のように呼び出す
tuple<ll, ll, ll> extgcd(ll a, ll b) {
	if (b == 0) {
		return {a, 1, 0};
	}
	auto [g, x, y] = extgcd(b, a % b);
	return {g, y, x - a / b * y};
}
