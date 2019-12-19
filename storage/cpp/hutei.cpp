// 不定方程式を解く

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
