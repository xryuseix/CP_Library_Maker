// next_permutation

template <class BidirectionalIterator>
bool generic_next_permutation(BidirectionalIterator first, BidirectionalIterator last) {
	// 要素が０又は１の場合終了
	if (first == last) return false;
	BidirectionalIterator second = first;
	++second;
	if (second == last) return false;
	BidirectionalIterator i = last;
	--i;   // itを最後尾にセット
	while (true) {
		BidirectionalIterator prev_i = i;
		if (*(--i) < *prev_i) {
			BidirectionalIterator j = last;
			while (!(*i < *--j));
			swap(*i, *j);
			reverse(prev_i, last);
			return true;
		}
		if (i == first) {
			reverse(first, last);
			return false;
		}
	}
}
