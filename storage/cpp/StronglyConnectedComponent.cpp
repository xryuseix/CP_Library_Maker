// 強連結成分分解

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
