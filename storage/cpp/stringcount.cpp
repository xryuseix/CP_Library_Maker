// 文字列中の特定の文字の個数をカウント

int stringcount(string s, char c) {
	return count(s.cbegin(), s.cend(), c);
}
