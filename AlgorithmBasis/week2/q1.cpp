#include <iostream>

using namespace std;

// 编程题＃1： 画家问题

int guess(int wall[][17], int paint[][17], int size) {
	int n = size;

	// 根据wall第1行和paint数组, 计算paint其他行的值
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n + 1; j++) {

			paint[i + 1][j] = (wall[i][j] + paint[i][j] + paint[i][j - 1] + paint[i][j + 1] + paint[i - 1][j]) % 2;

		}
	}

	// 判断最后一行
	for (int i = 1; i < n + 1; i++) {
		if ((paint[n][i] + paint[n][i - 1] + paint[n][i + 1] + paint[n - 1][i]) % 2 != wall[n][i]) {
			return n * n + 1;
		}
	}

	// 计算粉刷次数
	int count = 0;
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			if (paint[i][j] == 1) {
				count++;
			}
		}
	}

	return count;
}

//枚举第一行的所有情况  
int enumerate(int wall[][17], int paint[][17], int size) {
	int n = size;
	int minCount = n * n + 1;

	while (paint[1][n + 1] < 1) {
		int count = guess(wall, paint, size);
		if (count < minCount) {
			minCount = count;
		}
		paint[1][1]++;
		int c = 1;
		while (paint[1][c] > 1) {
			paint[1][c] = 0;
			c++;
			paint[1][c]++;
		}
	}
	return minCount;
}

int main(int argc, char *argv[]) {

	// 初始化
	int wall[16][17] = { 0 };
	int paint[16][17] = { 0 };

	// 读取cases数
	int cases = 0;
	cin >> cases;

	for (int i = 0; i < cases; i++) {
		// 读取case的size
		int n = 0;
		cin >> n;

		// 初始化墙和粉刷 
		for (int r = 0; r < 16; r++) {
			for (int c = 0; c < 17; c++) {
				wall[r][c] = 0;
				paint[r][c] = 0;
			}
		}

		// 读入wall
		for (int r = 1; r < n + 1; r++) {
			for (int c = 1; c < n + 1; c++) {
				char ch;
				cin >> ch;
				wall[r][c] = ch == 'y' ? 0 : 1;
			}
		}

		int minCount = enumerate(wall, paint, n);
		if (minCount > n*n) {
			cout << "inf" << endl;
		} else {
			cout << minCount << endl;
		}
	}
	return 0;
}