ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a;}
// gcdも呼ぶ！！！
ll lcm(ll a, ll b) { return a / gcd(a,   b) * b;}
// gcdも呼ぶ！！！
// lcmも呼ぶ！！！
ll nlcm(vector<ll> numbers) {
	ll l = numbers[0];
	for (int i = 1; i < numbers.size(); i++) {
		l = lcm(l, numbers[i]);
	}
	return l;
}
class UnionFind {
public:
	// 親の番号を格納．親だった場合は-(その集合のサイズ)
	vector<int> Parent;
	// 重さの差を格納
	vector<ll> diffWeight;

	UnionFind(const int N) {
		Parent = vector<int>(N, -1);
		diffWeight = vector<ll>(N, 0);
	}

	// Aがどのグループに属しているか調べる
	int root(const int A) {
		if (Parent[A] < 0) return A;
		int Root = root(Parent[A]);
		diffWeight[A] += diffWeight[Parent[A]];
		return Parent[A] = Root;
	}

	// 自分のいるグループの頂点数を調べる
	int size(const int A) {
		return -Parent[root(A)];
	}

	// 自分の重さを調べる
	ll weight(const int A) {
		root(A); // 経路圧縮
		return diffWeight[A];
	}

	// 重さの差を計算する
	ll diff(const int A, const int B) {
		return weight(B) - weight(A);
	}

	// AとBをくっ付ける
	bool connect(int A, int B, ll W = 0) {
		// Wをrootとの重み差分に変更
		W += weight(A);
		W -= weight(B);

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
			W = -W;
		}

		// Aのサイズを更新する
		Parent[A] += Parent[B];
		// Bの親をAに変更する
		Parent[B] = A;

		// AはBの親であることが確定しているのでBにWの重みを充てる
		diffWeight[B] = W;

