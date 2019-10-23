#include <iostream>

using namespace std;

// 1：UNIMODAL PALINDROMIC DECOMPOSITIONS
// 比较难想到啊
// 参考这篇的递推公式 http://blog.sina.com.cn/s/blog_7223fd910100x2bw.html

// 如果使用int会溢出
unsigned int cache[250][250];

int main(int argc, char *argv[]) {
	int n = 0;

	// 缓存数组预处理,边界条件
	for (int i = 0; i < 250; i++) {
		for (int j = 0; j < 250; j++) {
			if (i == 0) {
				cache[i][j] = 1;
			} else if (j > i) {
				cache[i][j] = 0;
			} else {
				cache[i][j] = 1;
			}
		}
	}

	while (cin >> n && n != 0) {

		if (cache[n][1] == 1) {
			for (int i = 2; i <= n; i++) {
				for (int j = i / 2; j >= 1; j--) {
					cache[i][j] = cache[i - 2 * j][j] + cache[i][j + 1];
				}
			}
		}

		cout << n << ' ' << cache[n][1] << endl;
	}

	return 0;
}