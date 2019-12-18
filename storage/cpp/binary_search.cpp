// 二分探索

//vector vの中のn以下の数で最大のものを返す
int bs(vector<int> v, int x){
	int ok = -1; //これがx以下 
	int ng = v.size(); //x以上 
// 問題によってokとngを入れ替える
	while(abs(ok - ng) > 1){
		int mid = (ok + ng)/2;
		if(v[mid] <= x) ok = mid;
		else ng = mid;
	}
	return ok;
}
