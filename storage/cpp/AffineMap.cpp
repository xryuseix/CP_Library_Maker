// アフィン変換

template <class T>
class AffineMap {
public:
	typedef vector<vector<T>> Matrix;
	Matrix matrix;              // 単位行列から変換する累積行列積
	vector<Matrix> affine_log;  // アフィン変換のログ
	AffineMap() {
		matrix = vector<vector<T>>{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
		affine_log.push_back(matrix);
	}

	// theta 度，反時計回りで回転
	Matrix AffineMatrix_Rotation(T theta) {
		double theta_rad = theta * M_PI / 180;
		return Matrix{
			{static_cast<T>(cos(theta_rad)), static_cast<T>(-sin(theta_rad)),
			0},
			{static_cast<T>(sin(theta_rad)), static_cast<T>(cos(theta_rad)), 0},
			{0, 0, 1}};
	};
	// X==p で反転
	Matrix AffineMatrix_ReverseX(T p) {
		return Matrix{{-1, 0, 2 * p}, {0, 1, 0}, {0, 0, 1}};
	};
	// Y==p で反転
	Matrix AffineMatrix_ReverseY(T p) {
		return Matrix{{1, 0, 0}, {0, -1, 2 * p}, {0, 0, 1}};
	};
	// +x, +y へ平行移動
	Matrix AffineMatrix_Translation(T x, T y) {
		return Matrix{{1, 0, x}, {0, 1, y}, {0, 0, 1}};
	};

	// 回転
	Matrix rotation(T theta) {
		matrix = matrix_product_33_33(AffineMatrix_Rotation(theta), matrix);
		affine_log.push_back(matrix);
		return matrix;
	}
	// X==p で反転
	Matrix reverseX(T p) {
		matrix = matrix_product_33_33(AffineMatrix_ReverseX(p), matrix);
		affine_log.push_back(matrix);
		return matrix;
	}
	// Y==p で反転
	Matrix reverseY(T p) {
		matrix = matrix_product_33_33(AffineMatrix_ReverseY(p), matrix);
		affine_log.push_back(matrix);
		return matrix;
	}
	// +x, +y へ平行移動
	Matrix translation(T x, T y, Matrix coord = Matrix(0)) {
		if (coord == Matrix(0)) {
			coord = matrix;
		}
		matrix = matrix_product_33_33(AffineMatrix_Translation(x, y), matrix);
		affine_log.push_back(matrix);
		return matrix;
	}

	// 3*3 * 3*1 の行列積
	Matrix matrix_product_33_31(Matrix a, Matrix b) {
		// a が 3*3, b が 3*1 の行列か確認
		assert((int)a.size() == 3 && (int)a[0].size() == 3 &&
			(int)a[1].size() == 3 && (int)a[2].size() == 3);
		assert((int)b.size() == 3 && (int)b[0].size() == 1 &&
			(int)b[1].size() == 1 && (int)b[2].size() == 1);
		return Matrix{
			{a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0]},
			{a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0]},
			{a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0]}};
	}
	Matrix matrix_product_33_33(Matrix a, Matrix b) {
		// a が 3*3, b が 3*1 の行列か確認
		assert((int)a.size() == 3 && (int)a[0].size() == 3 &&
			(int)a[1].size() == 3 && (int)a[2].size() == 3);
		assert((int)b.size() == 3 && (int)b[0].size() == 3 &&
			(int)b[1].size() == 3 && (int)b[2].size() == 3);
		Matrix matrix_tmp(3, vector<T>(3, 0));
		rep(i, 3) {
			rep(j, 3) {
				rep(k, 3) { matrix_tmp[i][j] += a[i][k] * b[k][j]; }
			}
		}
		return matrix_tmp;
	}
};
