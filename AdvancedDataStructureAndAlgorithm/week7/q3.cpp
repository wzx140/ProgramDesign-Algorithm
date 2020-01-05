#include <iostream>
#include <algorithm>

using std::endl;
using std::cin;
using std::cout;
using std::swap;
using std::max;

// 3. Training little cats
// 猫有做以下三种指令
// gi：第i个猫拿走一个花生；ei：第i个猫吃掉自己的所有花生；sij：第i和j个猫交换花生
// 给出一连串的指令，每个指令需要重复m次，求出最后每个猫手里的花生数量
// 利用矩阵乘法
// https://amoshyc.github.io/ojsolution-build/poj/p3735.html
// 快速幂 https://zhuanlan.zhihu.com/p/42639682

struct Matrix {
	long long val[116][116];
	int cols;	// 行数
	int rows;	// 列数

	Matrix() {}

	Matrix(int rows, int cols) : rows(rows), cols(cols) {
		zero();
	}

	void zero() {
		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->cols; j++) {
				this->val[i][j] = 0;
			}
		}
	}

	void unit() {
		zero();
		for (int i = 0; i < cols; i++) {
			val[i][i] = 1;
		}
	}

	void resize(int rows, int cols) {
		this->rows = rows;
		this->cols = cols;
	}
};

Matrix mul(const Matrix&a, Matrix &b) {
	Matrix ret(a.rows, b.cols);

	for (int k = 0; k < a.cols; k++) {
		for (int i = 0; i < a.rows; i++) {
			if (a.val[i][k] != 0) {
				for (int j = 0; j < b.cols; j++) {
					ret.val[i][j] += a.val[i][k] * b.val[k][j];
				}
			}
		}
	}
	return ret;
}

Matrix fastPow(const Matrix&a, int k) {
	Matrix ret(a.rows, a.rows), base = a;
	ret.unit();

	while (k) {
		if (k & 1)
			ret = mul(ret, base);
		base = mul(base, base);
		k >>= 1;
	}

	return ret;
}

int main(int argc, char *argv[]) {
	Matrix A, b;
	int n = 0, m = 0, k = 0;
	char order = '\0';
	int index1 = 0, index2 = 0;
	while (cin >> n >> m >> k && n) {
		// 初始化矩阵
		A.resize(n + 1, n + 1);
		A.unit();
		b.resize(n + 1, 1);
		b.zero();
		b.val[n][0] = 1;

		while (k--) {
			cin >> order;
			if (order == 'g') {
				cin >> index1;
				A.val[index1 - 1][n]++;
			} else if (order == 'e') {
				cin >> index1;
				for (int i = 0; i < n + 1; i++) {
					A.val[index1 - 1][i] = 0;
				}

			} else if (order == 's') {
				cin >> index1 >> index2;
				swap(A.val[index1 - 1], A.val[index2 - 1]);
			}
		}
		Matrix result = mul(fastPow(A, m), b);
		for (int i = 0; i < n; i++) {
			cout << result.val[i][0] << ' ';
		}
		cout << endl;
	}
	return 0;
}