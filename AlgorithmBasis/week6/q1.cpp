#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// 1： 棋盘问题
// 深度优先，动归

bool board[8][8];	// 棋盘
bool cols[8];		// 列状态，每列是否放过棋子
int n = 0;			// 棋盘大小
int k = 0;			// 棋子个数
int count = 0;		// 方案数
int chess = 0;		// 已放棋子数

// 从i行开始的递归深搜
// 因为每个棋子在行上不可能重复,所以要储存列的状态，
void DFS(int i) {
	// 找到一种方法
	if (chess == k) {
		count++;
		return;
	}

	if (i >= n) {
		return;
	}

	// 列搜索
	for (int j = 0; j < n; j++) {
		if (!board[i][j] && !cols[j]) {
			cols[j] = true;
			chess++;
			DFS(i + 1);
			// 恢复状态
			cols[j] = false;
			chess--;
		}
	}

	// 下一行
	// 允许出现空行的情形
	DFS(i + 1);
}

int main(int argc, char *argv[]) {

	while ((cin >> n, cin >> k) && n != -1 && k != -1) {
		for (int i = 0; i < n; i++) {
			cols[i] = false;
		}
		count = 0;
		chess = 0;

		// 初始化棋盘
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				char ch;
				cin >> ch;
				board[i][j] = ch == '.';
			}
		}

		DFS(0);
		cout << count << endl;
	}

	return 0;
}