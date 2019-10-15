#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

// 3. 大整数乘法

int main(int argc, char *argv[]) {
	int a[200] = { 0 };
	int b[200] = { 0 };
	int c[40000] = { 0 };

	char aSource[201], bSource[201];

	cin.getline(aSource, 200);
	cin.getline(bSource, 200);

	int aLen = strlen(aSource);
	int bLen = strlen(bSource);

	// 倒序并转化为数字
	for (int i = 0; i < aLen; i++) {
		a[aLen - i] = aSource[i] - 48;
	}
	for (int i = 0; i < bLen; i++) {
		b[bLen - i] = bSource[i] - 48;
	}

	// 当前结果位
	int curr = 0;
	for (int i = 1; i < bLen + 1; i++) {

		// 进位
		int carry = 0;
		for (int j = 1; j < aLen + 1; j++) {
			curr = i + j - 2;

			// 乘积结果+进位+当前结果位
			int result = a[j] * b[i] + carry + c[curr];

			carry = result / 10;
			c[curr] = result % 10;
		}

		// 最高位进位
		while (carry) {
			c[++curr] = carry % 10;
			carry = carry / 10;
		}
	}

	for (int i = curr; i >= 0; i--) {
		cout << c[i];
	}

	return 0;
}