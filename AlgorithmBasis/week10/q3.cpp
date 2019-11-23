#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// 3：简单的整数划分问题
// 比较容易想到递归，但是把所有情况考虑清楚不容易
// https://www.cnblogs.com/huashanqingzhu/p/7295329.html

//// n的正数划分数，子数不能大于m
//int recursive(int n, int m) {
//	if (n == 1) {
//		return 1;
//	} else if (m = 1) {
//		return 1;
//	} else if (m == n) {
//		return 1 + recursive(n, m - 1);
//	} else if (n < m) {
//		return recursive(n, n);
//	} else if (n > m) {
//		// 是否包含数m
//		return recursive(n - m, m) + recursive(n, m - 1);
//	}
//}

int dp[51][51];
// 动态规划
void dynamic() {
	// 根据递归的条件来
	for (int i = 1; i <= 50; i++) {
		dp[i][1] = 1;
		dp[1][i] = 1;
	}

	for (int i = 2; i <= 50; i++) {
		for (int j = 2; j <= 50; j++) {
			if (i == j) {
				dp[i][j] = 1 + dp[i][j - 1];
			} else if (i > j) {
				dp[i][j] = dp[i][j - 1] + dp[i - j][j];
			}else if(i<j){
				dp[i][j] = dp[i][i];
			}
		}
	}
}

int main(int argc, char *argv[]) {
	dynamic();
	int n = 0;
	while (cin >> n) {
		cout << dp[n][n] << endl;
	}
	return 0;
}
