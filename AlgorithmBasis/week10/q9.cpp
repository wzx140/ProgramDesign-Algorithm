#include <iostream>
#include <queue>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::queue;

struct State {
	int x = 0;
	int y = 0;
	int step = 0;
	short gem = 0;
	State(int a, int b, int c, short d) :x(a), y(b), step(c), gem(d) {}
	State() :x(-1), y(-1), step(0), gem(0) {}
};

// 宝石组合为00000~11111
bool visited[200][200][(1 << 5) - 1];

// 地图
char plot[200][200];

// 传送门
State doors[10];
int numDoors = 0;

// 左上角为(0,0)，下与右为正方向
// x表示行数，y表示列数
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

int r = 0;
int c = 0;
int k = 0;

// 9：拯救公主

int bfs(int startX, int startY) {
	queue<State> open;
	open.push(State(startX, startY, 0, 0));
	visited[startX][startY][0] = true;

	while (!open.empty()) {
		State curr = open.front();
		open.pop();

		for (int i = 0; i < 4; i++) {
			int nextX = curr.x + dir[i][0];
			int nextY = curr.y + dir[i][1];
			int nextStep = curr.step + 1;
			int nextGem = curr.gem;

			// 出界或墙或访问过
			if (nextX < 0 || nextX > r - 1 || nextY < 0 || nextY > c - 1 || plot[nextX][nextY] == '#' || visited[nextX][nextY][nextGem]) {
				continue;
			}

			// 集齐宝石，找到公主
			if (plot[nextX][nextY] == 'E' && nextGem == (1 << k) - 1) {
				return nextStep;
			}

			// 捡到宝石
			if (plot[nextX][nextY] >= '0' && plot[nextX][nextY] <= '4') {
				nextGem |= 1 << plot[nextX][nextY] - '0';
			}

			open.push(State(nextX, nextY, nextStep, nextGem));
			visited[nextX][nextY][nextGem] = true;

			// 传送门
			if (plot[nextX][nextY] == '$') {
				for (int j = 0; j < numDoors; j++) {
					if (doors[j].x == nextX && doors[j].y == nextY) {
						continue;
					} else if (!visited[doors[j].x][doors[j].y][nextGem]) {
						open.push(State(doors[j].x, doors[j].y, nextStep, nextGem));
						visited[doors[j].x][doors[j].y][nextGem] = true;
					}
				}
			}

		}
	}
	return -1;
}

int main(int argc, char *argv[]) {
	int t = 0;
	cin >> t;
	int startX = 0, startY = 0;
	while (t--) {
		numDoors = 0;
		cin >> r >> c >> k;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				cin >> plot[i][j];
				if (plot[i][j] == 'S') {
					startX = i;
					startY = j;
				} else if (plot[i][j] == '$') {
					doors[numDoors++] = State(i, j, 0, 0);
				}
			}
		}

		memset(visited, 0, sizeof(visited));

		int res = bfs(startX, startY);
		if (res == -1) {
			cout << "oop!" << endl;
		} else {
			cout << res << endl;
		}
	}
	return 0;
}