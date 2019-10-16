#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// 2. 出栈序列统计
// 并不需要真的构造一个栈

void recursive(int &source, int &stack, int &count) {
	if (source == 0 && stack == 0) {
		// 一种方式结束
		count++;
		return;
	} else if (stack == 0) {
		stack++;
		source--;
		recursive(source, stack, count);
	} else if (source == 0) {
		stack--;
		recursive(source, stack, count);
	} else {
		int stack2 = stack;
		int source2 = source;

		// 进栈
		stack2++;
		source2--;
		recursive(source2, stack2, count);

		// 出栈
		stack--;
		recursive(source, stack, count);
	}
}

int main(int argc, char *argv[]) {
	int n = 0;
	cin >> n;

	int count = 0;
	int stack = 0;
	recursive(n, stack, count);
	cout << count;

	return 0;
}