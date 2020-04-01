// ローリングハッシュ(文字列探索)

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
