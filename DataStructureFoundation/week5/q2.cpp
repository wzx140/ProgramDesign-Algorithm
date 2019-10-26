#include <iostream>
#include <vector>

using namespace std;

// 2. 实现堆结构
// 实现一个最小堆，第6周的课中有讲解

class MinHeap {
private:
	// 存储完全二叉树的数组
	int* heapArray;
	// 当前存储元素数量
	int size;
	// 最大空间
	int maxSize;
	// 向上调整
	void siftUp(int position);
	// 向下调整
	void siftDown(int position);
public:
	MinHeap(int n);
	// 建堆
	~MinHeap();
	void buildHeap();
	bool pop();
	bool push(int value);
	int top() const;
};

void MinHeap::buildHeap() {
	for (int i = this->size / 2 - 1; i >= 0; i--) {
		this->siftDown(i);
	}
}

void MinHeap::siftUp(int position) {
	int child = position;
	// 父结点
	int parent = (child - 1) / 2;
	// 当前值暂存
	int temp = this->heapArray[child];

	while (child > 0) {

		if (temp < this->heapArray[parent]) {
			// 比暂存值大的结点都向下传播一层
			this->heapArray[child] = this->heapArray[parent];

			// 向上层继续
			child = parent;
			parent = (child - 1) / 2;
		} else {
			break;
		}
	}

	// 最后再将暂存值放在合适位置
	this->heapArray[child] = temp;
}

void MinHeap::siftDown(int position) {
	int parent = position;
	// 左子结点
	int child = 2 * parent + 1;
	// 当前值暂存
	int temp = this->heapArray[parent];

	while (child < this->size) {
		// 取左右子结点中较小的一个
		if (child < this->size - 1 && this->heapArray[child] > this->heapArray[child + 1]) {
			child = child + 1;
		}

		if (temp > this->heapArray[child]) {
			// 比暂存值小的结点都向上传播一层
			this->heapArray[parent] = this->heapArray[child];

			// 向下层继续
			parent = child;
			child = 2 * parent + 1;
		} else {
			break;
		}
	}

	// 最后再将暂存值放在合适位置
	this->heapArray[parent] = temp;
}

MinHeap::MinHeap(int n) {
	this->heapArray = new int[n];
	this->maxSize = n;
	this->size = 0;
}

MinHeap::~MinHeap() {
	delete this->heapArray;
}

bool MinHeap::pop() {
	if (this->size <= 0) {
		return false;
	}
	this->heapArray[0] = this->heapArray[--this->size];
	this->siftDown(0);
	return true;
}

bool MinHeap::push(int value) {
	if (this->size == this->maxSize) {
		return false;
	}
	this->heapArray[size++] = value;
	this->siftUp(size - 1);
	return true;
}

int MinHeap::top() const {
	if (size > 0) {
		return this->heapArray[0];
	} else {
		// 应抛出异常
		return -1;
	}
}

int main(int argc, char *argv[]) {

	int t = 0;
	int n = 0;
	int type = 0;
	int num = 0;
	cin >> t;

	while (t--) {
		cin >> n;
		MinHeap minHeap(n);
		while (n--) {
			cin >> type;
			if (type == 1) {
				cin >> num;
				minHeap.push(num);
			} else if (type == 2) {
				cout << minHeap.top() << endl;
				minHeap.pop();
			}
		}
	}

	return 0;
}