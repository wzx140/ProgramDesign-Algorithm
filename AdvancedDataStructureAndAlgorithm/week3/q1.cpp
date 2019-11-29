#include <iostream>
#include <algorithm>
#include <functional>

using std::endl;
using std::cout;
using std::cin;
using std::sort;
using std::max_element;
using std::greater;

// 1. 牛的选举

struct a {
	int value = 0;
	int index = 0;
	bool operator < (const a &l) const {
		return value > l.value;
	}
}a[60000];

int b[60000];

int main(int argc, char *argv[]) {
	int n = 0;
	int k = 0;
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> a[i].value >> b[i];
	}

	for (int i = 0; i < n; i++) {
		a[i].index = i;
	}
	sort(a, a + n);

	int maxValue = 0;
	int maxIndex = 0;
	for (int i = 0; i < k; i++) {
		if (b[a[i].index] > maxValue) {
			maxValue = b[a[i].index];
			maxIndex = a[i].index;
		}
	}
	cout << maxIndex + 1 << endl;

	return 0;
}