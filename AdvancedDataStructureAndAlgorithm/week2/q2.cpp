#include <iostream>
#include <algorithm>
#include <cmath>

using std::pow;
using std::sort;
using std::endl;
using std::cin;
using std::cout;

// 2. 数据筛选
// n(10<=n<=10^6)
// k(1<=k<=10^5)
// T(1<=T<=10^9)

int nums[2000000];

int main(int argc, char *argv[]) {

	int n = 0, k = 0;
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	sort(nums, nums + n);

	cout << nums[k - 1] << endl;
	return 0;
}