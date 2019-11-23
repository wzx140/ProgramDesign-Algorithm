#include <iostream>

using std::endl;
using std::cout;
using std::cin;

// 7：复杂的整数划分问题
// 结合第三题的解答来看
// https://www.cnblogs.com/huashanqingzhu/p/7300766.html

// n的正数划分数，划分总数为k
int recursive1(int n, int k) {
	if (n < k || k == 0 || n == 0) {
		return 0;
	} else if (k == 1 || k == n) {
		return 1;
	} else {
		// 是否包含数1
		return recursive1(n - k, k) + recursive1(n - 1, k - 1);
	}
}

// n的正数划分数，子数不能大于m，必须不同
int recursive2(int n, int m) {
	if (m == 1 && n > m) {
		// 不能重复1
		return 0;
	} else if (n == 1) {
		return 1;
	} else if (m == 1) {
		return 1;
	} else if (m == n) {
		return 1 + recursive2(n, m - 1);
	} else if (n < m) {
		return recursive2(n, n);
	} else if (n > m) {
		// 只有一个m与没有m的情况
		return recursive2(n - m, m - 1) + recursive2(n, m - 1);
	}
}

int recursiveEven(int n, int m);

// n的正数划分数，划分总数为k，只能是奇数
int recursiveOdd(int n, int k) {

	if (n < k || k <= 0 || n <= 0) {
		return 0;
	} else if (k == 1) {
		if (n % 2 == 1) {
			return 1;
		}
	} else if (n >= k) {
		return recursiveOdd(n - 1, k - 1) + recursiveEven(n - k, k);
	}
}

// n的正数划分数，划分总数为k，只能是偶数
int recursiveEven(int n, int k) {

	if (n < k || k <= 0 || n <= 0) {
		return 0;
	} else if (k == 1) {
		if (n % 2 == 0) {
			return 1;
		}
	} else if (n == k) {
		return 0;
	} else if (n > k) {
		return recursiveOdd(n - k, k);
	}
}

int main(int argc, char *argv[]) {
	int n = 0;
	int k = 0;
	while (cin >> n >> k) {
		cout << recursive1(n, k) << endl;
		cout << recursive2(n, n) << endl;

		int sum = 0;
		for (int i = 1; i <= n; i++) {
			sum += recursiveOdd(n, i);
		}
		cout << sum << endl;
	}

	return 0;
}