ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a;}
template <class BidirectionalIterator>
bool generic_next_permutation(BidirectionalIterator first, BidirectionalIterator last) {
	// 要素が０又は１の場合終了
	if (first == last) return false;
	BidirectionalIterator second = first;
	++second;
	if (second == last) return false;
	BidirectionalIterator i = last;
	--i;   // itを最後尾にセット
	while (true) {
		BidirectionalIterator prev_i = i;
		if (*(--i) < *prev_i) {
			BidirectionalIterator j = last;
			while (!(*i < *--j));
			swap(*i, *j);
			reverse(prev_i, last);
			return true;
		}
		if (i == first) {
			reverse(first, last);
			return false;
		}
	}
}
// gcdも呼ぶ！！！
ll lcm(ll a, ll b) { return a / gcd(a,   b) * b;}
// gcdも呼ぶ！！！
// lcmも呼ぶ！！！
int nlcm(vector<int> numbers) {
	int l;
	l = numbers[0];
	for (int i = 1; i < numbers.size(); i++) {
		l = lcm(l, numbers[i]);
	}
	return l;
}
class UnionFind {
public:
	// 親の番号を格納する。親だった場合は-(その集合のサイズ)
	vector<int> Parent;

	UnionFind(int N) {
		Parent = vector<int>(N, -1);
	}

	// Aがどのグループに属しているか調べる
	int root(int A) {
		if (Parent[A] < 0) return A;
		return Parent[A] = root(Parent[A]);
	}

	// 自分のいるグループの頂点数を調べる
	int size(int A) {
		return -Parent[root(A)];//親をとってきたい]
	}

