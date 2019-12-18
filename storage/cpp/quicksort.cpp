// クイックソートですsort関数で十分です

#define N 10
int a[N];
void quicksort(int a[], int first, int last){
	int i, j, x;
	x = a[(first + last)/2];
	i = first;
	j = last;
	while(1){
		while(a[i] < x) i++;
		while(x < a[j]) j--;
		if(i >= j) break;
		swap(a[i], a[j]);
		i++;
		j--;
	}
	if(first < i - 1) quicksort(a, first, i - 1);
	if(j + 1 < last) quicksort(a, j + 1, last);
}
