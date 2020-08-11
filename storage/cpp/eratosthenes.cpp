// エラトステネスの篩

class Sieve{
	int N;
	void eratosmake(void) {
		// iを残してiの倍数を消していく
		for(int i = 2; i < N; i++) {
			if(nums[i] == 1) {
				for(int j = i + i; j < N; j += i){
					nums[j] = i;
				}
			}
		}
	}

public:
	vector<int> nums;
	Sieve(int n):N(n){
		nums = vi(n+1, 1);
		eratosmake();
	}
	bool isPrime(int n) {
		return nums[n] == 1;
	}
	int minPrimeFactor(int n) {
		return nums[n];
	}
};
