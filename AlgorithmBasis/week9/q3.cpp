#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

// 3：Gone Fishing
// 约翰去钓鱼，一共拥有h(2<=h<=25)小时
// 共有n(n<=25)个小河排成一排
// 小河i到小河i+1的距离需要走ti(0<=ti<=192)个5分钟
// fi(fi>=0)最初五分钟,小河i的捕鱼量
// di(di>=0)小河i捕鱼量的每5分钟的递减值，减到0就不在减
// 约翰一开始处于第一个小河，并且只能沿一个方向走。求最大的捕鱼量
// 如果存在多种方案，那么选取在第一个第一条小河停留时间最长的一种，或者在第二条小河·····第N个条小河停留时间最长的一种方案。

int h = 0;	// 总时间
int n = 0;	// 小河数
int f[25];	// 单位时间捕鱼量
int d[25];	// 捕鱼递减量
int t[25];	// 时间间隔

int tempF[25];	// 暂存的单位时间捕鱼量
int ans[25];	// 每个小河所花时间
int tempAns[25];	// 暂存的每个小河所花时间

int getMax(int a[], int n) {
	int value = 0;
	int index = 0;
	for (int i = 0; i <= n; i++) {
		if (a[i] > value) {
			value = a[i];
			index = i;
		}
	}
	return index;
}

int greedy() {
	int maxAmount = 0;

	// 到达第i个小河需要的时间
	for (int i = 1; i < n; i++) {
		t[i] += t[i - 1];
	}

	// 计算到达第i小河的最大捕鱼量
	for (int i = 0; i < n; i++) {
		int amount = 0;
		// 新的状态，更新单位时间捕鱼量
		for (int j = 0; j <= i; j++) {
			tempF[j] = f[j];
		}
		for (int j = 0; j < n; j++) {
			tempAns[j] = 0;
		}

		// 减去路程，剩下的纯钓鱼的时间
		int tempH = h - t[i];
		while (tempH > 0) {

			// 每个时间间隔去产鱼量最大的小河钓
			int pos = getMax(tempF, i);

			// 所有能到达的小河产鱼量都为0，把时间都花在第一个小河里
			if (tempF[pos] == 0) {
				tempAns[0] += tempH;
				break;
			}

			// 钓鱼更新
			amount += tempF[pos];
			tempF[pos] = tempF[pos] - d[pos] < 0 ? 0 : tempF[pos] - d[pos];
			tempAns[pos]++;
			tempH--;
		}

		if (amount > maxAmount) {
			maxAmount = amount;
			for (int j = 0; j < n; j++) {
				ans[j] = tempAns[j];
			}
		} else if (amount == maxAmount) {
			// 将多余时间尽可能放在前面的小河里
			bool flag = false;
			for (int i = 0; i < n; i++) {
				if(tempAns[i]>ans[i]){
					flag = true;
					break;
				}else if(tempAns[i]<ans[i]){
					break;
				}
			}
			if (flag) {
				for (int i = 0; i < n; i++) {
					ans[i] = tempAns[i];
				}
			}
					
		}
	}

	return maxAmount;
}

int main(int argc, char *argv[]) {

	while (cin >> n && n != 0) {

		for (int i = 0; i < n; i++) {
			ans[i] = 0;
		}

		cin >> h;
		h *= 12;
		for (int i = 0; i < n; i++) {
			cin >> f[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> d[i];
		}
		for (int i = 0; i < n - 1; i++) {
			cin >> t[i + 1];
		}

		int amount = greedy();

		// 每个小河停留的时间
		for (int i = 0; i < n - 1; i++) {
			cout << ans[i] * 5 << ", ";
		}
		cout << ans[n - 1] * 5 << endl;

		cout << "Number of fish expected: " << amount << endl << endl;
	}

	return 0;
}