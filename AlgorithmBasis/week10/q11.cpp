#include <iostream>
#include <algorithm>

using std::endl;
using std::cin;
using std::cout;
using std::sort;

// 11：至少有多少只恼人的大青蛙?
// 1. 按照限制条件，求出所有合法的青蛙，按踩踏次数排序。
// 2. 每次放出踩踏次数最大且合法的青蛙
// 3. 一旦所有该踩踏的地方都踩踏了，就将青蛙个数输出

int r = 0;
int c = 0;
int n = 0;

// 稻田
int farmLand[50][50];

// 合法青蛙的个数
int frogNum = 0;

// 可能存在的青蛙
struct Frog {
	int x;
	int y;
	int dx;
	int dy;
	// 踩踏稻田的个数
	int count;
	Frog(int a, int b, int c, int d) :x(a), y(b), dx(c), dy(d) {}
	Frog() :x(-1), y(-1), dx(-1), dy(-1) {}
	bool operator < (const Frog &frog) const {
		return count > frog.count;
	}
}frogs[700 * 700];

inline bool inrange(const int &x, const int &y) {
	if (x < 0 || y < 0 || x > r - 1 || y > c - 1) {
		return false;
	}
	return true;
}

// 当前已放的青蛙数，上一次放的青蛙的索引，剩余践踏数
int dfs(int frog, int last, int sum) {
	if (sum == 0) {
		return frog;
	}

	// 不同的青蛙可能走同一条路径
	for (int i = last; i < frogNum; i++) {
		if (frogs[i].count > sum) {
			continue;
		}

		int startX = frogs[i].x;
		int startY = frogs[i].y;
		int dx = frogs[i].dx;
		int dy = frogs[i].dy;
		bool flag = false;
		// 检查路径是否仍然可用 
		for (int x = startX, y = startY; inrange(x, y); x += dx, y += dy) {
			if (farmLand[x][y] <= 0) {
				flag = true;
				break;
			}
		}
		if (flag) {
			continue;
		}
		// 处理走过的路径
		for (int x = startX, y = startY; inrange(x, y); x += dx, y += dy) {
			farmLand[x][y]--;
		}

		int res = dfs(frog + 1, i, sum - frogs[i].count);
		if (res != -1) {
			return res;
		}

		// 回溯
		for (int x = startX, y = startY; inrange(x, y); x += dx, y += dy) {
			farmLand[x][y]++;
		}
	}

	return -1;
}


// 求所有合法的青蛙
void pretreatment() {

	// 保存所有合法的青蛙
	// 防止重复，正反方向的出现
	frogNum = 0;
	for (int i1 = 0; i1 < r; i1++) {
		for (int j1 = 0; j1 < c; j1++) {
			if (farmLand[i1][j1] > 0) {
				for (int i2 = i1; i2 < r; i2++) {
					int j2 = 0;
					if (i2 == i1) {
						j2 = j1;
					} else {
						j2 = 0;
					}
					for (; j2 < c; j2++) {
						if (farmLand[i2][j2] > 0) {

							int dx = i2 - i1;
							int dy = j2 - j1;

							if (dx == 0 && dy == 0) {
								continue;
							}

							// 检查合法性
							bool flag1 = false;
							bool flag2 = false;

							// 处于起点，反向没有点，防止重复
							for (int x = i1 - dx, y = j1 - dy; inrange(x, y); x -= dx, y -= dy) {
								if (farmLand[x][y] > 0) {
									flag1 = true;
								}
							}

							// 正向可以跳出
							int count = 1;
							for (int x = i2, y = j2; inrange(x, y); x += dx, y += dy) {
								if (farmLand[x][y] > 0) {
									count++;
								} else {
									flag2 = true;
									break;
								}
							}
							if (flag1 || flag2) {
								continue;
							} else {
								// 添加
								frogs[frogNum].x = i1;
								frogs[frogNum].y = j1;
								frogs[frogNum].dx = dx;
								frogs[frogNum].dy = dy;
								frogs[frogNum++].count = count;
							}

						}
					}
				}
			}
		}
	}
	// 排序，每次优先放破坏力大的青蛙去破坏稻田
	sort(frogs, frogs + frogNum);
}

int main(int argc, char *argv[]) {
	int t = 0;
	cin >> t;
	while (t--) {
		// 总践踏数
		int sum = 0;
		cin >> r >> c >> n;
		for (int i = 0; i < n; i++) {
			int x = 0;
			int y = 0;
			cin >> x >> y;
			cin >> farmLand[x - 1][y - 1];
			sum += farmLand[x - 1][y - 1];
		}
		pretreatment();
		cout << dfs(0, 0, sum) << endl;
	}
	return 0;
}