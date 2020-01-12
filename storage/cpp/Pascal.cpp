// 組み合わせ・PascalでnCkを求める

bool useinit = false;
int combMax = 4000;
vector<vector<ll> > comb(combMax + 2, vector<ll> (combMax + 2));
void init(){
	comb[0][0] = 1;
	for(int i = 0; i <= combMax; i++){
		for(int j = 0; j <= i; j++){
			comb[i + 1][j] += comb[i][j];
			comb[i + 1][j + 1] += comb[i][j];
		}
	}
}
int Pascal(int n,int k){
	if(!useinit){
		init();
		useinit = true;
	}
	return comb[n][k];
}
