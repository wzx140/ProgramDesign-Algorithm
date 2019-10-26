#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 3. 文本二叉树

struct BinaryTreeNode {
	char data;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode(char x) : data(x), left(NULL), right(NULL) {}
};

void preOrderTraverse(BinaryTreeNode* T) {
	if (T == NULL) {
		return;
	}
	cout << T->data;
	preOrderTraverse(T->left);
	preOrderTraverse(T->right);
}

void inOrderTraverse(BinaryTreeNode* T) {
	if (T == NULL) {
		return;
	}

	inOrderTraverse(T->left);
	cout << T->data;
	inOrderTraverse(T->right);
}

void postOrderTraverse(BinaryTreeNode* T) {
	if (T == NULL) {
		return;
	}
	postOrderTraverse(T->left);
	postOrderTraverse(T->right);
	cout << T->data;
}

BinaryTreeNode* buildTree(vector<char>& elems, vector<int>& layers, int parentLayer, int& currentIndex) {

	if (currentIndex > elems.size() - 1) {
		return NULL;
	}

	int layer = layers[currentIndex];
	char data = elems[currentIndex];
	if (layer - 1 != parentLayer) {
		// 找不到子结点
		return NULL;
	}
	if (data == '*') {
		// 空左结点
		currentIndex += 1;
		return NULL;
	}

	BinaryTreeNode* root = new BinaryTreeNode(elems[currentIndex]);
	currentIndex += 1;
	root->left = buildTree(elems, layers, layer, currentIndex);
	root->right = buildTree(elems, layers, layer, currentIndex);

	return root;
}

int main(int argc, char *argv[]) {
	int n = 0;
	cin >> n;
	while (n--) {
		string line;
		// 存储结点值
		vector<char> elems;
		// 存储结点层数
		vector<int> layers;

		while (cin >> line && line != "0") {
			elems.push_back(line[line.size() - 1]);
			layers.push_back(line.size() - 1);
		}

		int index = 0;
		BinaryTreeNode* root = buildTree(elems, layers, -1, index);

		preOrderTraverse(root);
		cout << endl;
		postOrderTraverse(root);
		cout << endl;
		inOrderTraverse(root);
		cout << endl << endl;
	}

	vector<char> elems;

	return 0;
}