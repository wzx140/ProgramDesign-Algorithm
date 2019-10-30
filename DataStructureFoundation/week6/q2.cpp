#include <iostream>
#include <stack>

using namespace std;

// 2. 二叉搜索树

struct BinaryTreeNode {
	int data;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode(int x) : data(x), left(NULL), right(NULL) {}
};

void insert(BinaryTreeNode* root, int num) {

	if (num < root->data) {
		if (root->left == NULL) {
			root->left = new BinaryTreeNode(num);
		} else {
			insert(root->left, num);
		}
	} else if(num > root->data){
		if (root->right == NULL) {
			root->right = new BinaryTreeNode(num);
		} else {
			insert(root->right, num);
		}
	} else {
		return;
	}
}

void preOrderTraverse(BinaryTreeNode* T) {
	if (T == NULL) {
		return;
	}
	cout << T->data << " ";
	preOrderTraverse(T->left);
	preOrderTraverse(T->right);
}

int main(int argc, char *argv[]) {

	BinaryTreeNode* root = NULL;
	int num = 0;
	while (cin >> num) {
		if (root == NULL) {
			root = new BinaryTreeNode(num);
		} else {
			insert(root, num);
		}

		if (cin.get() == '\n') {
			break;
		}
	}
	preOrderTraverse(root);

	return 0;
}