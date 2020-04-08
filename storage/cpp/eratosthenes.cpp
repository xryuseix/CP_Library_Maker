// エラトステネスの篩

vector<bool> eratosmake(int n){
	vector<bool> num(n + 1, false);
	for(int i = 0; i < n; i++) num[i] = true;
	// 0と1を消す
	num[0] = num[1] = false;
	// iを残してiの倍数を消していく
	for(int i = 2; i < n; i++){
		if(num[i]){
			for(int j = i + i; j < n; j += i){
				num[j] = false;
			}
		}
	}
	return num;
}
