#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::sort;

// 1：Aggressive cows
// 约翰在他的畜棚上建立了N(2<=N<=100000)个畜栏
// 畜栏分布在一条直线上,x1...xN(0<=xi<=1000000000)
// 奶牛放在畜栏里，最大化它们间的最小间隔，并输出这个值

vector<int> pos;

// 极值问题->状态判断
bool check(int space, int cowNum) {
	// 第一个畜栏放入奶牛
	int pre = pos[0];
	cowNum--;
	int length = pos.size();

	for (int i = 1; i < length; i++) {
		if (pos[i] - pre >= space) {
			// 间距足够，当前畜栏放入奶牛
			pre = pos[i];
			cowNum--;
		}
	}

	if (cowNum <= 0) {
		return true;
	} else {
		return false;
	}
}

int main(int argc, char *argv[]) {

	int n = 0;
	int c = 0;
	cin >> n >> c;

	for (int i = 0; i < n; i++) {
		int k = 0;
		cin >> k;
		pos.push_back(k);
	}

	sort(pos.begin(), pos.end());

	int left = 0;
	int right = pos[n - 1] - pos[0];
	int ans = right;
	while (left <= right) {
		int middle = left + (right - left) / 2;
		if (check(middle, c)) {
			ans = middle;
			left = middle + 1;
		} else {
			right = middle - 1;
		}
	}

	cout << ans << endl;

	return 0;
}