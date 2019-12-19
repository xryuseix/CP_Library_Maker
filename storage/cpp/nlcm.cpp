// n個の値の最小公倍数

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
