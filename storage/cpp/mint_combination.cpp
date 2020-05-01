// mintの二項定理

#define MAX_MINT_NCK 201010
mint f[MAX_MINT_NCK], rf[MAX_MINT_NCK];

bool isinit = false;

void init() {
	f[0] = 1;
	rf[0] = 1;
	for(int i = 1; i < MAX_MINT_NCK; i++) {
		f[i] = f[i - 1] * i;
		// rf[i] = modinv(f[i].x);
		rf[i] = f[i].pow(f[i], MOD - 2);
	}
}

mint nCk(mint n, mint k) {
	if(n < k) return 0;
	if(!isinit) {
		init();
		isinit = 1;
	}
	mint nl = f[n.x]; // n!
	mint nkl = rf[n.x - k.x]; // (n-k)!
	mint kl = rf[k.x]; // k!
	mint nkk = (nkl.x * kl.x);

	return nl * nkk;
}
