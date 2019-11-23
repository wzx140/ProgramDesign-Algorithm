#include <iostream>
#include <queue>
#include <algorithm>

using std::endl;
using std::cin;
using std::cout;
using std::queue;
using std::max;

// 8：潘多拉星球的悬浮公寓

// x为当前行数，y为当前列数
// 面标号展开图(每面都是左上角为(0,0)，向下和向右为正方向)
//4	
//0 1 2 3
//5
bool visit[20][20][6];
// 立方体大小
int k = 0;
// 房子数
int sum = 0;
// 最大房子面积
int maxSpace = 0;

// 0->上 1->下 2->左 3->右
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
// 面的上下左右 以 面的坐标轴向下和向右为正方向时为准
int next[6][4] = { {4,5,3,1},{4,5,0,2},{4,5,1,3},{4,5,2,0},{2,0,3,1},{2,0,3,1} };

// i溢出当前面的方向
// 有点绕，需要空间想象能力
void nextPos(int &x, int &y, int s, int i) {
	switch (s) {
	case 0:
		if (i == 0) {
			x = k - 1;
		} else if (i == 1) {
			x = k - 1;
		} else if (i == 2) {
			y = k - 1;
		} else if (i == 3) {
			y = 0;
		}
		break;
	case 1:
		if (i == 0) {
			x = k - 1 - y;
			y = k - 1;
		} else if (i == 1) {
			x = k - 1 - y;
			y = k - 1;
		} else if (i == 2) {
			y = k - 1;
		} else if (i == 3) {
			y = 0;
		}
		break;
	case 2:
		if (i == 0) {
			x = 0;
			y = k - 1 - y;
		} else if (i == 1) {
			x = 0;
			y = k - 1 - y;
		} else if (i == 2) {
			y = k - 1;
		} else if (i == 3) {
			y = 0;
		}
		break;
	case 3:
		if (i == 0) {
			x = y;
			y = 0;
		} else if (i == 1) {
			x = y;
			y = 0;
		} else if (i == 2) {
			y = k - 1;
		} else if (i == 3) {
			y = 0;
		}
		break;
	case 4:
		if (i == 0) {
			x = 0;
			y = k - 1 - y;
		} else if (i == 1) {
			x = 0;
		} else if (i == 2) {
			y = x;
			x = 0;
		} else if (i == 3) {
			y = k - 1 - x;
			x = 0;
		}
		break;
	case 5:
		if (i == 0) {
			x = k - 1;
			y = k - 1 - y;
		} else if (i == 1) {
			x = k - 1;
		} else if (i == 2) {
			y = x;
			x = k - 1;
		} else if (i == 3) {
			y = k - 1 - x;
			x = k - 1;
		}
		break;
	default:
		break;
	}
}

int dfs(int x, int y, int s) {
	visit[x][y][s] = true;

	int area = 1;
	for (int i = 0; i < 4; i++) {
		int nextX = x + dir[i][0];
		int nextY = y + dir[i][1];
		int nextS = s;
		if (nextX == -1 || nextY == -1 || nextX == k || nextY == k) {
			nextPos(nextX, nextY, nextS, i);
			nextS = next[nextS][i];
		}

		if (!visit[nextX][nextY][nextS]) {
			area += dfs(nextX, nextY, nextS);
		}
	}

	return area;
}

int main(int argc, char *argv[]) {
	int t = 0;
	cin >> t;
	while (t--) {
		sum = 0;
		maxSpace = 0;
		cin >> k;
		// 接收表面情况
		for (int s = 0; s < 6; s++) {
			for (int i = 0; i < k; i++) {
				for (int j = 0; j < k; j++) {
					int space = 0;
					cin >> space;
					visit[i][j][s] = space == 1;
				}
			}
		}

		for (int s = 0; s < 6; s++) {
			for (int i = 0; i < k; i++) {
				for (int j = 0; j < k; j++) {
					if (!visit[i][j][s]) {
						maxSpace = max(maxSpace, dfs(i, j, s));
						sum++;
					}
				}
			}
		}
		cout << sum << ' ' << maxSpace << endl;
	}
	return 0;
}