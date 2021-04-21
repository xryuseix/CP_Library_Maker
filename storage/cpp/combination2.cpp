// 逆元を使わないnCk

// 逆元を使わないnCk
// なんでこうなるかわよくわからん
const int NCKMAX = 3;
int C[NCKMAX][NCKMAX];
bool isinit = false;
void init() {
	rep(i, NCKMAX) { C[i][0] = C[i][i] = 1; }
	for (int i = 1; i < NCKMAX; i++) {
		for (int j = 1; j < i; j++) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % NCKMAX;
		}
	}
}

int nCk(int n, int k) {
	if (!isinit) {
		init();
		isinit = 1;
	}
	if (k < 0 || k > n) return 0;
	int ans = 1;
	while (n > 0) {
		int x = n % NCKMAX;
		int y = k % NCKMAX;
		n /= NCKMAX;
		k /= NCKMAX;
		ans = (ans * C[x][y]) % NCKMAX;
	}
	return ans;
}