		return true;
	}
};
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
void factorize(ll n) {
	for(ll i = 2; i * i <= n; i++) {
		while(n % i == 0) {
			prime[i]++;
			n /= i;
		}
	}
	if(n != 1) {
		prime[n] = 1;
	}
}
bool isPrime(ll x){
	if(x < 2)return 0;
	else if(x == 2) return 1;
	if(x%2 == 0) return 0;
	for(ll i = 3; i*i <= x; i += 2) if(x%i == 0) return 0;
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
int bs(vector<ll> &v, ll x){
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
vector<ll> enum_div(ll n) {
	vector<ll> ret;
	for(ll i = 1 ; i*i <= n ; ++i){
		if(n%i == 0) {
			ret.push_back(i);
			if(i != 1 && i*i != n){
				ret.push_back(n/i);
			}
		}
	}
	return ret;
}
// xのn乗%modを計算
ll mod_pow(ll x, ll n, ll mod = MOD) {
	ll res = 1;
	while(n > 0) {
		if(n & 1) res = res*x%mod;
		x = x*x%mod;
		n >>= 1;
	}
	return res;
}
int stringcount(string s, char c) {
	return count(s.cbegin(), s.cend(), c);
}
map<ll, ll> zip;
int compress(vector<ll> x) {
	int unzip[x.size()];
	sort(x.begin(), x.end());
	x.erase(unique(x.begin(),x.end()),x.end());
	for(int i = 0; i < x.size(); i++){
		zip[x[i]] = i;
		unzip[i] = x[i];
	}
	return x.size();
}
struct mint {
	ll x;
	mint(ll _x = 0) : x((_x % MOD + MOD) % MOD) {}

	/* 初期化子 */
	mint operator+() const { return mint(x); }
	mint operator-() const { return mint(-x); }

	/* 代入演算子 */
	mint& operator+=(const mint a) {
		if ((x += a.x) >= MOD) x -= MOD;
		return *this;
	}
	mint& operator-=(const mint a) {
		if ((x += MOD - a.x) >= MOD) x -= MOD;
		return *this;
	}
	mint& operator*=(const mint a) {
		(x *= a.x) %= MOD;
		return *this;
	}
	mint& operator/=(const mint a) {
		x *= modinv(a).x;
		x %= MOD;
		return (*this);
	}
	mint& operator%=(const mint a) {
		x %= a.x;
		return (*this);
	}
	mint& operator++() {
		++x;
		if (x >= MOD) x -= MOD;
		return *this;
	}
	mint& operator--() {
		if (!x) x += MOD;
		--x;
		return *this;
	}
	mint& operator&=(const mint a) {
		x &= a.x;
		return (*this);
	}
	mint& operator|=(const mint a) {
		x |= a.x;
		return (*this);
	}
	mint& operator^=(const mint a) {
		x ^= a.x;
		return (*this);
	}
	mint& operator<<=(const mint a) {
		x *= pow(2, a).x;
		return (*this);
	}
	mint& operator>>=(const mint a) {
		x /= pow(2, a).x;
		return (*this);
	}

	/* 算術演算子 */
	mint operator+(const mint a) const {
		mint res(*this);
		return res += a;
	}
	mint operator-(const mint a) const {
		mint res(*this);
		return res -= a;
	}
	mint operator*(const mint a) const {
		mint res(*this);
		return res *= a;
	}
	mint operator/(const mint a) const {
		mint res(*this);
		return res /= a;
	}
	mint operator%(const mint a) const {
		mint res(*this);
		return res %= a;
	}
	mint operator&(const mint a) const {
		mint res(*this);
		return res &= a;
	}
	mint operator|(const mint a) const {
		mint res(*this);
		return res |= a;
	}
	mint operator^(const mint a) const {
		mint res(*this);
		return res ^= a;
	}
	mint operator<<(const mint a) const {
		mint res(*this);
		return res <<= a;
	}
	mint operator>>(const mint a) const {
		mint res(*this);
		return res >>= a;
	}

	/* 条件演算子 */
	bool operator==(const mint a) const noexcept { return x == a.x; }
	bool operator!=(const mint a) const noexcept { return x != a.x; }
	bool operator<(const mint a) const noexcept { return x < a.x; }
	bool operator>(const mint a) const noexcept { return x > a.x; }
	bool operator<=(const mint a) const noexcept { return x <= a.x; }
	bool operator>=(const mint a) const noexcept { return x >= a.x; }

	/* ストリーム挿入演算子 */
	friend istream& operator>>(istream& is, mint& m) {
		is >> m.x;
		m.x = (m.x % MOD + MOD) % MOD;
		return is;
	}
	friend ostream& operator<<(ostream& os, const mint& m) {
		os << m.x;
		return os;
	}

	/* その他の関数 */
	mint modinv(mint a) { return pow(a, MOD - 2); }
	mint pow(mint x, mint n) {
		mint res = 1;
		while (n.x > 0) {
			if ((n % 2).x) res *= x;
			x *= x;
			n.x /= 2;
		}
		return res;
	}
};
int knapsack(int n, int W, vi w, vi v) {
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
	// trueなら負の閉路が存在する
	bool shortest_path(int s) {
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
		ll cost;
	};

	typedef pair<ll, int> PI;  // firstは最短距離、secondは頂点の番号
	vector<vector<dk_edge> > G;
	vector<ll> d;      //これ答え。d[i]:=V[i]までの最短距離
	vector<int> prev;  //経路復元

	DIJKSTRA(int size) {
		V = size;
		G = vector<vector<dk_edge> >(V);
		prev = vector<int>(V, -1);
	}

	void add(int from, int to, ll cost) {
		dk_edge e = {to, cost};
		G[from].push_back(e);
	}

	void dijkstra(int s) {
		// greater<P>を指定することでfirstが小さい順に取り出せるようにする
		priority_queue<PI, vector<PI>, greater<PI> > que;
		d = vector<ll>(V, LLINF);
		d[s] = 0;
		que.push(PI(0, s));

		while (!que.empty()) {
			PI p = que.top();
			que.pop();
			int v = p.second;
			if (d[v] < p.first) continue;
			for (int i = 0; i < G[v].size(); i++) {
				dk_edge e = G[v][i];
				if (d[e.to] > d[v] + e.cost) {
					d[e.to] = d[v] + e.cost;
					prev[e.to] = v;
					que.push(PI(d[e.to], e.to));
				}
			}
		}
	}
	vector<int> get_path(int t) {
		vector<int> path;
		for (; t != -1; t = prev[t]) {
			// tがsになるまでprev[t]をたどっていく
			path.push_back(t);
		}
		//このままだとt->sの順になっているので逆順にする
		reverse(path.begin(), path.end());
		return path;
	}
	void show(void) {
		for (int i = 0; i < d.size() - 1; i++) {
			cout << d[i] << " ";
		}
		cout << d[d.size() - 1] << endl;
	}
};
template <typename T>
class WAR_FLY {
public:
	vector<vector<T>> d; // 辺の数
	int V; // 頂点の数
	
	WAR_FLY(int n) {
		V = n;
		d = vector<vector<T> > (n,vector<T>(n));
		for(int i = 0; i < V; i++) {
			for(int j = 0; j < V; j++) {
				if(i == j) {
					d[i][j] = 0;
				}
				else {
					d[i][j] = LLINF;
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

	void add(int from, int to, T cost) {
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
template <typename T>
class Sum {
public:
	// 単位元
	T unit;

	Sum(void) {
		// 単位元
		unit = 0;
	}

	// 演算関数
	T calc(T a, T b) { return a + b; }
};

template <typename T>
struct Min {
public:
	// 単位元
	T unit;

	Min(void) {
		// 単位元
		unit = INF;
	}

	// 演算関数
	T calc(T a, T b) { return min(a, b); }
};

template <typename T, class MONOID>
class SegmentTree {
public:
	// セグメント木の葉の要素数
	int n;

	// セグメント木
	vector<T> tree;

	// モノイド
	MONOID mono;

	SegmentTree(vector<T>& v)
		: n(1 << (int)ceil(log2(v.size()))),
		tree(vector<T>(n << 1, mono.unit)) {
		for (int i = 0; i < v.size(); ++i) {
			tree[i + n] = v[i];
		}
		for (int i = n - 1; i > 0; --i) {
			tree[i] = mono.calc(tree[i << 1 | 0], tree[i << 1 | 1]);
		}
	}

	SegmentTree(int _n)
		: n(1 << (int)ceil(log2(_n))), tree(vector<T>(n << 1, mono.unit)) {}

	// k番目の値(0-indexed)をxに変更
	void update(int k, T x) {
		k += n;
		tree[k] = x;
		for (k = k >> 1; k > 0; k >>= 1) {
			tree[k] = mono.calc(tree[k << 1 | 0], tree[k << 1 | 1]);
		}
	}

	// k番目の値(0-indexed)をxを加算
	void add(int k, T x) {
		k += n;
		tree[k] += x;
		for (k = k >> 1; k > 0; k >>= 1) {
			tree[k] = mono.calc(tree[k << 1 | 0], tree[k << 1 | 1]);
		}
	}

	// [l, r)の最小値(0-indexed)を求める．
	T query(int l, int r) {
		T res = mono.unit;
		l += n;
		r += n;
		while (l < r) {
			if (l & 1) {
				res = mono.calc(res, tree[l++]);
			}
			if (r & 1) {
				res = mono.calc(res, tree[--r]);
			}
			l >>= 1;
			r >>= 1;
		}
		return res;
	}

	T operator[](int k) {
		// st[i]で添字iの要素の値を返す
		if (k - n >= 0 || k < 0) {
			return -INF;
		}
		return tree[tree.size() - n + k];
	}

	void show(int elements = 31) {
		int ret = 2;
		for (int i = 1; i < max(2 * n, elements); ++i) {
			if (tree[i] == mono.unit)
				cout << "UNIT ";
			else
				cout << tree[i] << " ";
			if (i == ret - 1) {
				cout << endl;
				ret <<= 1;
			}
		}
		cout << endl;
	}
};
int lis(vi& v) {
	vi dp(1, v[0]);
	for(int i = 1; i < v.size(); i++) {
		if(v[i] > dp[dp.size() - 1]) {
			dp.push_back(v[i]);
		} else {
			int pos = distance(dp.begin(), lower_bound(dp.begin(), dp.end(), v[i]));
			dp[pos] = v[i];
		}
	}
	return dp.size();
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
// 返り値は<gcd(a, b), x, y>
// auto [g, x, y] = extgcd(a, b);のように呼び出す
tuple<ll, ll, ll> extgcd(ll a, ll b) {
	if (b == 0) {
		return {a, 1, 0};
	}
	auto [g, x, y] = extgcd(b, a % b);
	return {g, y, x - a / b * y};
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
class Compress {
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
#define MAX_NCK 201010
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
	if(n < k) return 0;
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

// 直線a-bと点pの距離
long double distance(const Point& p, const Point& a, const Point& b) {
	long double A = b.y - a.y;
	long double B = a.x - b.x;
	long double C = a.y * b.x - b.y * a.x;
	return abs(A * p.x + B * p.y + C) / sqrt(A * A + B * B);
}
// 各座標に格納したい情報を構造体にする
// 今回はX座標,Y座標,深さ(距離)を記述している
struct Corr {
	int x;
	int y;
	int depth;
};
queue<Corr> q;
int bfs(vector<vector<int>> grid) {
	// 既に探索の場所を1，探索していなかったら0を格納する配列
	vector<vector<int>> ispassed(grid.size(), vector<int>(grid[0].size(), false));
	// このような記述をしておくと，この後のfor文が綺麗にかける
	int dx[8] = {1, 0, -1, 0};
	int dy[8] = {0, 1, 0, -1};
	while(!q.empty()) {
		Corr now = q.front();q.pop();
		/*
			今いる座標は(x,y)=(now.x, now.y)で，深さ(距離)はnow.depthである
			ここで，今いる座標がゴール(探索対象)なのか判定する
		*/
		for(int i = 0; i < 4; i++) {
			int nextx = now.x + dx[i];
			int nexty = now.y + dy[i];

			// 次に探索する場所のX座標がはみ出した時
			if(nextx >= grid[0].size()) continue;
			if(nextx < 0) continue;

			// 次に探索する場所のY座標がはみ出した時
			if(nexty >= grid.size()) continue;
			if(nexty < 0) continue;

			// 次に探索する場所が既に探索済みの場合
			if(ispassed[nexty][nextx]) continue;

			ispassed[nexty][nextx] = true;
			Corr next = {nextx, nexty, now.depth+1};
			q.push(next);
		}
	}
}
std::mt19937 mt{ std::random_device{}() };
std::uniform_int_distribution<int> dist(129, INF);
const int BASE = dist(mt);

class RollingHash {
public:
	string str;
	vector<ull> powBase, csumHash;
	const ull ROLMOD = (1LL << 61) - 1;
	const ull MASK30 = (1LL << 30) - 1;
	const ull MASK31 = (1LL << 31) - 1;
	const ull LLMAX = ROLMOD*((1LL << 3) - 1);

	RollingHash(const string s) : str(s) {
		powBase.resize(s.size() + 1);
		csumHash.resize(s.size() + 1);
		powBase[0] = 1;
		for(int i = 0; i < s.size(); i++) {
			powBase[i + 1] = calcMod(multiple(powBase[i], BASE));
		}
	}

	void rollingHash() {
		csumHash[0] = 0;
		for(int i = 0; i < str.size(); ++i) {
			csumHash[i + 1] = calcMod(multiple(csumHash[i], BASE) + str[i]);
		}
	}

	ull getHash(const int begin, const int length) {
		return calcMod(csumHash[begin + length] + LLMAX - multiple(csumHash[begin], powBase[length]));
	}

	string substr(const int begin) {
		return str.substr(begin);
	}

	string substr(const int begin, const int length) {
		if(length < 0) {
			return str.substr(begin, str.size() + length - begin + 1);
		} else {
			return str.substr(begin, length);
		}
	}

private:
	ull calcMod(const ull num) {
		const ull modNum = (num & ROLMOD) + (num >> 61);
		return (modNum >= ROLMOD) ? modNum - ROLMOD : modNum;
	}

	ull multiple(const ull leftNum, const ull rightNum) {
		ull lu = leftNum >> 31;
		ull ld = leftNum & MASK31;
		ull ru = rightNum >> 31;
		ull rd = rightNum & MASK31;
		ull middleBit = ld * ru + lu * rd;
		return ((lu * ru) << 1) + ld * rd + ((middleBit & MASK30) << 31) + (middleBit >> 30);
	}

};
int Q;
cin >> Q;
while(Q--) {
	$1
}
template <typename T>
class Sum {
public:
	// 単位元
	T unit;
	
	Sum(void) {
		// 単位元
		unit = 0;
	}

	// 演算関数
	T calc(T a, T b) {
		return a + b; 
	}
};

template <typename T, class MONOID>
class LazySegmentTree {
public:
	// セグメント木の葉の要素数
	int n;

	// セグメント木
	vector<T> tree, lazy;

	// モノイド
	MONOID mono;

	LazySegmentTree(vector<T> &v) {
		n = 1 << (int)ceil(log2(v.size()));
		tree = vector<T>(n << 1);
		lazy = vector<T>(n << 1, mono.unit);
		for(int i = 0; i < v.size(); ++i) {
			update(i, v[i]);
		}
		for(int i = v.size(); i < n; ++i) {
			update(i, mono.unit);
		}
	}

	// k番目の値(0-indexed)をxに変更
	void update(int k, T x) {
		k += n;
		tree[k] = x;
		for(k = k >> 1; k > 0; k >>= 1){
			tree[k] = mono.calc(tree[k << 1 | 0], tree[k << 1 | 1]);
		}
	}

	// [l, r)の最小値(0-indexed)を求める．
	T query(int l, int r) {
		T res = mono.unit;
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

	// k番目のノードの遅延評価を行う
	void eval(int k, int l, int r) {
		// 遅延評価配列が空でない時，値を伝播する
		if(lazy[k] != mono.unit) {
			tree[k] += lazy[k];
			if(r - l > 1) {
				lazy[k<<1|0] += lazy[k]>>1;
				lazy[k<<1|1] += lazy[k]>>1;
			}

			// 伝播が終わったので自ノードの遅延配列を空にする
			lazy[k] = mono.unit;
		}
	}

	// 区間[l, r)にxを足す(遅延評価)
	void add(int l, int r, ll x) {
		add(l, r, x, 1, 0, n);
	}

	void add(int a, int b, ll x, int k, int l, int r) {
		// k番目のノードに対して遅延評価を行う
		eval(k, l, r);

		// 範囲外なら何もしない
		if(b <= l || r <= a) return;
		
		// 完全に被覆しているならば、遅延配列に値を入れた後に評価
		if(a <= l && r <= b) {
			lazy[k] += (r - l) * x;
			eval(k, l, r);
		} else {
			add(a, b, x, k<<1|0, l, (l + r)>>1);
			add(a, b, x, k<<1|1, (l + r)>>1, r);
			tree[k] = tree[k<<1|0] + tree[k<<1|1];
		}
	}

	// 区間[l, r)の合計を取得する
	ll getRange(int l, int r) {
		return getRange(l, r, 1, 0, n);
	}

	ll getRange(int a, int b, int k, int l, int r) {
		if(b <= l || r <= a) return mono.unit;
		// 関数が呼び出されたら評価！
		eval(k, l, r);
		if(a <= l && r <= b) return tree[k];
		ll vl = getRange(a, b, k<<1|0, l, (l + r)>>1);
		ll vr = getRange(a, b, k<<1|1, (l + r)>>1, r);
		return vl + vr;
	}

	T operator[](int k) {
		// st[i]で添字iの要素の値を返す
		if(k - n >= 0 || k < 0) {
			return -INF;
		}
		return tree[tree.size() - n + k];
	}

	void show(void) {
		showTree();
		showLazy();
	}

	void showTree(void) {
		int ret = 2;
		for(int i = 1; i < 2*n; ++i) {
			if(tree[i] == mono.unit) cout << "UNIT ";
			else cout << tree[i] << " ";
			if(i == ret - 1) {
				cout << endl;
				ret <<= 1;
			}
		}
		cout << endl;
	}

	void showLazy(void) {
		int ret = 2;
		for(int i = 1; i < 2*n; ++i) {
			if(lazy[i] == mono.unit) cout << "UNIT ";
			else cout << lazy[i] << " ";
			if(i == ret - 1) {
				cout << endl;
				ret <<= 1;
			}
		}
		cout << endl;
	}
};
template<class T>
void print_vector(vector<T> &v) {
	rep(i, v.size()) {
		if(!i) cout << v[i];
		else cout << " " << v[i];
	}
	cout << endl;
}
template<class T>
void lambdaSort(vector<T> &v) {
	sort(all(v), [](auto const& l, auto const& r) {
		return l.fi > r.fi; // このbool式が成り立つ時入れ替える
	});
}
class BridgeArticulation {
	int N, num = 0;
	vvi G;
	vi pre, low;
	vb isPassed;

	int culcLow(const int v, const int bef) {
		int nowLow = num;
		low[v] = pre[v] = nowLow;
		for(auto ne : G[v]) {
			if(ne == bef) continue;
			if(ne == 0) {
				low[0] = -1;
			}
			if(pre[ne] == -1) {
				num++;
				culcLow(ne, v);
			}
			chmin(nowLow, low[ne]);
		}
		return low[v] = nowLow;
	}

	void traceGraph(const int v, const int bef) {
		bool is_articulation = false;
		for(auto ne : G[v]) {
			if(ne == bef) continue;
			if(!isPassed[ne]) {
				if(low[ne] >= pre[v] && (bef != -1 || G[v].size() >= 2)) {
					is_articulation = true;
				}
				if(low[ne] == pre[ne]) {
					bridges.emplace_back(min(v, ne), max(v, ne));
				}
				isPassed[ne] = true;
				traceGraph(ne, v);
			}
		}
		if(is_articulation) {
			articulation.push_back(v);
		}
	}

public:
	vpii bridges; // 橋
	vi articulation; // 関節点

	BridgeArticulation(const int _n, const vvi _G) : N(_n), G(_G) {
		pre = vi(N, -1);
		low = vi(N, INF);
		isPassed = vb(N, false);
		isPassed[0] = true;
	}

	void findBridges() {
		culcLow(0, -1);
		traceGraph(0, -1);
		Sort(bridges);
	}

	void show() {
		for(auto p : bridges) {
			cout << p.fi << " " << p.se << endl; 
		}
	}
};
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
template <typename T>
class BIT {
	int N;
	vector<T> tree;

public:
	BIT(vector<T>& v) : N(v.size()), tree(vector<T>(v.size() + 1)) {
		rep(i, v.size()) { add(i, v[i]); }
	}
	BIT(int n) : N(n), tree(vector<T>(n + 1)) {}

	void add(int i, T x = 1) {
		for (++i; i <= N; i += i & -i) {
			tree[i] += x;
		}
	}

	T sum(int l) {  // [0, l)の和
		T x = 0;
		for (; l; l -= l & -l) {
			x += tree[l];
		}
		return x;
	}

	T sum(int l, int r) {  // [l, r)の和
		return sum(r) - sum(l);
	}

	T sum_back(int l) {  // [l, N)の和
		return sum(N) - sum(l);
	}
};
class LCA {
	int n;
	int MAX;
	vvi doubling, v;

	void init() {
		rep(i, n) {
			for(auto j : v[i]) {
				doubling[0][j] = i;
			}
		}
		for(int i = 1; i < MAX; i++) {
			rep(j, n) {
				doubling[i][j] = doubling[i - 1][doubling[i - 1][j]];
			}
		}
		depth[0] = 0;
		dfs(0, -1);
	}

	void dfs(const int crrPos, const int befPos) {
		for(auto i : v[crrPos]) {
			if(i == befPos || depth[i] != -1) {
				continue;
			}
			depth[i] = depth[crrPos] + 1;
			dfs(i, crrPos);
		}
	}

public:
	vi depth;

	// vは0が根のbfs木にする．親->子のように辺を張る．
	LCA(vvi &_v) : v(_v), n(_v.size()) {
		MAX = ceil(log2(n));
		doubling = vvi(MAX, vi(n, 0));
		depth = vi(n, -1);
		init();
	}

	void show(const int height = 0) {
		rep(i, ((!height)?MAX:height)) {
			dump(doubling[i]);
		}
		dump(depth);
	}

	// ダブリングでVのnum個親の祖先を調べる
	int doublingNode(int V, const int num) {
		rep(i, MAX) {
			if((1LL<<i) & num) {
				V = doubling[i][V];
			}
		}
		return V;
	}

	int lca(int A, int B) {
		// Aのが深い位置にあるようにする
		if(depth[A] < depth[B]) {
			swap(A, B);
		}
		A = doublingNode(A, depth[A] - depth[B]);
		if(A == B) {
			return A;
		}

		for (int k = MAX - 1; k >= 0; k--) {
			if (doubling[k][A] != doubling[k][B]) {
				A = doubling[k][A];
				B = doubling[k][B];
			}
		}
		return doubling[0][A];
	}
};
class MaximumFlow {

	int v;

	// 辺を表す構造体(行き先，容量，逆辺のインデックス)
	struct edge {
		int to;
		int cap;
		int rev;
	};

	vector<vector<edge>> G; // グラフの隣接リスト表現
	vector<bool> used; // DFSですでに調べたかのフラグ

	// 増加パスをDFSで探す(今いる頂点, ゴールの頂点, 今の頂点以降のフローの最小値)
	int dfs(int v, int t, int f) {
		if (v == t) return f;
		used[v] = true;
		for (int i = 0; i < G[v].size(); i++) {
			// vから行ける&&cap>0の頂点を全てたどる
			edge& e = G[v][i];
			if (!used[e.to] && e.cap > 0) {
				// 次の頂点(e.to)以降でtまで行けるパスを探索し，その時のフローの最小値をdとする
				int d = dfs(e.to, t, min(f, e.cap));
				if (d > 0) {
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

public:
	MaximumFlow(int _v) : v(_v) {
		used = vector<bool>(v);
		G = vector<vector<edge>>(v);
	}

	// fromからtoへ向かう容景capの辺をグラフに追加する
	void add(int from, int to, int cap) {
		G[from].push_back((edge){to, cap, (int)G[to].size()});
		G[to].push_back((edge){from, 0, (int)G[from].size() - 1});
	}

	// sからtへの最大流を求める
	int maxFlow(int s, int t) {
		int flow = 0;
		while (true) {
			used = vector<bool>(v);
			int f = dfs(s, t, INF);
			if (f == 0) {
				return flow;
			}
			flow += f;
		}
	}
};
class MinCostFlow {

	int V; // 頂点数

	// 辺を表す構造体(行き先，容量，逆辺のインデックス)
	struct edge {
		int to;
		int cap;
		int cost;
		int rev;
	};

	vector<vector<edge>> G; // グラフの隣接リスト表現
	vector<int> h; // ポテンシャル
	vector<int> prevV; // 直前の頂点
	vector<int> prevE; // 直前の辺
	vector<int> dist; // 最短距離
	typedef pair<int, int> PI;

public:
	MinCostFlow(int _v) : V(_v) {
		G = vector<vector<edge>>(V);
		h = vector<int>(V);
		prevV = vector<int>(V);
		prevE = vector<int>(V);
	}

	// fromからtoへ向かう容景capの辺をグラフに追加する
	void add(int from, int to, int cap, int cost) {
		G[from].push_back((edge){to, cap, cost, (int)G[to].size()});
		G[to].push_back((edge){from, 0, -cost, (int)G[from].size() - 1});
	}

	// sからtへの最大流を求める
	int minCostFlow(int s, int t, int f) {
		int res = 0;
		while (f > 0) {
			// ダイクストラ法を用いてhを更新する
			priority_queue<PI, vector<PI>, greater<PI>> que;
			dist = vector<int>(V, INF);
			dist[s] = 0;
			que.push(PI(0, s));
			while(!que.empty()) {
				PI p = que.top();
				que.pop();
				int v = p.second;
				if(dist[v] < p.first) continue;
				for (int i = 0; i < G[v].size(); i++) {
					edge e = G[v][i];
					if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
						dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
						prevV[e.to] = v;
						prevE[e.to] = i;
						que.push(PI(dist[e.to], e.to));
					}
				}
			}
			if(dist[t] == INF) {
				// これ以上流せない
				return -1;
			}
			for(int v = 0; v < V; v++) {
				h[v] += dist[v];
			}
			// s-t問最短路に沿って目一杯流す
			int d = f;
			for(int v = t; v != s; v = prevV[v] ) {
				d = min(d, G[prevV[v]][prevE[v]].cap);
			}
			f -= d;
			res += d*h[t];
			for(int v = t; v != s; v = prevV[v]) {
				edge& e = G[prevV[v]][prevE[v]];
				e.cap -= d;
				G[v][e.rev].cap += d;
			}
		}
		return res;
	}
};
template <int char_size, int base>
class Trie {
public:
	struct Node {
		vector<int> next;    // 子の頂点番号を格納。存在しなければ-1
		vector<int> accept;  // 末端がこの頂点になる文字列(受理状態)のID
		int c;               // 文字，baseからの距離
		int common;          // いくつの文字列がこの頂点を共有しているか
		Node(int c_) : c(c_), common(0) { next = vector<int>(char_size, -1); }
	};
	vector<Node> nodes;  // trie 木本体
	Trie() { nodes.push_back(Node(0)); }

	/*
	単語の検索
	prefix ... 先頭のwordが一致していればいいかどうか
	*/
	bool search(const string word, const bool prefix = false) {
		int node_id = 0;
		for (auto w : word) {
			int c = w - base;
			int next_id = nodes[node_id].next[c];
			// printf("%c %d %d
",w,c,next_id);
			if (next_id == -1) {
				return false;
			}
			node_id = next_id;
		}
		return (prefix) ? true : nodes[node_id].accept.size();
	}

	/*
	単語の挿入
	word_id ... 何番目に追加する単語か
	*/
	void insert(const string &word) {
		int node_id = 0;
		for (auto w : word) {
			int c = w - base;
			int next_id = nodes[node_id].next[c];
			if (next_id == -1) {  // 次の頂点が存在しなければ追加
				next_id = nodes.size();
				nodes.push_back(Node(c));
				nodes[node_id].next[c] = next_id;
			}
			++nodes[node_id].common;
			node_id = next_id;
		}
		++nodes[node_id].common;
		nodes[node_id].accept.push_back(nodes[0].common - 1); // 単語の終端なので、頂点に番号を入れておく
	}

	/*
	prefixの検索
	*/
	bool start_with(const string& prefix) { return search(prefix, true); }

	/*
	挿入した単語数
	*/
	int count() const { return nodes[0].common; }

	/*
	頂点数
	*/
	int size() const { return nodes.size(); }
};
