// setのintersect

void intersect(set<int> &Set_A, set<int> &Set_B, set<int> &Set_res) {
	set_intersection(Set_A.begin(), Set_A.end(), Set_B.begin(), Set_B.end(), inserter(Set_res, Set_res.end()));
}
