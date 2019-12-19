// 特定の文字の配列内の添字

int indexdistance(vector<int> distance_array, char c) {
	return static_cast<int>(std::distance(std::begin(distance_array), std::find(std::begin(distance_array), std::end(distance_array), c)));
}
