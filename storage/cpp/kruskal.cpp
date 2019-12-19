// クラスカル法

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

	vector<kr_edge> es; //辺の集合
	vector<kr_edge> minst; // 最小全域木に用いられる辺の集合
	int V, E; // 頂点数と辺数

	Kruskal(int v) {
		V = v;
	}

	void add(int v, int u, int cost){
		kr_edge e = {v, u, cost};
		es.push_back(e);
	}

	int kruskal() {
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

	void show(){
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
