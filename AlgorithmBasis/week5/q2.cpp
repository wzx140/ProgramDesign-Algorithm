#include <iostream>
#include <algorithm>

using namespace std;

// 2： Charm Bracelet

int weights[3402];
int charms[3402];
int cache[12881];
int limit;
int n;

// 递归的写法,较为容易理解
//int getMax(int item, int limit) {
//	if (item == 0) {
//		return 0;
//	}
//	if (weights[item] > limit) {
//		// 最后一个手镯超重
//		return getMax(item - 1, limit);
//	} else {
//		// 最后一个手镯放与不放,返回最大的charm
//		return max(getMax(item - 1, limit), getMax(item - 1, limit - weights[item]) + weights[item]);
//	}
//}

int main(int argc, char *argv[]) {
	cin >> n >> limit;

	// 输入
	for (int i = 0; i < n; i++) {
		cin >> weights[i] >> charms[i];
	}

	int currLimit = 0;
	for (int i = 0; i < n; i++) {
		int weight = weights[i];
		int desirability = charms[i];

		// 剪枝，减少不必要的遍历
		currLimit += weight;
		currLimit = min(currLimit, limit);

		// 倒序,因为防止出现 cache[j - weight]中已经使用了当前手镯 的情况
		for (int j = limit; j >= weight; j--) {
			// 当前手镯应不应该放入
			cache[j] = max(cache[j - weight] + desirability, cache[j]);
		}
	}

	cout << cache[limit] << endl;


	return 0;
}