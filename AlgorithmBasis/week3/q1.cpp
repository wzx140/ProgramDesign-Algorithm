#include <iostream>

using namespace std;

// 1： 完美覆盖
// 递推公式很难想到，参考了这篇的解法
// https://segmentfault.com/a/1190000013500389

// f(n) = 3f(n-2) + 2f(n-4) + 2f(n-6) + ... + 2f(0)
int recursive(int n) {
	if (n == 0) {
		return 1;
	} else if (n % 2 != 0) {
		return 0;
	} else {
		int sum = 3 * recursive(----n);
		while (n != 0) {
			sum += 2 * recursive(----n);
		}
		return sum;
	}
}

int main(int argc, char *argv[]) {
	int n = 0;

	while (cin >> n && n != -1) {
		cout << recursive(n) << endl;
	}

	return 0;
}