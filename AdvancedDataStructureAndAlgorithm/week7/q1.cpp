#include <iostream>
#include <algorithm>

using std::endl;
using std::cin;
using std::cout;
using std::swap;

// 1. 开关问题
// 可以联想到非齐次线性方程组的求解，即Ax=b
// Ax=(a1^T,...,ai^T,...,an^T)^T x=b
// 因为每个开关的开合状态由本身和关联的开关决定，所以ai^T表示A的行向量，表示第i个开关与1~n个开关的关联性
// x表示是否按下1~n的开关

// 增广矩阵
int aug[35][36];

// 增广矩阵中只有0,1
int gauss(int n) {
	// 上一个主元行的位置
	int prePivot = -1;
	for (int j = 0; j < n; j++) {
		// 找到主元所在行
		int pivotRow = prePivot + 1;
		while (pivotRow < n) {
			if (aug[pivotRow][j] == 1) {
				break;
			} else {
				pivotRow++;
			}
		};

		// 该列没有主元
		if (pivotRow >= n) {
			continue;
		}

		if (pivotRow != prePivot + 1) {
			// 初等行变换，将主元行换到对应位置
			for (int col = 0; col < n + 1; col++) {
				swap(aug[pivotRow][col], aug[prePivot + 1][col]);
			}
		}
		pivotRow = prePivot + 1;

		// 初等行变换，将主元所在的列的其他元素变成0，这应该使用异或运算
		for (int row = pivotRow + 1; row < n; row++) {
			if (aug[row][j] == 1) {
				for (int col = j; col < n + 1; col++) {
					aug[row][col] ^= aug[pivotRow][col];
				}
			}
		}
		prePivot = pivotRow;
	}

	// ra!=rab
	for (int i = prePivot + 1; i < n; i++) {
		if (aug[i][n] != 0) {
			return -1;
		}
	}

	return 1 << (n - (prePivot + 1));
}

int main(int argc, char *argv[]) {
	int k = 0, n = 0, x = 0, y = 0;
	int start[35], end[35];
	cin >> k;
	while (k--) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				aug[i][j] = 0;
			}
		}

		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> start[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> end[i];
		}
		while (cin >> x >> y) {
			if (x == 0 && y == 0) {
				break;
			}
			aug[y - 1][x - 1] = 1;
		}
		for (int i = 0; i < n; i++) {
			// 开关i受本身影响
			aug[i][i] = 1;
			// 增广矩阵
			aug[i][n] = start[i] ^ end[i];
		}

		int res = gauss(n);
		if (res == -1) {
			cout << "Oh,it's impossible~!!" << endl;
		} else {
			cout << res << endl;
		}
	}
	return 0;
}