	// AとBをくっ付ける
	bool connect(int A, int B) {
		// AとBを直接つなぐのではなく、root(A)にroot(B)をくっつける
		A = root(A);
		B = root(B);
		if (A == B) {
			//すでにくっついてるからくっ付けない
			return false;
		}

		// 大きい方(A)に小さいほう(B)をくっ付ける
		// 大小が逆だったらひっくり返す
		if (size(A) < size(B)) {
			swap(A, B);
		}

		// Aのサイズを更新する
		Parent[A] += Parent[B];
		// Bの親をAに変更する
		Parent[B] = A;

		return true;
	}
};
vector<bool> eratosmake(int n,vector<bool> num){
	// 整数を列挙して素数の候補とする
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
#define QsoetN 10
int a[QsoetN];
void quicksort(int a[], int first, int last){
	int i, j, x;
	x = a[(first + last)/2];
	i = first;
	j = last;
	while(1){
		while(a[i] < x) i++;
		while(x < a[j]) j--;
		if(i >= j) break;
		swap(a[i], a[j]);
		i++;
		j--;
	}
	if(first < i - 1) quicksort(a, first, i - 1);
	if(j + 1 < last) quicksort(a, j + 1, last);
}
// gcdも呼ぶ！！！
ll ngcd(vector<ll> a){
	ll d;
	d = a[0];
	for(int i = 1; i < a.size() && d != 1; i++) d = gcd(a[i], d);
	return d;
}
// 三次方程式 ax^3+bx^2+cx+d=0を解く 
double ans1=0, ans2=0, ans3=0;
void cardano(double a, double b, double c, double d){
	double p, q, t, a3, b3, x1, x2, x3;
	b /= (3*a); c /= a; d /= a;
	p = b*b - c/3;
	q = (b*(c - 2*b*b) - d)/2;
	a = q*q - p*p*p;
	if(a == 0){
		q = cbrt(q); x1 = 2*q - b; x2 = -q - b;
		cout << "x=" << x1 << ", " << x2 << "(重解)" << endl;
		ans1 = x1; ans2 = x2;
	}else if(a > 0){
		if(q > 0) a3 = cbrt(q + sqrt(a));
		else   a3 = cbrt(q - sqrt(a));
		b3 = p/a3;
		x1 = a3 + b3 - b; x2 = -0.5 + (a3 + b3) - b;
		x3 = fabs(a3 - b3)*sqrt(3.0)/2;
		cout << "x=" << x1 << "; " << x2 << "+- " << x3 << "i" << endl;
		ans1 = x1; ans2 = x2; ans3 = x3;
	}else{
		a = sqrt(p); t = acos(q/(p*a)); a *= 2;
		x1 = a*cos(t/3) - b;
		x2 = a*cos((t+2*M_PI)/3) - b;
		x3 = a*cos((t+4*M_PI)/3) - b;
		cout << "x=" << x1 << ", " << x2 << ", " << x3 << endl;
		ans1 = x1; ans2 = x2; ans3 = x3;
	}
}
map<ll, ll> prime;
void factorize(int n) {
	for(int i = 2; i * i <= n; i++) {
		while(n % i == 0) {
			prime[i]++;
			n /= i;
		}
	}
	if(n != 1) {
		prime[n] = 1;
	}
}
bool isPrime(int x){
	int i;
	if(x < 2)return 0;
	else if(x == 2) return 1;
	if(x%2 == 0) return 0;
	for(i = 3; i*i <= x; i += 2) if(x%i == 0) return 0;
	return 1;
}
#define RANK 20 // 20元連立方程式まで解ける
/*
使用方法
	double a[RANK][RANK+1];
	int i, n;
	a[0][0] = 2; a[0][1] = 3; a[0][2] = 1; a[0][3] = 4;
	a[1][0] = 4; a[1][1] = 1; a[1][2] = -3 ; a[1][3] = -2;
	a[2][0] = -1; a[2][1] = 2; a[2][2] = 2; a[2][3] = 2;
	n = 3;
	hakidashi(a,n);
*/
void hakidashi(double a[][RANK+1], int n) { 
	double piv, t;
	int i, j, k;
	for (k = 0; k < n; k++) {
		piv = a[k][k];
		for (j = k; j < n + 1; j++) {
			a[k][j] = a[k][j]/piv;
		}
		for (i = 0; i < n; i++) {
			if (i != k) {
				t = a[i][k];
				for (j = k; j < n+1; j++) {
					a[i][j] = a[i][j] - t*a[k][j];
				}
			}
		}
	}
}
/*
	aX^2+bX+c=0の解を求める
	出力はこんな感じ
	if(x1 == DBL_MIN)cout<<"解なし"<<endl;
	else if(x1==DBL_MAX)cout<<"不定"<<endl;
	else if(!i)cout<<x1<<" , "<<x2<<endl;
	else cout<<x1<<" +- "<<x2<<"i"<<endl;
*/
double x1, x2;
bool i = false;
void quadeq(double a, double b, double c){
	double d, x;
	if(a != 0){
		b /= a; c /= a;
		if(c != 0){
			b /= 2;
			d = b*b - c;
			if(d > 0){
				if(b > 0) x = -b - sqrt(d);
				else x = -b + sqrt(d);
				x1 = x; x2 = c/x;
			}else if(d < 0){
				x1 = -b; x2 = sqrt(-d); i = true;
			}else{
				x1 = x2 = -b;
			}
		}else{
			x1 = -b; x2 = 0;
		}
	}else if(b != 0){
		x1 = x2 = -c/b;
	}
	else if(c != 0) x1 = x2 = DBL_MIN;
	else x1 = x2 = DBL_MAX;
}
// vector vの中のn以下の数で最大のものを返す
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
vector<int> enum_div(int n){
	vector<int> ret;
	for(int i = 1 ; i*i <= n ; ++i){
		if(n%i == 0){
			ret.push_back(i);
			if(i != 1 && i*i != n){
				ret.push_back(n/i);
			}
		}
	}
	return ret;
}
// xのn乗%modを計算
ll mod_pow(ll x,ll n,ll mod){
	ll res = 1;
	while(n > 0){
		if(n & 1) res = res*x%mod;
		x = x*x%mod;
		n >>= 1;
	}
	return res;
}
int stringcount(string s, char c) {
	return count(s.cbegin(), s.cend(), c);
}
map<int,int> zip;
int compress(vector<int> x) {
	int unzip[x.size()];
	sort(x.begin(), x.end());
	x.erase(unique(x.begin(),x.end()),x.end());
	for(int i = 0; i < x.size(); i++){
		zip[x[i]] = i;
		unzip[i] = x[i];
	}
	return x.size();
}
// {0, 1, ..., n-1} の部分集合の全探索
void bitsearch(int n) {
	for(int bit = 0; bit < (1<<n); ++bit){
		/* bit で表される集合の処理を書く */
		
		/* きちんとできていることを確認してみる */
		// bit の表す集合を求める
		vector<int> S;
		for(int i = 0; i < n; ++i) {
			if(bit & (1<<i) ){ // i が bit に入るかどうか
				S.push_back(i);
			}
		}
		
		// bit の表す集合の出力
		cout << bit << ": {";
		for(int  i = 0; i < S.size(); ++i) {
			cout << S[i] << " ";
		}
		cout << "}" << endl;
	}
}
bool useinit = false;
int combMax = 4000;
vector<vector<ll> > comb(combMax + 2, vector<ll> (combMax + 2));
void init(void) {
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
const int mod = 1000000007;
struct mint {
	ll x;
	mint(ll x=0):x(x%mod){}
	mint& operator+=(const mint a) {
		if ((x += a.x) >= mod) x -= mod;
		return *this;
	}
	mint& operator-=(const mint a) {
		if ((x += mod-a.x) >= mod) x -= mod;
		return *this;
	}
	mint& operator*=(const mint a) {
		(x *= a.x) %= mod;
		return *this;
	}
	mint operator+(const mint a) const {
		mint res(*this);
		return res+=a;
	}
	mint operator-(const mint a) const {
		mint res(*this);
		return res-=a;
	}
	mint operator*(const mint a) const {
		mint res(*this);
		return res*=a;
	}
};
int  knapsack(int n, int W, vi w, vi v){
	vvi dp(n + 1, vi (W + 1, 0));
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= W; j++) {
			if(j - w[i] >= 0) {
				chmax(dp[i][j], dp[i - 1][j - w[i]] + v[i]);
			}
			chmax(dp[i][j], dp[i - 1][j]);
		}
	}
	return dp[n][W];
}
string lcs(string s, string t) {
	vvi dp(s.size() + 1, vi(t.size() + 1));
	
	for(int i = 0; i < s.size(); i++) {//LCS
		for(int j = 0; j < t.size(); j++) {
			if(s[i] == t[j]) {
				dp[i + 1][j + 1] = dp[i][j] + 1;
			}
			else{
				dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
			}
		}
	}
	// 復元
	string ans = "";
	int i = (int)s.size(), j = (int)t.size();
	while (i > 0 && j > 0){
		// (i-1, j) -> (i, j) と更新されていた場合
		if (dp[i][j] == dp[i-1][j]) {
			--i; // DP の遷移を遡る
		}
		// (i, j-1) -> (i, j) と更新されていた場合
		else if (dp[i][j] == dp[i][j-1]) {
			--j; // DP の遷移を遡る
		}
		// (i-1, j-1) -> (i, j) と更新されていた場合
		else {
			ans = s[i-1] + ans;
			--i, --j; // DP の遷移を遡る
		}
	}
	return ans;
}
priority_queue<int, vector<int>, greater<int> > queue;
// 頂点fromから頂点toへのコストcostの辺
struct bf_edge {
	int from;
	int to;
	int cost;
};

