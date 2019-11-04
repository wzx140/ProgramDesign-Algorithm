#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::stack;
using std::queue;

// 2. 树的镜面映射

struct TreeNode {
	char data;
	TreeNode* leftMostChild;
	TreeNode* rightSibling;
	TreeNode(char ch) :data(ch), leftMostChild(NULL), rightSibling(NULL) {}
};

// 伪满二叉树的空结点在最后打印的时候可以不输出
// 或者可以在重建之后，删除$结点
// 参考树的双标记的前根序列的恢复
TreeNode* buildTree(vector<char>& chs, vector<int>& flags) {
	stack<TreeNode*> aStack;
	int length = chs.size();
	TreeNode* pointer = new TreeNode('\0');
	TreeNode* root = pointer;

	for (int i = 0; i < length - 1; i++) {
		pointer->data = chs[i];

		TreeNode* temp = new TreeNode('\0');

		if (flags[i] == 0) {
			// 伪满二叉树的分支结点必有右子结点
			aStack.push(pointer);
		}

		// 优先分配左子结点，就近分配右子结点
		if (flags[i] == 0 && pointer->leftMostChild == NULL) {
			pointer->leftMostChild = temp;
		} else{
			pointer = aStack.top();
			aStack.pop();
			pointer->rightSibling = temp;
		}

		pointer = temp;
	}
	// 处理最后一个结点
	pointer->data = chs[length - 1];

	return root;
}

void mirror(TreeNode* root) {
	if (root->leftMostChild != NULL) {
		stack<TreeNode*> aStack;

		// 所有子结点压栈
		TreeNode* child = root->leftMostChild;
		while (child != NULL) {
			aStack.push(child);
			mirror(child);
			child = child->rightSibling;
		}

		// 子结点弹栈
		TreeNode* brother = aStack.top();
		aStack.pop();
		root->leftMostChild = brother;
		brother->rightSibling = NULL;
		while (!aStack.empty()) {
			child = aStack.top();
			aStack.pop();
			child->rightSibling = NULL;
			brother->rightSibling = child;
			brother = child;
		}
	}
}

void seqTraverse(TreeNode* T) {
	queue<TreeNode*> aQueue;
	TreeNode* pointer = T;

	while (pointer != NULL) {
		aQueue.push(pointer);
		pointer = pointer->rightSibling;
	}

	while (!aQueue.empty()) {
		pointer = aQueue.front();
		aQueue.pop();
		if (pointer->data != '$') {
			cout << pointer->data << ' ';
		}

		pointer = pointer->leftMostChild;
		while (pointer != NULL) {
			aQueue.push(pointer);
			pointer = pointer->rightSibling;
		}
	}
}

int main(int argc, char *argv[]) {
	int n = 0;
	cin >> n;

	vector<char> chs;
	vector<int> flags;
	while (n--) {
		char ch = '\0';
		int flag = 0;
		cin >> ch;
		cin >> flag;
		chs.push_back(ch);
		flags.push_back(flag);
	}

	TreeNode* root = buildTree(chs, flags);
	mirror(root);
	seqTraverse(root);

	return 0;
}