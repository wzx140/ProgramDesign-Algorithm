#include <iostream>

using std::cout;
using std::cin;
using std::endl;

// 5：猴子吃桃

int n = 0;

int main(int argc, char *argv[]) {

	while (cin >> n && n != 0) {
		int num = 0;

		// 最后一只猴子拿走的桃子数
		for (int i = 1; ; i++) {

			num = i * n + 1;

			// 是否找到这样的桃子数
			bool flag = true;
			// 从后往前推
			for (int j = 1; j < n; j++) {
				if (num % (n - 1) == 0) {
					num = num / (n - 1)*n + 1;
				} else {
					flag = false;
					break;
				}
			}

			if (flag) {
				break;
			}
		}

		cout << num << endl;
	}

	return 0;
}