class Bellman_Ford{
public:
	vector<bf_edge> es; // 辺
	vector<int> d; // d[i]...頂点sから頂点iまでの最短距離
	int V, E; // Vは頂点数、Eは辺数

	Bellman_Ford(int v, int e) {
		V = v;
		E = e;
		d = vector<int>(v);
	}

	void add(int from, int to, int cost) {
		bf_edge ed = {from, to, cost};
		es.push_back(ed);
	}

	// s番目の頂点から各頂点への最短距離を求める
	void shortest_path(int s) {
		for(int i = 0; i < V; i++) {
			d[i] = INF;
		}
		d[s] = 0;
		while(true) {
			bool update = false;
			for(int i = 0; i < E; i++) {
				bf_edge e = es[i];
				if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
					d[e.to] = d[e.from] + e.cost;
					update = true;
				}
			}
			if (!update) break;
		}
	}
	// trueなら負の閉路が存在する
	bool is_nagative_loop(void) {
		for(int i = 0; i < V; i++) {
			d[i] = 0;
		}
		for (int i = 0; i < 3*V; i++) {
			for(int j = 0; j < E; j++) {
				bf_edge e = es[j];
				if(d[e.to] > d[e.from] + e.cost) {
					d[e.to] = d[e.from] + e.cost;

					// 3n回目にも更新があるなら負の閉路が存在する
					if(i == V - 1)return true;
				}
			}
		}
		return false;
	}
};
vvi G(1000); // グラフ(リスト)

// トポロジカルソート
void rec(int v, vector<bool> &seen, vector<int> &order) {
	seen[v] = true;
	cout<<v<<endl;
	for (int i= 0; i < G[v].size(); i++) {
		int next = G[v][i];
		if (seen[next]) continue; // 既に訪問済みなら探索しない
		rec(next, seen, order);
	}
	order.push_back(v);
}

vector<int> topo(int N) { // Nはノード数
	// 探索
	vector<bool> seen(N, 0); // 初期状態では全ノードが未訪問
	vector<int> order; // トポロジカルソート順
	for (int v = 0; v < N; ++v) {
		if (seen[v]) continue; // 既に訪問済みなら探索しない
		rec(v, seen, order);
	}
	reverse(order.begin(), order.end());
	return order;
}
class DIJKSTRA {
public:
	int V;

