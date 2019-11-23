#include <iostream>
#include <limits>
#include <algorithm>

using std::endl;
using std::cin;
using std::cout;
using std::numeric_limits;
using std::min;

// 4：Minecraft

int n = 0;
int minPaper = numeric_limits<int>::max();

// 无论怎么剪枝都会超出时间限制
//// 长宽高，剩余个数
//void recursive(int length, int wide, int height, int num) {
//
//	// 为避免重复,规定 长<=宽<=高
//	if (length > wide || wide > height) {
//		return;
//	}
//
//	// 可行性剪枝
//	if (num < 0) {
//		return;
//	}
//
//	// 最优化剪枝
//	if (length * wide * 2 + length * height * 2 + wide * height * 2 > minPaper) {
//		return;
//	}
//
//	if (num == 0) {
//		minPaper = min(minPaper, length * wide * 2 + length * height * 2 + wide * height * 2);
//		return;
//	}
//
//	// 可行性剪枝
//	// 高度增加
//	int area = 0;
//	if (num >= length * wide) {
//		recursive(length, wide, height + 1, num - length * wide);
//	}
//	// 宽度增加
//	if (num >= length * height) {
//		recursive(length, wide + 1, height, num - length * height);
//	}
//	// 长度增加
//	if (num >= height * wide) {
//		recursive(length + 1, wide, height, num - height * wide);
//	}
//}

int main(int argc, char *argv[]) {
	int c = 0;
	cin >> c;
	while (c--) {
		cin >> n;
		minPaper = numeric_limits<int>::max();

		// 枚举长宽
		for (int length = 1; length <= n; ++length) {
			if (n%length == 0) {
				for (int wide = 1; wide <= n / length; ++wide) {
					if (n % (length*wide) == 0) {
						int height = n / (length*wide);
						int area = 2 * (length*wide + wide * height + height * length);
						minPaper = min(area, minPaper);
					}
				}
			}
		}

		cout << minPaper << endl;
	}
	return 0;
}