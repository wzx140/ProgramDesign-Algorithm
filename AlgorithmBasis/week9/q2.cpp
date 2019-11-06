#include <iostream>
#include <vector>
#include <algorithm>

using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::min;

// 2：Yogurt factory
// 酸奶工厂每周生产一个单位的酸奶的成本为 ci(1<=ci<=5000)
// 对应每周的销量为 y_i(0<=y_i<=10000)
// 储存的费用是 s(1<=s<=100)每单位每周
// 求保持供应的最小花费
// 总花费可能超出int32

int c[10000];
int y[10000];

long long greedy(int n, int s) {
	long long total = 0;
	int cost = 0;
	for (int i = n - 1; i >= 0; i--) {
		// 与前面生产的单位费用作比较，取最小值
		cost = c[i];
		for (int j = 0; j <= i - 1; j++) {
			cost = min(cost, c[j] + s * (i - j));
		}
		total += cost * y[i];
	}
	return total;
}

int main(int argc, char *argv[]) {
	int n = 0;
	int s = 0;
	cin >> n >> s;

	for (int i = 0; i < n; i++) {
		cin >> c[i] >> y[i];
	}

	long long total = greedy(n, s);

	cout << total << endl;

	return 0;
}