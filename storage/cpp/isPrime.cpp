// 素数判定（ O(√N) ）

bool isPrime(int x){
	int i;
	if(x < 2)return 0;
	else if(x == 2) return 1;
	if(x%2 == 0) return 0;
	for(i = 3; i*i <= x; i += 2) if(x%i == 0) return 0;
	return 1;
}
