// BoyerMoore法(文字列探索アルゴリズム)

// Quote from https://www.yasuhisay.info/entry/20091215/1260835159

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
	void compute_lambda() {
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
	bool match() {
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
