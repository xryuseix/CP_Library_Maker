// 素因数分解

map<ll, ll> prime;
void factorize(ll n) {
	for(ll i = 2; i * i <= n; i++) {
		while(n % i == 0) {
			prime[i]++;
			n /= i;
		}
	}
	if(n != 1) {
		prime[n] = 1;
	}
}