	struct dk_edge {
		int to;
		int cost;
	};

	typedef pair<int, int> PI; //firstは最短距離、secondは頂点の番号
	vector<vector<dk_edge> >G;
	vector<int> d; //これ答え。d[i]:=V[i]までの最短距離
	vector<int> prev; //経路復元

	DIJKSTRA(int size) {
		V = size;
		G = vector<vector<dk_edge> >(V);
		prev = vector<int> (V, -1);
	}

	void add(int from, int to, int cost) {
		dk_edge e = {to, cost};
		G[from].push_back(e);
	}

	void dijkstra(int s) {
		//greater<P>を指定することでfirstが小さい順に取り出せるようにする
		priority_queue<PI, vector<PI>, greater<PI> > que;
		d = vector<int> (V, INF);
		d[s] = 0;
		que.push(PI(0, s));

		while(!que.empty()) {
			PI p = que.top();
			que.pop();
			int v = p.second;
			if(d[v] < p.first) continue;
			for(int i = 0; i < G[v].size(); i++) {
				dk_edge e = G[v][i];
				if(d[e.to] > d[v] + e.cost) {
					d[e.to] = d[v] + e.cost;
					prev[e.to] = v;
					que.push(PI(d[e.to], e.to));
				}
			}
		}
	}
	vector<int> get_path(int t) {
		vector<int> path;
		for(;t != -1; t = prev[t]) {
			//tがsになるまでprev[t]をたどっていく
			path.push_back(t);
		}
		//このままだとt->sの順になっているので逆順にする
		reverse(path.begin(),path.end());
		return path;
	}
	void show(void) {
		for(int i = 0; i < d.size()-1; i ++) {
			cout << d[i] << " ";
		}
		cout << d[d.size()-1] << endl;
	}
};
class WAR_FLY {
public:
	vvi d; // 辺の数
	int V; // 頂点の数
	
	WAR_FLY(int n) {
		V = n;
		d = vector<vector<int> > (n,vector<int>(n));
		for(int i = 0; i < V; i++) {
			for(int j = 0; j < V; j++) {
				if(i == j) {
					d[i][j] = 0;
				}
				else {
					d[i][j] = INF;
				}
			}
		}
	}

	void warshall_floyd(void) {
		for(int k = 0; k < V; k++) {
			for(int i = 0; i < V; i++) {
				for(int j = 0; j < V; j++) {
					d[i][j] = min((ll)d[i][j], (ll)d[i][k] + (ll)d[k][j]);
				}
			}
		}
	}

	void add(int from, int to, int cost) {
		d[from][to] = cost;
	}

	bool is_negative_loop(void) {
		for(int i = 0; i < V; i++) {
			if(d[i][i] < 0) return true;
		}
		return false;
	}

	void show(void) {
		for(int i = 0; i < V; i++) {
			for(int j = 0; j < V; j++) {
				cout << d[i][j] << " ";
			}
			cout << endl;
		}
	}
};
void intersect(set<int> &Set_A, set<int> &Set_B, set<int> &Set_res) {
	set_intersection(Set_A.begin(), Set_A.end(), Set_B.begin(), Set_B.end(), inserter(Set_res, Set_res.end()));
}
int digsum(int n) {
	int res = 0;
	while(n > 0) {
		res += n%10;
		n /= 10;
	}
	return res;
}
int indexdistance(vector<int> distance_array, char c) {
	return static_cast<int>(std::distance(std::begin(distance_array), std::find(std::begin(distance_array), std::end(distance_array), c)));
}
// (a/b)%P の場合は，(a%P)*modinv(b)%P とする
ll modinv(ll a) {
	ll b = MOD, u = 1, v = 0;
	while (b) {
		ll t = a / b;
		a -= t * b; swap(a, b);
		u -= t * v; swap(u, v);
	}
	u %= MOD;
	if (u < 0) u += MOD;
	return u;
}
class BoyerMoore {
	public:
	string text;
	string pattern;
	int n;
	int m;
	map<char, int> lambda;
	BoyerMoore(string text_, string pattern_) : 
		text(text_), pattern(pattern_), n(text_.size()), m(pattern_.size()) {
		compute_lambda();
	};
	void compute_lambda(void) {
		for(int j = 1; j <= m; j++) {
			lambda[pattern.at(j - 1)] = j;
		}
	};
	int get_lambda(const char& c) {
		if (lambda.find(c) != lambda.end()) {
			return lambda[c];
		} else {
			return 0;
		}
	};
	bool match(void) {
		int s = 0;
		while(s <= n - m) {
			int j = m;
			while(j > 0 && pattern.at(j - 1) == text.at(s + j - 1)) {
				j--;
			}
			if(j == 0) {
				return true;//ここを消すとsが文字列の位置を示す
				s++;
			} else {
				s += std::max(1, j - get_lambda(text.at(s + j - 1)));
			}
		}
		return false;
	};
};
UnionFind uni(100);
// Union-Findも呼んで！！そして上の書き換えて！！！
struct kr_edge {
	int u; // 辺の片方，fromではないので二回辺を張る必要はない
	int v; // 辺のもう片方
	int cost;

