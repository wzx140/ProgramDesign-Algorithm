#include <iostream>
#include <math.h>

using namespace std;

// 编程题＃2： 拨钟问题

// 每个action都有4中实施方法，实施0-4次，所以总共有4^9种情况
// 仔细观察actiongs数组发现，a4,a5,a6唯一的改变第一行的元素，类比第一个问题，我们可以得到以下解决方案
// 对a1,a2,a3进行枚举，确定a4,a5,a6使得ABC都为12点
// 检查是否存在a6,a8使得DEF都为12点，检查是否存在a7使得GHI都为12点
int actions[9][9] = {
	//   A  B  C  D  E  F  G  H  I
		{1, 1, 0, 1, 1, 0, 0, 0, 0},  //a1: ABDE
		{1, 1, 1, 0, 0, 0, 0, 0, 0},  //a2: ABC
		{0, 1, 1, 0, 1, 1, 0, 0, 0},  //a3: BCEF
		{1, 0, 0, 1, 0, 0, 1, 0, 0},  //a4: ADG
		{0, 1, 0, 1, 1, 1, 0, 1, 0},  //a5: BDEFH
		{0, 0, 1, 0, 0, 1, 0, 0, 1},  //a6: CFI
		{0, 0, 0, 1, 1, 0, 1, 1, 0},  //a7: DEGH
		{0, 0, 0, 0, 0, 0, 1, 1, 1},  //a8: GHI
		{0, 0, 0, 0, 1, 1, 0, 1, 1}  //a9: EFHI
};

// clock经过time次的op拨动后
void rotate(int clock[], int op, int time) {

	for (int i = 0; i < 9; i++) {
		clock[i] += actions[op][i] * time;
		clock[i] %= 4;
	}
}

bool guess(int clock[], int ops[]) {

	// 储存中间状态
	int tempClock[9] = { 0 };
	for (int i = 0; i < 9; i++) {
		tempClock[i] = clock[i];
	}

	// 应用a1 a2 a3更改
	for (int i = 0; i < 3; i++) {
		rotate(tempClock, i, ops[i]);
	}

	// 调整a4 a5 a6 以适应第一行
	for (int i = 0; i < 3; i++) {
		ops[i + 3] = (4 - tempClock[i]) % 4;
	}

	// 应用a4 a5 a6更改
	for (int i = 3; i < 6; i++) {
		rotate(tempClock, i, ops[i]);
	}

	// 调整a7 a9 以适应第二行
	ops[6] = (4 - tempClock[3]) % 4;
	ops[8] = (4 - tempClock[5]) % 4;
	// 应用
	rotate(tempClock, 6, ops[6]);
	rotate(tempClock, 8, ops[8]);

	// 检查第二行是否合法
	if (tempClock[4] != 0) {
		return false;
	}

	// 调整并应用a8
	ops[7] = (4 - tempClock[6]) % 4;
	rotate(tempClock, 7, ops[7]);

	// 检查第三行是否合法
	for (int i = 6; i < 9; i++) {
		if (tempClock[i] != 0) {
			return false;
		}
	}

	return true;
}

//枚举a1 a2 a3的所有情况  
int enumerate(int clock[], int ops[]) {

	int minCount = pow(4, 9) + 1;
	int tempOps[9] = { 0 };
	for (int i = 0; i < 9; i++) {
		tempOps[i] = ops[i];
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {

				tempOps[0] = i;
				tempOps[1] = j;
				tempOps[2] = k;

				if (guess(clock, tempOps)) {

					// 统计移动次数
					int count = 0;
					for (int i = 0; i < 9; i++) {
						count += tempOps[i];
					}

					if (count < minCount) {
						for (int i = 0; i < 9; i++) {
							ops[i] = tempOps[i];
						}
					}
				}

			}
		}
	}

	return minCount;
}

//int main(int argc, char *argv[]) {
//
//	int clock[9] = { 0 };
//	// 每种操作的次数
//	int ops[9] = { 0 };
//
//	for (int i = 0; i < 9; i++) {
//		cin >> clock[i];
//	}
//
//	int count = enumerate(clock, ops);
//
//	for (int i = 0; i < 9; i++) {
//		if (ops[i] != 0) {
//			cout << i + 1 << ' ';
//			ops[i]--;
//			i--;
//		}
//	}
//
//	return 0;
//}