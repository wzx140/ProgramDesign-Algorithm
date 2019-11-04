#include <iostream>
#include <vector>
#include <queue>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::queue;
using std::string;
using std::getline;

// 1. 森林的带度数层次序列存储

struct TreeNode {
	char data;
	TreeNode* leftMostChild;
	TreeNode* rightSibling;
	TreeNode(char ch) :data(ch), leftMostChild(NULL), rightSibling(NULL) {}
};

// 字符串分割
void SplitString(const string& source, vector<string>& res, const string& split) {
	int pos1, pos2;
	pos2 = source.find(split);
	pos1 = 0;
	while (pos2 != string::npos) {
		res.push_back(source.substr(pos1, pos2 - pos1));

		pos1 = pos2 + split.size();
		pos2 = source.find(split, pos1);
	}
	if (pos1 != source.length()) {
		res.push_back(source.substr(pos1));
	}
}

// 后序遍历
void postOrderTraverse(TreeNode* T) {
	while (T != NULL) {
		postOrderTraverse(T->leftMostChild);
		std::cout << T->data << ' ';
		T = T->rightSibling;
	}
}

TreeNode* transform(vector<char>& nodes, vector<int>& degrees) {
	queue<TreeNode*> aQueue;
	int length = nodes.size();

	TreeNode* root = NULL;

	for (int i = 0; i < length; i++) {
		int degree = degrees[i];
		char data = nodes[i];

		// 把当前结点作为出队结点的子结点
		TreeNode* node = new TreeNode(data);
		if (!aQueue.empty()) {
			TreeNode* pointer = aQueue.front();
			aQueue.pop();

			// 找到其空的子结点，并连接
			if (pointer->leftMostChild == NULL) {
				pointer->leftMostChild = node;
			} else {
				TreeNode* child = pointer->leftMostChild;
				while (child->rightSibling != NULL) {
					child = child->rightSibling;
				}
				child->rightSibling = node;
			}

		} else {
			root = node;
		}

		// 当前结点入队，度数为多少就入队几次
		for (int d = 0; d < degree; d++) {
			aQueue.push(node);
		}
	}

	return root;
}

int main(int argc, char *argv[]) {
	int n = 0;
	cin >> n;
	cin.get();

	TreeNode* root = NULL;
	TreeNode* subRoot = NULL;
	for (int i = 0; i < n; i++) {

		vector<char> nodes;
		vector<int> degrees;
		vector<string> splits;
		string line;
		getline(cin, line);

		SplitString(line, splits, " ");
		for (int i = 0; i < splits.size(); i+=2) {
			nodes.push_back(splits.at(i)[0]);
			degrees.push_back(splits.at(i + 1)[0] - 48);
		}

		TreeNode* tempRoot = transform(nodes, degrees);

		if (root == NULL) {
			root = tempRoot;
			subRoot = root;
		} else {
			// 子树的根结点视为兄弟结点
			subRoot->rightSibling = tempRoot;
			subRoot = tempRoot;
		}
	}

	postOrderTraverse(root);

	return 0;
}