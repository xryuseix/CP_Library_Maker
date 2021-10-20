// mのn乗modPを計算

// xのn乗%modを計算
ll pow_mod(ll x, ll n, ll mod = MOD) {
	ll res = 1;
	x %= MOD;
	while(n > 0) {
		if(n & 1) res = res*x%mod;
		x = x*x%mod;
		n >>= 1;
	}
	return res;
}
