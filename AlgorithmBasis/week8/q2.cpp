#include <iostream>
#include <queue>
#include <vector>

using std::endl;
using std::cin;
using std::cout;
using std::queue;
using std::vector;

// 2：迷宫问题

// 左上角为00，x正方向下，y正方向右

struct State {
	short x = 0;		// 当前位置
	short y = 0;
	int father = -1;	// 父结点
};

// 状态数组
State states[1 << 25];
// 迷宫与visit放在一起
int visited = 0;

int dir[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };

// 某点是否走过
bool getPoint(int board, int i, int j) {
	return !((board & (1 << i * 5 + j)) == 0);
}

// test
void print(int board) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			bool point = getPoint(board, i, j);
			if (point) {
				cout << 1 << ' ';
			} else {
				cout << 0 << ' ';
			}
		}
		cout << endl;
	}
	cout << endl;
}

int bfs() {
	queue<int> open;

	// 处于原点
	visited += 1;
	states[visited].x = 0;
	states[visited].y = 0;
	open.push(visited);

	while (!open.empty()) {
		int board = open.front();
		open.pop();

		if (getPoint(board, 4, 4)) {
			// 走到右下角了
			return board;

		} else {
			int x = states[board].x;
			int y = states[board].y;

			for (int op = 0; op < 4; op++) {

				int nextX = x + dir[op][0];
				int nextY = y + dir[op][1];

				// 此点已经被走过
				if (getPoint(visited, nextX, nextY)) {
					continue;
				}

				// 超出范围
				if (nextX < 0 || nextX >= 5 || nextY < 0 || nextY >= 5) {
					continue;
				}

				int nextBoard = board + (1 << nextX * 5 + nextY);

				// 更新父指针
				states[nextBoard].father = board;
				// 更新坐标
				states[nextBoard].x = nextX;
				states[nextBoard].y = nextY;
				open.push(nextBoard);
				// 访问过
				visited += (1 << nextX * 5 + nextY);
			}
		}
	}
}

int main(int argc, char *argv[]) {

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			int value = 0;
			cin >> value;
			if (value == 1) {
				visited += 1 << i * 5 + j;
			}
		}
	}

	// 返回路径终点状态
	int board = bfs();

	// 方向寻找到初始状态
	vector<int> result;
	while (board != -1) {
		result.push_back(board);
		board = states[board].father;
	}
	// 输出
	for (int i = result.size() - 1; i >= 0; i--) {
		int x = states[result[i]].x;
		int y = states[result[i]].y;
		cout << '(' << x << ", " << y << ')' << endl;
	}

	return 0;
}