// 掃き出し法

#define RANK 20 // 20元連立方程式まで解ける
/*
使用方法
	double a[RANK][RANK+1];
	int i, n;
	a[0][0] = 2; a[0][1] = 3; a[0][2] = 1; a[0][3] = 4;
	a[1][0] = 4; a[1][1] = 1; a[1][2] = -3 ; a[1][3] = -2;
	a[2][0] = -1; a[2][1] = 2; a[2][2] = 2; a[2][3] = 2;
	n = 3;
	hakidashi(a,n);
*/
void hakidashi(double a[][RANK+1], int n) { 
	double piv, t;
	int i, j, k;
	for (k = 0; k < n; k++) {
		piv = a[k][k];
		for (j = k; j < n + 1; j++) {
			a[k][j] = a[k][j]/piv;
		}
		for (i = 0; i < n; i++) {
			if (i != k) {
				t = a[i][k];
				for (j = k; j < n+1; j++) {
					a[i][j] = a[i][j] - t*a[k][j];
				}
			}
		}
	}
}
