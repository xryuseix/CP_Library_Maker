// 幾何ライブラリ

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
