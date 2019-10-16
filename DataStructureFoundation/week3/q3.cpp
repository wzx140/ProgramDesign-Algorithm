#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <stack>

using namespace std;

// 3. 等价表达式

// 利用两个栈，一个栈储存符号，一个栈储存数字。把中缀表达式转化为后缀表达式并求解，这两个过程耦合在一起完成
// 把字母的ASCII值带入计算，这样会简单很多
// 但是似乎有问题， a+1 和 b 这两个式子就会错误的相等，可以通过将字母用多种值表示，多次比较表达式的值
// 这个解法通过了 coursera 的测试

int arithmetic(int num1, int num2, char operation) {
	int res = 0;

	switch (operation) {
	case '+':
		res = num1 + num2;
		break;
	case '-':
		res = num2 - num1;
		break;
	case '*':
		res = num1 * num2;
		break;
	default:
		break;
	}

	return res;
}

int calculate(string s) {
	int n = s.size();

	// 添加负号的前导0
	for (int i = 0; i < n; i++) {
		char ch = s[i];
		if (ch == '-') {
			if (i == 0) {
				s = '0' + s;
			} else if (s[i - 1] == '(') {
				s = (s.substr(0, i) + '0' + s.substr(i, n - i));
			}
		}
	}

	stack<int> num = stack<int>();
	stack<char> symbol = stack<char>();

	// 符号优先度映射表
	map<char, int> operationPriority;
	operationPriority.insert(make_pair('+', 0));
	operationPriority.insert(make_pair('-', 0));
	operationPriority.insert(make_pair('*', 1));

	n = s.size();
	for (int i = 0; i < n; i++) {
		char ch = s[i];
		if (ch == ' ' || ch == '\t') {
			continue;

		} else if (ch >= 48 && ch <= 57) {
			// 数字压栈
			num.push(ch - 48);
		} else if (ch >= 97) {
			// 变量的ASCII值压入栈
			num.push(ch);
		} else if (ch == ')') {
			// 优先计算小括号的内容
			while (symbol.top() != '(') {
				int num1 = num.top();
				num.pop();
				int num2 = num.top();
				num.pop();
				num.push(arithmetic(num1, num2, symbol.top()));
				symbol.pop();
			}
			// 去掉左小括号
			symbol.pop();
		} else if (ch == '(') {
			symbol.push(ch);
		} else {
			// 符号
			while (!symbol.empty()) {
				char currSymbol = symbol.top();

				// 计算表达式直到遇到比其优先度小的符号或括号
				if (currSymbol == '(') {
					break;
				} else if (operationPriority[ch] <= operationPriority[currSymbol]) {
					int num1 = num.top();
					num.pop();
					int num2 = num.top();
					num.pop();

					num.push(arithmetic(num1, num2, currSymbol));
					symbol.pop();
				} else {
					break;
				}
			}
			symbol.push(ch);
		}
	}

	// 计算剩余的表达式
	while (!symbol.empty()) {
		int num1 = num.top();
		num.pop();
		int num2 = num.top();
		num.pop();
		num.push(arithmetic(num1, num2, symbol.top()));
		symbol.pop();
	}

	return num.top();
}



int main(int argc, char *argv[]) {
	int n = 0;
	cin >> n;
	cin.get();	// 丢弃换行符

	for (int i = 0; i < n; i++) {
		char s1[100];
		char s2[100];
		cin.getline(s1, 100);
		cin.getline(s2, 100);
		if (calculate(s1) == calculate(s2)) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}

	return 0;
}