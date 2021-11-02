// 写像12相数え上げライブラリ

// modint呼ぶ！！！

class Counting {
	struct pre_calculation {
		bool factorial;
		bool partition;
		bool combination;
		bool bell;
	};
	pre_calculation pre_calc;

	vector<mint> Factorial;
	void factorial_precalc(const int MAX = 301010) {
		Factorial = vector<mint>(MAX, 1);
		for (int i = 1; i < MAX; i++) {
			Factorial[i] = Factorial[i - 1] * i;
		}
	}

	vector<mint> FactorialInv;
	void nCk_precalc(const int MAX = 301010) {
		if (!pre_calc.factorial) {
			factorial_precalc();
		}
		FactorialInv = vector<mint>(MAX, 1);
		for (int i = 1; i < MAX; i++) {
			FactorialInv[i] = mint(1).pow(Factorial[i], MOD - 2);
		}
	}

	vector<mint> Bell;
	void bell_precalc(const int MAX = 2020) {
		if (!pre_calc.factorial) {
			factorial_precalc();
		}
		Bell = vector<mint>(MAX, 1);
		for (int j = 1; j < MAX; j++) {
			Bell[j] = Bell[j - 1] + mint(0).pow(-1, j) / Factorial[j];
		}
	}

	vector<vector<mint>> Partition;
	void partition_precalc(const int MAX = 2020) {
		Partition = vector<vector<mint>>(MAX, vector<mint>(MAX, 0));
		for (int k = 0; k < MAX; k++) {
			Partition[0][k] = 1;
		}
		for (int n = 1; n < MAX; n++) {
			for (int k = 1; k < MAX; k++) {
				Partition[n][k] = Partition[n][k - 1];
				if (n - k >= 0) {
					Partition[n][k] += Partition[n - k][k];
				}
			}
		}
	}

public:
	Counting(void) {
		pre_calc.factorial = false;
		pre_calc.partition = false;
		pre_calc.combination = false;
		pre_calc.bell = false;
	};

	// 階乗 n! を計算
	mint factorial(const mint n) {
		if (!pre_calc.factorial) {
			factorial_precalc();
			pre_calc.factorial = true;
		}
		return Factorial[n.x];
	}

	// 二項係数 nCk を計算
	mint nCk(const mint n, const mint k) {
		if (n < k) {
			return 0;
		}
		if (!pre_calc.combination) {
			nCk_precalc();
			pre_calc.combination = true;
		}
		mint nl = Factorial[n.x];            // n!
		mint nkl = FactorialInv[n.x - k.x];  // (n-k)!
		mint kl = FactorialInv[k.x];         // k!
		mint nkk = (nkl.x * kl.x);
		return nl * nkk;
	}

	// 順列 nPk を計算
	mint nPk(mint n, mint k) {
		if (n < k) {
			return 0;
		}
		if (!pre_calc.factorial) {
			factorial_precalc();
			pre_calc.factorial = true;
		}
		return Factorial[n.x] / Factorial[n.x - k.x];
	}

	// 包除原理 \sum_{i=0}^k (-1)^{k-i} kCi i^n
	mint inclusion_exclusion(const mint n, const mint k) {
		if (!pre_calc.combination) {
			nCk_precalc();
			pre_calc.combination = true;
		}
		mint ans = 0;
		for (int i = 0; i <= k.x; i++) {
			ans += mint(0).pow(-1, k - i) * nCk(k, i) * mint(0).pow(i, n);
		}
		return ans;
	}

	// スターリング数 S(n, k) を計算
	mint stirling(const mint n, const mint k) {
		mint res = inclusion_exclusion(n, k);
		res /= Factorial[k.x];
		return res;
	}

	// ベル数 B(n, k) を計算
	mint bell(const mint n, const mint k) {
		if (!pre_calc.bell) {
			bell_precalc();
			pre_calc.bell = true;
		}
		mint ans = 0;
		for (int i = 0; i <= k.x; i++) {
			ans += mint(0).pow(i, n) / Factorial[i] * Bell[k.x - i];
		}
		return ans;
	}

	// 分割数 P(n, k) を計算
	// n - k < 0 場合は別途，場合分けを行う
	mint partition(const mint n, const mint k) {
		if (n.x < 0) {
			return 0;
		}
		if (!pre_calc.partition) {
			partition_precalc();
			pre_calc.partition = true;
		}
		return Partition[n.x][k.x];
	}
};
