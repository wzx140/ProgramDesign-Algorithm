#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::string;

// 1：Shredding Company
// 将一串数字分割，使得分割后的数字和最接近 target(不大于)
// 1. 如果数字正好等于target，则不会剪切
// 2. 如果多种最接近target的方案，则输出 rejected
// 3. 如果数字和大于target，则输出 error
// 4. 否则输出sum和方案

int minDifference = 2147483647;	// 与target的最小差
int target = -1;
int state = -1;					// 状态 0->存在解决方案 1->重复 -1->无解决方案
vector<int> tempSolution;		// 临时存储解决方案
vector<int> solution;			// minDifference对应的解决方案

// divisor最多比num的长度多1
bool divisorInNum(int num, int divisor) {
	if (num / divisor != 0) {
		return true;
	}

	if (num / divisor == 0 && num / (divisor / 10) != 0) {
		return true;
	}

	return false;
}

void dfs(int num, int difference) {

	// 最优化剪枝
	if (difference - num > minDifference) {
		return;
	}
	// 可行性剪枝
	if (difference < 0 || (difference == 0 && num != 0)) {
		return;
	}
	if (num == 0) {
		if (difference < minDifference) {
			state = 0;
			// 保存符合要求的解决方案
			minDifference = difference;
			solution = tempSolution;
		} else if (difference == minDifference) {
			state = 1;
		}
		return;
	}

	int divisor = 10;
	while (num != 0 && divisorInNum(num, divisor)) {
		int splitor = num % divisor;
		tempSolution.push_back(splitor);
		dfs(num / divisor, difference - splitor);
		// 回溯
		tempSolution.pop_back();
		divisor *= 10;
	}
}

int main(int argc, char *argv[]) {
	int num = -1;
	while (cin >> target >> num && target != 0 && num != 0) {
		minDifference = 2147483647;
		state = -1;
		if (num == target) {
			cout << num << ' ' << num << endl;
		} else {
			dfs(num, target);
			if (state == 0) {
				cout << target - minDifference;
				// 倒序遍历
				for (int i = solution.size() - 1; i >= 0; i--) {
					cout << " " << solution[i];
				}
				cout << endl;
			} else if (state == -1) {
				cout << "error" << endl;
			} else if (state == 1) {
				cout << "rejected" << endl;
			}
		}
	}

	return 0;
}