// 二次元座標圧縮(バグってる)

class Compress {
public:
	int before_W, before_H, N;
	vi before_X1, before_X2, before_Y1, before_Y2;
	int after_W, after_H;
	vi after_X1, after_X2, after_Y1, after_Y2;
	
	// (x1,y1) -> (x2, y2) の直線上のマスが塗られているとする
	// 点の場合は (x1,y1) == (x2, y2) とする
	// 四角形の場合は直線の集合とする
	// (バグってるよこれ)
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
