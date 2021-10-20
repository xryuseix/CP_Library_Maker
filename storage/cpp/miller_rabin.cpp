// ミラーラビン素数判定法

// xのn乗%modを計算
ll pow_mod_i128(__int128_t x, ll n, ll mod = MOD) {
	ll res = 1;
	x %= MOD;
	while (n) {
		if (n & 1) res = res * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return res;
}

// 素数判定
bool miller_rabin(ll x) {
	if (x <= 2) {
		return x == 2;
	}
	if (x % 2 == 0) {
		return false;
	}
	ll d = x - 1;
	while (d % 2 == 0) d /= 2;
	for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
		if (x <= a) {
			return true;
		}
		ll t = d;
		ll y = pow_mod_i128(a, t, x);
		while (t != x - 1 && y != 1 && y != x - 1) {
			y = __int128_t(y) * y % x;
			t <<= 1;
		}
		if (y != x - 1 && t % 2 == 0) {
			return false;
		}
	}
	return true;
}
