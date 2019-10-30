#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <math.h>

using namespace std;

// 3. 表达式·表达式树·表达式求值
// 中缀转后缀，week2的q3里有类似的算法
// 后缀转二叉树，需要点技巧
// 打印二叉树比较麻烦

struct BinaryTreeNode {
	char data;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode(char x) : data(x), left(NULL), right(NULL) {}
};

// 图形模式的树
char pic[50][300];

// 两数运算
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
	case '/':
		res = num2 / num1;
		break;
	default:
		break;
	}

	return res;
}

string infix2postfix(string s) {
	int n = s.size();
	string postfix;

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

	stack<char> symbol = stack<char>();

	// 符号优先度映射表
	map<char, int> operationPriority;
	operationPriority.insert(make_pair('+', 0));
	operationPriority.insert(make_pair('-', 0));
	operationPriority.insert(make_pair('*', 1));
	operationPriority.insert(make_pair('/', 1));

	n = s.size();
	for (int i = 0; i < n; i++) {
		char ch = s[i];
		if ((ch >= 97 && ch <= 122) || ch == 48) {
			// 变量优先输出
			postfix += ch;
		} else if (ch == ')') {
			// 优先计算小括号的内容
			while (symbol.top() != '(') {
				postfix += symbol.top();
				symbol.pop();
			}
			// 去掉左小括号
			symbol.pop();
		} else if (ch == '(') {
			symbol.push(ch);
		} else {
			// 运算符
			while (!symbol.empty()) {
				char currSymbol = symbol.top();

				// 弹出直到遇到比其优先度小的符号或括号
				if (currSymbol == '(') {
					break;
				} else if (operationPriority[ch] <= operationPriority[currSymbol]) {
					postfix += currSymbol;
					symbol.pop();
				} else {
					break;
				}
			}
			symbol.push(ch);
		}
	}

	// 输出剩余运算符
	while (!symbol.empty()) {
		postfix += symbol.top();
		symbol.pop();
	}

	return postfix;
}

// 计算后缀表达式
int cal(string postfix, map<char, int>& values) {
	stack<int> nums;
	int n = postfix.length();

	for (int i = 0; i < n; i++) {
		char ch = postfix[i];

		if ((ch >= 97 && ch <= 122) || ch == 48) {
			nums.push(values[ch]);
		} else {
			int num1 = nums.top();
			nums.pop();
			int num2 = nums.top();
			nums.pop();

			nums.push(arithmetic(num1, num2, ch));
		}
	}
	return nums.top();
}

// 根据后缀建树
BinaryTreeNode* buildTree(string postfix) {
	stack<BinaryTreeNode *> variables;
	int n = postfix.size();

	for (int i = 0; i < n; ++i) {
		char ch = postfix[i];
		BinaryTreeNode * node = new BinaryTreeNode(postfix[i]);

		if ((ch >= 97 && ch <= 122) || ch == 48) {
			// 数字入栈
			variables.push(node);

		} else {
			// 遇到运算符，则将它前两个元素作为它的左右子树，并入栈
			node->right = variables.top();
			variables.pop();
			node->left = variables.top();
			variables.pop();
			variables.push(node);
		}
	}

	return variables.top();
}

// 确定图形化的树，存储到pic数组
// x行号，y列号
// 这里比较坑，子结点之间的空格是由其深度决定的
void drawTree(BinaryTreeNode* root, int x, int y, int space) {

	pic[x][y] = root->data;

	if (root->left != NULL) {
		pic[x + 1][y - 1] = '/';
		drawTree(root->left,  x + 2, y - space, space >> 1);
	}
	if (root->right != NULL) {
		pic[x + 1][y + 1] = '\\';
		drawTree(root->right, x + 2, y + space, space >> 1);
	}
}

// 打印树
void printTree(int height){
	// 行数量包含 '\' '/' 符号
	for (int i = 0; i < 2 * height - 1; i++) {

		// 找到当前行的最后一个空字符，打上结尾标记
		int j = 299;
		while (pic[i][j--] == ' ');
		pic[i][j + 2] = '\0';
		
		cout << pic[i] << endl;
	}
}

// 返回高度
int layers(BinaryTreeNode* root) {
	if (root == NULL) {
		return 0;
	}

	int left = layers(root->left);
	int right = layers(root->right);

	// +1是要包含当前结点
	// 根结点的高度为1，深度为0
	return left > right ? left + 1 : right + 1;
}

int main(int argc, char *argv[]) {

	string infix;
	getline(cin, infix);

	// 中缀转后缀
	string postfix = infix2postfix(infix);
	cout << postfix << endl;

	// 后缀建树
	BinaryTreeNode* root = buildTree(postfix);

	// 树图形化显示
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 300; j++) {
			// 初始化为空
			pic[i][j] = ' ';
		}
	}
	int height = layers(root);
	int y = pow(2, height - 1) - 1;
	drawTree(root, 0, y, (y + 1) >> 1);
	printTree(height);

	// 计算表达式的值
	int n = 0;
	cin >> n;
	map<char, int> values;
	while (n--) {
		char variable = '\0';
		int value = 0;
		cin >> variable;
		cin.get();
		cin >> value;
		cin.get();

		values.insert(make_pair(variable, value));
	}
	cout << cal(postfix, values) << endl;

	return 0;
}