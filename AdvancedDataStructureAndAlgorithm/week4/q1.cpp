#include <iostream>
#include <queue>
#include <vector>

using std::endl;
using std::cin;
using std::cout;
using std::vector;

int heapArray[1000];
int m = 0;
int n = 0;

// 1. 置换选择排序

void SiftDown(int position) {
	int parent = position;
	// 左子结点
	int child = 2 * parent + 1;
	// 当前值暂存
	int temp = heapArray[parent];

	while (child < n) {
		// 取左右子结点中较小的一个
		if (child < n - 1 && heapArray[child] > heapArray[child + 1]) {
			child = child + 1;
		}

		if (temp > heapArray[child]) {
			// 比暂存值小的结点都向上传播一层
			heapArray[parent] = heapArray[child];

			// 向下层继续
			parent = child;
			child = 2 * parent + 1;
		} else {
			break;
		}
	}

	// 最后再将暂存值放在合适位置
	heapArray[parent] = temp;
}

int main(int argc, char *argv[]) {
	cin >> m >> n;

	vector<int> numArray;
	for (int i = 0; i < m; i++) {
		int num = 0;
		cin >> num;
		numArray.push_back(num);
	}
	for (int i = 0; i < n; i++) {
		cin >> heapArray[i];
	}

	vector<int> res;
	int readIndex = 0;
	while (n > 0 && readIndex < m) {
		int minValue = heapArray[0];
		res.push_back(minValue);

		int elem = numArray[readIndex++];
		if (elem >= minValue) {
			heapArray[0] = elem;
			SiftDown(0);
		} else {
			heapArray[0] = heapArray[n - 1];
			SiftDown(0);
			n--;
		}

	}

	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << ' ';
	}
	return 0;
}