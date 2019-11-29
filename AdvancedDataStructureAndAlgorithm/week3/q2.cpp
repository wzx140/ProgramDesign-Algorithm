#include <iostream>
#include <algorithm>

using std::endl;
using std::cin;
using std::cout;
using std::sort;
using std::abs;

// 2. The Peanuts
// 小猴子采花生，每次去花生最多的地方采
// 从road到field，走到下一个结点，采花生均耗费一个单位时间
// 给定时间回到road上，最多采多少花生

int m = 0, n = 0, k = 0, c = 0;

struct Peanuts {
	int value;
	int x;
	int y;
	Peanuts(int a, int b, int c) :x(a), y(b), value(c) {}
	Peanuts() :x(0), y(0), value(0) {}
	bool operator < (const Peanuts &peanut) const {
		return value > peanut.value;
	}
}peanuts[3000];

int main(int argc, char *argv[]) {
	int t = 0;
	cin >> t;
	while (t--) {
		c = 0;
		cin >> m >> n >> k;
		for (int i = 1; i < m + 1; i++) {
			for (int j = 1; j < n + 1; j++) {
				peanuts[c].x = i;
				peanuts[c].y = j;
				cin >> peanuts[c++].value;
			}
		}
		sort(peanuts, peanuts + c);

		int count = 0;
		// 前往第一个花生点
		k -= peanuts[0].x;
		for (int i = 0; i < c; i++) {

			if (peanuts[i].value == 0) {
				break;
			}

			// 采完当前花生还能回到road
			if (k >= peanuts[i].x + 1) {
				count += peanuts[i].value;
				k -= abs(peanuts[i].x - peanuts[i + 1].x) + abs(peanuts[i].y - peanuts[i + 1].y) + 1;
			} else {
				break;
			}
		}
		cout << count << endl;
	}
	return 0;
}