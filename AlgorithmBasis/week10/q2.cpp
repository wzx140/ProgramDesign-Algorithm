#include<iostream>

using std::endl;
using std::cin;
using std::cout;

// 2：最大公约数
// 题目提示的已经很清楚了，辗转相除法

int recursive(int m,int n) {
	int factor = m % n;
	if (factor == 0) {
		return n;
	} else {
		return recursive(n, factor);
	}
}

int main(int argc, char *argv[]) {
	int m = 0;
	int n = 0;
	while (cin >> m >> n) {
		
		cout << recursive(m, n) << endl;
	}
	return 0;
}