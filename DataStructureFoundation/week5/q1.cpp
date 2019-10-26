#include <iostream>
#include <vector>

using namespace std;

// 1. 由中根序列和后根序列重建二叉树
// 后根序列的最后一个元素是根结点,中根序列的最后一个元素是根结点的右子结点
// 中根序列={左子树的中根序列+根结点+右子树的中根序列}
// 后跟序列={左子树的后根序列+右子树的后根序列+根结点}

struct BinaryTreeNode {
	int data;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode(int x) : data(x), left(NULL), right(NULL) {}
};

int inOrder[65536];
int postOrder[65536];

BinaryTreeNode* buildTree(int inBegin, int inEnd, int postBegin, int postEnd) {
	// 找到根结点
	BinaryTreeNode* root = new BinaryTreeNode(postOrder[postEnd]);

	// 寻找左右子树的分割点
	int split = 0;
	for (split = inBegin; split <= inEnd; split++) {
		if (root->data == inOrder[split]) {
			break;
		}
	}

	// 左子树序列长度
	int lLength = split - inBegin;
	// 右子树序列长度
	int rLength = inEnd - split;

	// 左子树不为空
	if (lLength > 0) {
		root->left = buildTree(inBegin, split - 1, postBegin, postBegin + lLength - 1);
	}

	// 右子树不为空
	if (rLength > 0) {
		root->right = buildTree(split + 1, inEnd, postBegin + lLength, postEnd - 1);
	}

	return root;
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
	int n = 0;
	int value = 0;
	// 中根序列
	while (cin >> inOrder[n++]) {
		if (cin.get() != ' ') {
			break;
		}
	};

	n = 0;
	// 后根序列
	while (cin >> postOrder[n++]) {
		if (cin.get() != ' ') {
			break;
		}
	}

	preOrderTraverse(buildTree(0, n - 1, 0, n - 1));

	return 0;
}