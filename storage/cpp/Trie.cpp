// Trie木

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
