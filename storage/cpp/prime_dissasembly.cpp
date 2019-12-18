// 素因数分解

map<int,int> prime;
map<int,int>::iterator it;
void factorize(int x){
	int d, q;
	bool ck = true;
	while(x >= 4 && x%2 == 0){
		x /= 2;
		if(prime.find(2) == prime.end()) prime[2] = 1;
		else prime[2]++;
	}
	d = 3; q = x/d;
	while(q >= d){
		if(x%d == 0){
			x = q;
			if(prime.find(d) == prime.end()) prime[d] = 1;
			else prime[d]++;
		}
		else if(ck){
			d += 2;
			ck = false;
		}
		else{
			d += 4;
			ck = true;
		}
		q = x/d;
	}
	if(prime.find(x) == prime.end()) prime[x] = 1;
	else prime[x]++;
}
