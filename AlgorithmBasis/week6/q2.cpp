#include <iostream>

using std::cout;
using std::cin;
using std::endl;

// 2：A Knight's Journey
// 简单的翻译一下，骑士在矩形棋盘上走，一步只能直走两格再拐一个弯(垂直方向走一格)
// 在A1起点下，棋盘每个点都只经过一次的方案

// A1 坐标为(0,0) 右与下为正方向
bool square[26][26];	// 棋盘

int p = 0;	// x,行数，数字表示
int q = 0;	// y,列数，字母表示
int maxStep = 0;	// 总步数
bool flag = false;	//	已经找到方案

struct Node {
	int x = 0;
	int y = 0;
}route[26];

// 方向：0~7
// ！题目要求字典序最小，所以这里要按序排列
void move(int& x, int& y, int direction) {
	switch (direction) {
	case 0:
		x -= 2;
		y -= 1;
		break;
	case 1:
		x -= 2;
		y += 1;
		break;
	case 2:
		x -= 1;
		y -= 2;
		break;
	case 3:
		x -= 1;
		y += 2;
		break;
	case 4:
		x += 1;
		y -= 2;
		break;
	case 5:
		x += 1;
		y += 2;
		break;
	case 6:
		x += 2;
		y -= 1;
		break;
	case 7:
		x += 2;
		y += 1;
		break;
	default:
		break;
	}
}

void DFS(int x, int y, int step) {

	if (flag) {
		// 在找到字典序最小的方案后快速结束其他正在递归中的函数
		// 避免不必要的递归
		return;
	}

	square[x][y] = true;
	route[step].x = x;
	route[step].y = y;
	step++;

	if (step == maxStep) {
		flag = true;
		return;
	}

	for (int i = 0; i < 8; i++) {
		int nextX = x;
		int nextY = y;
		move(nextX, nextY, i);

		if (!square[nextX][nextY] &&
			nextX >= 0 && nextX < q &&
			nextY >= 0 && nextY < p) {

			DFS(nextX, nextY, step);
		}
	}

	// 恢复状态
	square[x][y] = false;
}

int main(int argc, char *argv[]) {
	int n = 0;
	cin >> n;

	for (int index = 1; index <= n; index++) {
		cin >> p >> q;
		maxStep = p * q;
		flag = false;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				square[i][j] = false;
			}
		}

		DFS(0, 0, 0);

		cout << "Scenario #" << index << ":" << endl;
		if (flag) {
			for (int i = 0; i < maxStep; i++) {
				char ch = route[i].x + 'A';
				cout << ch << route[i].y + 1;
			}
			cout << endl << endl;
		} else {
			cout << "impossible" << endl << endl;
		}
	}

	return 0;
}