	// コストの大小で順序定義
	bool operator<(const kr_edge& e) const {
		return cost < e.cost;
	}
};
class Kruskal{
	public:

	bool comp(const kr_edge& e1, const kr_edge& e2) { // sort関数の比較関数
		return e1.cost < e2.cost;
	}

	vector<kr_edge> es; // 辺の集合
	vector<kr_edge> minst; // 最小全域木に用いられる辺の集合
	int V, E; // 頂点数と辺数

	Kruskal(int v) {
		V = v;
	}

	void add(int v, int u, int cost){
		kr_edge e = {v, u, cost};
		es.push_back(e);
	}

	int kruskal(void) {
		sort(es.begin(), es.end()); // kr_edge.costが小さい順にソートされる
		UnionFind uni(V); //union-findの初期化
		int res = 0;
		for(int i = 0; i < es.size(); i++) {
			kr_edge e = es[i];
			if(uni.root(e.u) != uni.root(e.v)) {
				uni.connect(e.u, e.v);
				res += e.cost;
				minst.push_back(e);
			}
		}
		return res;
	}

	void show(void) {
		vvi v(V, vi(V, -1));
		for(int i = 0; i < minst.size(); i++) {
			v[minst[i].u][minst[i].v] = minst[i].cost;
			v[minst[i].v][minst[i].u] = minst[i].cost;
		}
		for(int i = 0; i < V; i++) {
			for(int j = 0; j < V; j++) {
				if(v[i][j] == -1) {
					printf("  __ ");
				} else {
					printf("%4d ", v[i][j]);
				}
			}
			cout << endl;
		}
	}
};
void hutei(int a, int b, int c, bool minus) {
	vector<int> arr;

	// A / B = div...mod
	int A = max(a, b);
	int B = min(a, b);
	int div, mod;

	while(1) {
		div = A/B;
		mod = A%B;
		arr.push_back(div);

		A = B;
		B = mod;

		if(mod == 1) {
			break;
		}
	}

	vector<vector<int> > calc(2, vector<int> (arr.size() + 1, INF));

	for(int i = 0; i < arr.size() - 1; i++) {
		calc[0][i] = -arr[i];
	}
	calc[1][arr.size() - 1] = -arr[arr.size() - 1];
	calc[1][arr.size()] = 1;

	for(int i = arr.size()-2; i >= 0; i--) {
		calc[1][i] = calc[0][i]*calc[1][i + 1] + calc[1][i + 2];
	}

	int x = calc[1][0]*c;
	int y = calc[1][1]*c;

	if(minus) {
		y *= -1;
	}
	cout << a << "(" << b << "m + " << x << ")";
	if(minus) {
		cout << " - ";
	} else {
		cout << " + ";
	}
	cout << b << "(" << a << "m + " << y << ")" << " = " << c << endl;
}
class Monoid {
public:
	// 単位元
	int unit;
	
	Monoid(void) {
		// 単位元
		unit = INF;
	}

	// 演算関数
	int calc(int a, int b) {
		return min(a, b); 
	}
};

class SegmentTree {
public:
	// セグメント木の葉の要素数
	int n;

	// セグメント木
	vector<int> tree;

	// モノイド
	Monoid mono;

	SegmentTree(vector<int> &v) {
		n = 1 << (int)ceil(log2(v.size()));
		tree = vector<int>(n << 1);
		for(int i = 0; i < v.size(); i++) {
			update(i, v[i]);
		}
		for(int i = v.size(); i < n; i++) {
			update(i, mono.unit);
		}
	}

	// k番目の値(0-indexed)をxに変更
	void update(int k, int x) {
		k += n;
		tree[k] = x;
		for(k = k >> 1; k > 0; k >>= 1){
			tree[k] = mono.calc(tree[k << 1 | 0], tree[k << 1 | 1]);
		}
	}

