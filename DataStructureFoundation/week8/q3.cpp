#include <iostream>
#include <queue>
#include <algorithm>
#include <limits>

using std::endl;
using std::cin;
using std::cout;
using std::priority_queue;
using std::max;
using std::numeric_limits;

// 3. Finding Nemo
// 使用优先队列+BFS
// https://blog.csdn.net/PKU_ZZY/article/details/52938152
// 左下角的点坐标确定网格，每个网格拥有四条边

// 第三个维度表示格子的四条边 -1->墙 0->空 1->门
// 0->上 1->下 2->左 3->右
int sea[250][250][4];

// 0->上 1->下 2->左 3->右
const int dir[4][2] = { {0,1},{0,-1},{-1,0},{1,0} };

// 走到当前点的最小门数
int minDoors[250][250];

// 边界，由墙的长度决定
int sx = 0;
int sy = 0;

struct State {
	int x;
	int y;
	int doors;
	State(int a, int b, int c) :x(a), y(b), doors(c) {}
	friend bool operator<(State state1, State state2) {
		return state1.doors > state2.doors;
	}
};

int bfs(int f1, int f2) {
	priority_queue<State> open;

	// 起点
	open.push(State(0, 0, 0));
	minDoors[0][0] = 0;

	while (!open.empty()) {
		State state = open.top();
		open.pop();
		// 找到儿子
		if (state.x == f1 && state.y == f2) {
			return state.doors;
		}

		// 继续搜索
		for (int i = 0; i < 4; i++) {

			// 墙
			if (sea[state.x][state.y][i] == -1) {
				continue;
			}

			int nextDoors = state.doors;
			int nextX = state.x;
			int nextY = state.y;
			nextX += dir[i][0];
			nextY += dir[i][1];
			nextDoors += sea[state.x][state.y][i];

			// 超出边界
			if (nextX < 0 || nextY < 0 || nextX > sx + 1 || nextY > sy + 1) {
				continue;
			}

			// 已走过或者不是最优路线
			if (nextDoors >= minDoors[nextX][nextY]) {
				continue;
			}

			minDoors[nextX][nextY] = nextDoors;
			open.push(State(nextX, nextY, nextDoors));
		}
	}

	return -1;
}

int main(int argc, char *argv[]) {
	int m = 0;
	int n = 0;
	int x = 0, y = 0, d = 0, t = 0;
	float f1 = 0, f2 = 0;

	while ((cin >> m >> n) && (m != -1 && n != -1)) {
		sx = 0;
		sy = 0;

		// 初始化
		for (int i = 0; i < 250; i++) {
			for (int j = 0; j < 250; j++) {
				for (int k = 0; k < 4; k++) {
					sea[i][j][k] = 0;
				}
			}
		}
		for (int i = 0; i < 250; i++) {
			for (int j = 0; j < 250; j++) {
				minDoors[i][j] = numeric_limits<int>::max();
			}
		}

		for (int i = 0; i < m; i++) {
			cin >> x >> y >> d >> t;

			if (d == 0) {
				// 平行x
				for (int j = 0; j < t; j++) {
					// 注意重叠的地方都要赋值
					sea[x + j][y - 1][0] = sea[x + j][y][1] = -1;
				}
				sx = max(x + t - 1, sx);
				sy = max(y, sy);
			} else if (d == 1) {
				// 平行y
				for (int j = 0; j < t; j++) {
					sea[x - 1][y + j][3] = sea[x][y + j][2] = -1;
				}
				sx = max(x, sx);
				sy = max(y + t - 1, sy);
			}
		}

		for (int i = 0; i < n; i++) {
			cin >> x >> y >> d;

			sx = max(x, sx);
			sy = max(y, sy);

			if (d == 0) {
				sea[x][y - 1][0] = sea[x][y][1] = 1;
			} else if (d == 1) {
				sea[x - 1][y][3] = sea[x][y][2] = 1;
			}
		}

		cin >> f1 >> f2;
		// 向下取整
		int fx = (int)f1;
		int fy = (int)f2;

		if (fx < 1 || fx > sx || fy < 1 || fy > sy) {
			fx = fy = 0;
		}
		cout << bfs(fx, fy) << endl;
	}

	return 0;
}