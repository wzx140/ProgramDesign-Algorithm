#include <iostream>
#include <cmath>

using std::endl;
using std::cin;
using std::cout;

// 2. 败方树

class LoserTree {
private:
	int maxSize;			// 最大选手数
	int n;					// 选手个数
	int* ls;				// 分支结点数组(索引)
	int* b;					// 叶结点数组(外部序列的首个元素)
	int exSize;				// 最底层外部结点个数
	int offset;				// 最底层外部结点之上的结点个数
	void play(int inParent, int exLeft, int exRight);
public:
	// 败者树的分支节点数与叶结点数相等
	LoserTree(int treeSize) { ls = new int[treeSize]; this->maxSize = treeSize; }
	~LoserTree() { delete[] ls; }
	void initialize(int a[], int size);
	void replay(int i);
	int getWinner() { return n ? ls[0] : 0; }
	int* getTree() { return this->ls; }
};

// inParent:父结点索引(分支结点) exLeft:左子结点的外部序列索引 exRight：右子结点的外部序列索引
void LoserTree::play(int inParent, int exLeft, int exRight) {
	// 失败者存入父结点
	ls[inParent] = b[exLeft] > b[exRight] ? exLeft : exRight;
	int exWinner = b[exLeft] <= b[exRight] ? exLeft : exRight;

	// initialize的顺序是从左至右的外部序列两两比较，没必要对左分支和右分支处理的时候都上升比较
	// 只对右分支上升比较一次
	while (inParent > 1 && inParent % 2 != 0) {
		// 这里的完全二叉树是从b[1]开始的，所以父结点为 p/2
		int temp = b[exWinner] <= b[ls[inParent / 2]] ? exWinner : ls[inParent / 2];
		// 胜者每次与父结点比较
		ls[inParent / 2] = b[exWinner] > b[ls[inParent / 2]] ? exWinner : ls[inParent / 2];
		// 胜者向上传递
		exWinner = temp;
		inParent /= 2;
	}
	// 把胜者存到祖父结点，等待下一次右分支的胜者与其比较
	// inParent=1时,ls[0]=winner
	ls[inParent / 2] = exWinner;
}

void LoserTree::initialize(int a[], int size) {

	if (size < 2 || size > maxSize) {
		// 出错，抛出异常
		return;
	}

	this->n = size;
	this->b = a;

	// 计算最底层外部结点个数
	this->exSize = 2 * n - pow(2, int(log(2 * n) / log(2)));

	// 为了便于计算最底层外部结点的父结点索引，所以求offset
	this->offset = pow(2, int(log(2 * n) / log(2)));

	// 最底层和次底层的外部结点需要分开处理，以应对内部节点和外部结点比较的情况
	// 以及确定父结点位置
	for (int i = 1; i < this->exSize; i += 2) {
		play((i + offset) / 2, i - 1, i);
	}
	int start = this->exSize + 1;
	if (n % 2 != 0) {
		play((n - 1) / 2, ls[(n - 1) / 2], this->exSize);
		// 次底层的外部结点有一个与内部结点比较了
		// 所以次底层的结点间比较的起始点+1
		start++;
	}
	for (int i = start; i < n; i += 2) {
		play((i - this->exSize + n - 1) / 2, i - 1, i);
	}

}

// 第i个外部叶结点改变了
void LoserTree::replay(int i) {
	if (i < 0 || i > this->n) {
		// 出错，抛出异常
		return;
	}

	// 父结点位置
	int inParent = 0;
	if (i < this->exSize) {
		inParent = (i + offset) / 2;
	} else {
		inParent = (i - this->exSize + n) / 2;
	}

	int exWinner = b[i] <= b[ls[inParent]] ? i : ls[inParent];
	ls[inParent] = b[i] > b[ls[inParent]] ? i : ls[inParent];
	while (inParent / 2 >= 1) {
		int temp = b[exWinner] <= b[ls[inParent / 2]] ? exWinner : ls[inParent / 2];
		ls[inParent / 2] = b[exWinner] > b[ls[inParent / 2]] ? exWinner : ls[inParent / 2];
		exWinner = temp;
		inParent /= 2;
	}
	ls[0] = exWinner;
}

int main(int argc, char *argv[]) {
	int n = 0, m = 0;
	cin >> n >> m;
	int* b = new int[n];
	// 败方树
	int* ls;
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	LoserTree loserTree(n);
	loserTree.initialize(b, n);
	ls = loserTree.getTree();
	for (int i = 0; i < n; i++) {
		cout << b[ls[i]] << ' ';
	}
	cout << endl;
	for (int i = 0; i < m; i++) {
		int index = 0;
		cin >> index;
		cin >> b[index];
		loserTree.replay(index);
		for (int i = 0; i < n; i++) {
			cout << b[ls[i]] << ' ';
		}
		cout << endl;
	}

	return 0;
}