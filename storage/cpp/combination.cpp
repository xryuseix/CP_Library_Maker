// 組み合わせ・逆元でnCkを求める

#define MAX_NCK 101010
ll f[MAX_NCK], rf[MAX_NCK];

// modinvも呼ぶ！！

bool isinit = false;

void init(void) {
	f[0] = 1;
	rf[0] = modinv(1);
	for(int i = 1; i < MAX_NCK; i++) {
		f[i] = (f[i - 1] * i) % MOD;
		rf[i] = modinv(f[i]);
	}
}

ll nCk(int n, int k) {
	if(!isinit) {
		init();
		isinit = 1;
	}
	ll nl = f[n]; // n!
	ll nkl = rf[n - k]; // (n-k)!
	ll kl = rf[k]; // k!
	ll nkk = (nkl * kl) % MOD;

	return (nl * nkk) % MOD;
}
