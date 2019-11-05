#include <iostream>
#include <queue>
#include <bitset>
#include <vector>

using std::endl;
using std::cin;
using std::cout;
using std::queue;
using std::bitset;
using std::vector;

// 2：迷宫问题

// 迷宫
int maze;

struct State {
	short x = 0;		// 当前位置
	short y = 0;
	int father = -1;	// 父结点
	int board;			// 当前已走过的状态
};

// 状态数组
State states[1 << 25];
// 状态是否走过
bitset<1 << 25> aClose;

// 某点是否走过
bool getPoint(int board, int i, int j) {
	return !((board & (1 << i * 5 + j)) == 0);
}

// test
//void print(int board) {
//	for (int i = 0; i < 5; i++) {
//		for (int j = 0; j < 5; j++) {
//			bool point = getPoint(board, i, j);
//			if (point) {
//				cout << 1 << ' ';
//			} else {
//				cout << 0 << ' ';
//			}
//		}
//		cout << endl;
//	}
//}

int nextState(int board, int i, int j, int op) {
	switch (op) {
	case 0:
		// 上移
		if (j > 0 && !getPoint(board, i, j - 1)) {
			return board + (1 << i * 5 + j - 1);
		} else {
			return -1;
		}
		break;

	case 1:
		// 下移
		if (j < 4 && !getPoint(board, i, j + 1)) {
			return board + (1 << i * 5 + j + 1);
		} else {
			return -1;
		}
		break;

	case 2:
		// 左移
		if (i > 0 && !getPoint(board, i - 1, j)) {
			return board + (1 << (i - 1) * 5 + j);
		} else {
			return -1;
		}
		break;

	case 3:
		// 右移
		if (i < 4 && !getPoint(board, i + 1, j)) {
			return board + (1 << (i + 1) * 5 + j);
		} else {
			return -1;
		}
		break;

	default:
		break;
	}
}

int DBFS(int init) {
	queue<int> open;

	states[init].board = init;
	open.push(init);

	while (!open.empty()) {
		int board = open.front();
		open.pop();
		aClose[board] = true;

		if (getPoint(board, 4, 4)) {
			// 走到右下角了
			return board;

		} else {
			int x = states[board].x;
			int y = states[board].y;

			for (int op = 0; op < 4; op++) {
				int res = nextState(board, x, y, op);

				if (res != -1 && !aClose[res]) {
					open.push(res);

					// 更新父指针
					states[res].father = board;
					// 更新坐标
					switch (op) {
					case 0:
						// 上移
						states[res].x = x;
						states[res].y = y - 1;
						break;

					case 1:
						// 下移
						states[res].x = x;
						states[res].y = y + 1;
						break;

					case 2:
						// 左移
						states[res].x = x - 1;
						states[res].y = y;
						break;

					case 3:
						// 右移
						states[res].x = x + 1;
						states[res].y = y;
						break;
					default:
						break;
					}
				}
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
				maze += 1 << i * 5 + j;
			}
		}
	}

	// 返回路径终点状态
	int board = DBFS(maze);

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