	// [l, r)の最小値(0-indexed)を求める．
	int query(int l, int r) {
		int res = mono.unit;
		l += n;
		r += n;
		while(l < r) {
			if(l & 1) {
				res = mono.calc(res, tree[l++]);
			}
			if(r & 1) {
				res = mono.calc(res, tree[--r]);
			}
			l >>= 1;
			r >>= 1;
		}
		return res;
	}
	int operator[](int k) {
		// st[i]で添字iの要素の値を返す
		if(k - n >= 0 || k < 0) {
			return -INF;
		}
		return tree[tree.size()-n+k];
	}

	void show(void) {
		int ret = 2;
		for(int i = 1; i < 2*n; i++) {
			cout << tree[i] << " ";
			if(i == ret - 1) {
				cout << endl;
				ret <<= 1;
			}
		}
		cout << endl;
	}
};
int lis(vector<int>& v) {
	vi dp(1, v[0]);
	for(int i = 1; i < v.size(); i++) {
		if(v[i] > dp[dp.size() - 1]) {
			dp.push_back(v[i]);
		} else {
			int pos = distance(lower_bound(dp.begin(), dp.end(), v[i]), dp.begin());
			dp[pos] = v[i];
		}
	}
	return (int)dp.size();
}
int conlis(vector<int>& v) {
	vi dp(v.size() + 1, 0);
	int ans = 0;
	for(int i = 0; i < v.size(); i++) {
		dp[v[i]] = dp[v[i] - 1] + 1;
		ans = max(ans, dp[v[i]]);
	}
	return ans;
}
// x,y に ax + by = gcd(a, b) を満たす値が格納される
ll extgcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll d = extgcd(b, a%b, y, x);
	y -= a/b * x;
	return d;
}
class StronglyConnectedComponent {
public:
	int V;          // 頂点数
	int SubGraph;   // 強連結成分の数
	vvi Graph;      // グラフの隣接リスト表現
	vvi revGraph;   // 辺の向きを逆にしたグラフ
	vvi SmallGraph; // 強連結成分分解によって縮めたグラフ
	vi dfsline;     // 帰りがけ順の並び
	vi compo;       // cmp[i]で頂点iの属するグループ
	vb used;        // すでに調べたか

	StronglyConnectedComponent(int v) {
		V = v;
		Graph = vvi(v);
		revGraph = vvi(v);
		used = vb(v);
		compo = vi(v);
	}

	int operator[](int k) {
		// scc[i]でi番目の頂点のグループ番号を返す
		return compo[k];
	}

	void add_edge(int from, int to) {
		Graph[from].push_back(to);
		revGraph[to].push_back(from);
	}

	void dfs(int v) {
		used[v] = true;
		for(int i = 0; i < Graph[v].size(); i++) {
			if(!used[Graph[v][i]]) dfs(Graph[v][i]);
		}
		dfsline.push_back(v);
	}

	void revdfs(int v, int k) {
		used[v] = true;
		compo[v] = k;
		for(int i = 0; i < revGraph[v].size(); i++) {
			if(!used[revGraph[v][i]]) revdfs(revGraph[v][i], k);
		}
	}

	int scc(void) {
		used = vb((int)used.size(), false);
		dfsline.clear();
		for(int v = 0; v < V; v++) {
			if(!used[v]) dfs(v);
		}
		used = vb(used.size(), false);
		SubGraph = 0;
		for(int i = dfsline.size() - 1; i >= 0; i--) {
			if(!used[dfsline[i]]) revdfs(dfsline[i], SubGraph++);
		}
		for(int i = 0; i < compo.size(); i++) {
			compo[i] = SubGraph - compo[i] - 1;
		}
		return SubGraph;
	}

	void build(void) {
		// 縮めたグラフを構築する
		SmallGraph = vvi(SubGraph);
		for (int i = 0; i < Graph.size(); i++) {
			for(int j = 0; j < Graph[i].size(); j++) {
				int to = Graph[i][j];
				int s = compo[i], t = compo[to];
				if (s != t){
					SmallGraph[s].push_back(t);
				}
			}
		}
		for(int i = 0; i < SmallGraph.size(); i++) {
			// 被った辺を削除
			SmallGraph[i].erase(unique(SmallGraph[i].begin(), SmallGraph[i].end()), SmallGraph[i].end());
		}
	}

