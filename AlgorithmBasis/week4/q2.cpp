#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 2： 滑雪

struct Dot {
	int x;
	int y;
	int height;
};

// 最短路径缓存数组
int route[101][101];
// 雪场
int playground[101][101];
int row = 0;
int col = 0;

// 搜索临近四个区域，这里采用课程里介绍的"人人为我"策略
int search(int x, int y) {

	if (route[x][y] > 0) {
		return route[x][y];
	}

	int nextX = 0;
	int nextY = 0;
	int maxRoute = 0;

	// 上
	nextX = x;
	nextY = y - 1;
	if (nextY >= 0) {
		if (playground[nextX][nextY] < playground[x][y]) {
			maxRoute = max(maxRoute, route[nextX][nextY]);
		}
	}

	// 下
	nextX = x;
	nextY = y + 1;
	if (nextY < col) {
		if (playground[nextX][nextY] < playground[x][y]) {
			maxRoute = max(maxRoute, route[nextX][nextY]);
		}
	}

	// 左
	nextX = x - 1;
	nextY = y;
	if (nextX >= 0) {
		if (playground[nextX][nextY] < playground[x][y]) {
			maxRoute = max(maxRoute, route[nextX][nextY]);
		}
	}

	// 右
	nextX = x + 1;
	nextY = y;
	if (nextX < row) {
		if (playground[nextX][nextY] < playground[x][y]) {
			maxRoute = max(maxRoute, route[nextX][nextY]);
		}
	}

	route[x][y] = maxRoute + 1;
	return maxRoute + 1;
}

bool cmp(const Dot& a, const Dot& b) {
	return a.height < b.height;
}

int main(int argc, char *argv[]) {

	cin >> row >> col;

	// 初始化雪场
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			int value = 0;
			cin >> value;
			playground[i][j] = value;
		}
	}

	// 排序
	// 这里有点麻烦,需要再新建一个数组储存排序结果
	vector<Dot> beSort;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Dot dot = { i,j,playground[i][j] };
			beSort.push_back(dot);
		}
	}
	sort(beSort.begin(), beSort.end(), cmp);

	// 搜索
	int res = 0;
	for (int i = 0; i < beSort.size(); i++) {
		int x = beSort[i].x;
		int y = beSort[i].y;
		res = max(res, search(x, y));
	}

	cout << res << endl;

	return 0;
}