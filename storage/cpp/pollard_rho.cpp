// ポラード・ロー素因数分解法

// miller_rabinを呼ぶ！！
ll gcd_norecursive(ll _a, ll _b) {
	ull a = abs(_a), b = abs(_b);
	if (a == 0) return b;
	if (b == 0) return a;
	int shift = __builtin_ctz(a | b);
	a >>= __builtin_ctz(a);
	do {
		b >>= __builtin_ctz(b);
		if (a > b) swap(a, b);
		b -= a;
	} while (b);
	return (a << shift);
}

ll pollard_single(ll n) {
	auto rand = [&](ll x) -> ll { return (__int128_t(x) % n * x % n + 1) % n; };
	if (miller_rabin(n)) {
		return n;
	}
	if (n % 2 == 0) {
		return 2;
	}
	ll st = 0;
	while (true) {
		st++;
		ll x = st, y = rand(x), d = 1;
		while (d == 1) {
			d = gcd_norecursive(y - x + n, n);
			if (d == n || d == 0) {
				break;
			} else if (d != 1) {
				return d;
			}
			x = rand(x);
			y = rand(rand(y));
		}
	}
};

// 受け取るときにソートすること
vll pollard_rho(ll n) {
	if (n == 1) {
		return {};
	}
	ll x = pollard_single(n);
	if (x == n) return {x};
	vll primes = pollard_rho(x);
	vll primes_inverse = pollard_rho(n / x);
	primes.insert(primes.end(), primes_inverse.begin(), primes_inverse.end());
	return primes;
}