	void show_set_to_edge(void) {
		for(int i = 0; i < SmallGraph.size(); i++) {
			cout << "集合" << i << "から出ている辺 : ";
			for(int j = 0; j < SmallGraph[i].size(); j++) {
				cout << SmallGraph[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}

	void show_group_of_node(void) {
		for(int i = 0; i < V; i++) {
			cout << "頂点" << i << "の属するグループ : " << compo[i] << endl;
		}
		cout << endl;
	}

	void show_node_in_group(void) {
		vvi group(SubGraph);
		for(int i = 0; i < compo.size(); i++) {
			group[compo[i]].push_back(i);
		}
		for(int i = 0; i < SmallGraph.size(); i++) {
			cout << "グループ" << i << "に属する頂点 : ";
			for(int j = 0; j < group[i].size(); j++) {
				cout << group[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}
};
class Compress{
public:
	int before_W, before_H, N;
	vi before_X1, before_X2, before_Y1, before_Y2;
	int after_W, after_H;
	vi after_X1, after_X2, after_Y1, after_Y2;
	
	// (x1,y1) -> (x2, y2) の直線上のマスが塗られているとする
	// 点の場合は (x1,y1) == (x2, y2) とする
	// 四角形の場合は直線の集合とする
	Compress(int max_h, int max_w, int n, vi x1, vi x2, vi y1, vi y2) {
		before_H = max_h;
		before_W = max_w;
		N = n;
		before_X1 = x1;
		before_X2 = x2;
		before_Y1 = y1;
		before_Y2 = y2;
		after_X1 = vi(max_w);
		after_X2 = vi(max_w);
		after_Y1 = vi(max_h);
		after_Y2 = vi(max_h);
	}

	void compress(void) {
		after_W = exec_compress(before_X1, before_X2, after_X1, after_X2, before_W, "width");
		after_H = exec_compress(before_Y1, before_Y2, after_Y1, after_Y2, before_H, "height");
	}

	void before_show(void) {
		vvc v(before_H, vc(before_W, '_'));
		cout << "H = " << before_H << ", W = " << before_W << endl;
		for(int i = 0; i < N; i++) {
			for(int y = before_Y1[i]; y <= before_Y2[i]; y++) {
				for(int x = before_X1[i]; x <= before_X2[i]; x++) {
					v[y][x] = '#';
				}
			}
		}
		rep(i, before_H){
			rep(j, before_W){
				cout << v[i][j];
			}
			cout<<endl;
		}
		cout << endl;
	}

	void after_show(void) {
		vvc v(after_H, vc(after_W, '_'));
		cout << "H = " << after_H << ", W = " << after_W << endl;
		for(int i = 0; i < N; i++) {
			for(int y = after_Y1[i]; y <= after_Y2[i]; y++) {
				for(int x = after_X1[i]; x <= after_X2[i]; x++) {
					v[y][x] = '#';
				}
			}
		}
		rep(i, after_H){
			rep(j, after_W){
				cout << v[i][j];
			}
			cout<<endl;
		}
		cout << endl;
	}

private:
	int exec_compress(vi &z1, vi &z2, vi &aft_z1, vi &aft_z2, int max_len, string mode) {
		vector<int> zs;
		for(int i = 0; i < N; i++) {
			if(z1[i] > z2[i]) swap(z1[i], z2[i]);

			zs.push_back(z1[i]);
			zs.push_back(z2[i]);

			if(mode == "width") {
				if(z2[i] + 1 <= max_len) zs.push_back(z2[i] + 1);
			} else if(mode == "height") {
				if(0 < z1[i] - 1) zs.push_back(z1[i] - 1);
			}
		}
		zs.push_back(1);
		zs.push_back(max_len);

		sort(zs.begin(), zs.end());
		zs.erase(unique(zs.begin(), zs.end()), zs.end());

		for(int i = 0; i < N; i++) {
			aft_z1[i] = find(zs.begin(), zs.end(), z1[i]) - zs.begin() + 1;
			aft_z2[i] = find(zs.begin(), zs.end(), z2[i]) - zs.begin() + 1;
		}
		return zs.size();
	}
};
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
/* ==== 幾何ライブラリ ==== */
/* 点 */
struct Point {
	double x;
	double y;
	Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

	// === 四則演算の定義 ===
	friend inline Point operator + (const Point &p, const Point &q) {return Point(p.x + q.x, p.y + q.y);}
	friend inline Point operator - (const Point &p, const Point &q) {return Point(p.x - q.x, p.y - q.y);}
	friend inline Point operator * (const Point &p, const double a) {return Point(p.x * a, p.y * a);}
	friend inline Point operator * (const double a, const Point &p) {return Point(a * p.x, a * p.y);}
	friend inline Point operator * (const Point &p, const Point &q) {return Point(p.x * q.x - p.y * q.y, p.x * q.y + p.y * q.x);}
	friend inline Point operator / (const Point &p, const double a) {return Point(p.x / a, p.y / a);}

	// === その他の演算 ===
	// 反時計回りに90度回転
	friend Point rot90(const Point &p) {return Point(-p.y, p.x);}

	// 直線b,cからみて，aがどちら側にいるか判定
	// 1: bを上cを下とした時にaが右側にある, -1: aが左側にある, 0: aは直線bc上
	friend int simple_ccw(const Point &a, const Point &b, const Point &c) {
		if(OuterProduct(b-a, c-a) > EPS) return 1;
		if(OuterProduct(b-a, c-a) < -EPS) return -1;
		return 0;
	}

	// 内積
	friend inline double InnerProduct(const Point &p, const Point &q) {return p.x * q.x + p.y * q.y;}
	// 外積
	friend inline double OuterProduct(const Point &p, const Point &q) {return p.x * q.y - p.y * q.x;}

	// 二次元のノーム(ユークリッド距離)を計算
	friend inline double norm2(const Point &p) {return sqrt(InnerProduct(p, p));}

	// === 出力 ===
	friend ostream& operator << (ostream &s, const Point &p) {return s << '(' << p.x << ", " << p.y << ')';}
};

/* 線 */
struct Line {
	vector<Point> line;

	Line(void) {}
	// 線分の時
	Line(Point a, Point b = Point(0.0, 0.0)) {
		// x座標が小さい方->y座標が小さい順にしておく
		if(a.x > b.x) {
			swap(a, b);
		} else if(a.x == b.x && a.y > b.y) {
			swap(a, b);
		}
		line.push_back(a);
		line.push_back(b);
	}
	// 多角形などの時
	Line(vector<Point> L) {
		/*
		// 基本はソートするとバグるのでしないこと
		sort(L.begin(), L.end(), [](Point const& lhs, Point const& rhs) {
			if(lhs.x != rhs.x) return lhs.x < rhs.x;
			else if(lhs.y != rhs.y) return lhs.y < rhs.y;
			return true;
		});
		*/
		line = L;
	}

	// === 出力 ===
	friend ostream& operator << (ostream &s, const Line &l) {
		s << '{';
		rep(i, l.line.size()) {
			if(i) {
				s << ", ";
			}
			s << l.line[i];
		}
		s << '}';
		return s;
	}
};

/* 単位変換 */
double torad(int deg) {return (double)(deg) * MATHPI / 180;}
double todeg(double ang) {return ang * 180 / MATHPI;}

/* 直線や多角形の交点 */
Line crosspoint(const Line &L, const Line &M) {
	Line res;
	Line l = L;
	Line m = M;
	l.line.push_back(l.line[0]);
	m.line.push_back(m.line[0]);
	for(int i = 0; i < l.line.size() - 1; i++) {
		for(int j = 0; j < m.line.size() - 1; j++) {
			double d = OuterProduct(m.line[j + 1] - m.line[j], l.line[i + 1] - l.line[i]);
			if(abs(d) < EPS) continue;
			res.line.push_back(l.line[i] + (l.line[i + 1] - l.line[i]) * OuterProduct(m.line[j + 1] - m.line[j], m.line[j + 1] - l.line[i]) / d);
		}
	}
	return res;
}

/* 外心 */
Point gaisin(const Point a, const Point b, const Point c) {
	// 外心は三角形の二つの辺の垂直二等分線の交点
	Line ab( (a + b)/2, (a + b)/2 + rot90(a - b) );
	Line bc( (b + c)/2, (b + c)/2 + rot90(b - c) );
	return crosspoint(ab, bc).line[0];
}

/* 最小包含円 */
double SmallestEnclosingCircle(const vector<Point> &V) {
	int N = V.size();
	if(N <= 1) return 0;

	// 最小包含円の中心の候補
	vector<Point> CenterCandidate;
	for(int i = 0; i < N; i++) {
		for(int j = i + 1; j < N; j++) {
			// 最小包含円の円弧上に点が２つしかないの時
			CenterCandidate.push_back( (V[i] + V[j]) / 2 );
			for(int k = j + 1; k < N; k++) {
				if(!simple_ccw(V[i], V[j], V[k])) {
					// 三点が一直線上にある
					continue;
				}
				// 三点の外心が円の中心
				Point r = gaisin(V[i], V[j], V[k]);
				CenterCandidate.push_back(r);
			}
		}
	}

	double res = INF;
	rep(c, CenterCandidate.size()) {
		double tmp = 0.0;
		rep(v, V.size()) {
			// 中心からの距離が最大の点との距離が，包含円の半径になる
			chmax(tmp, norm2(V[v] - CenterCandidate[c]));
		}
		// 候補の包含円の中で，半径が最小の包含円が最小包含円になる．
		chmin(res, tmp);
	}
	return res;
}
