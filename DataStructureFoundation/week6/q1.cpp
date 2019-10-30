#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

// 1. Huffman编码树

int main(int argc, char *argv[]) {
	int n = 0;
	cin >> n;

	priority_queue<int, vector<int>, greater<int> > weights;
	while (n--) {
		int weight = 0;
		cin >> weight;
		weights.push(weight);
	}

	// 这里并不需要先建立哈夫曼编码树，再遍历计算
	int sum = 0;
	while (weights.size() != 1) {
		// 每次拿出两个最小的两个元素，放入他们的和，并排序
		int w1 = weights.top();
		weights.pop();
		int w2 = weights.top();
		weights.pop();
		int w3 = w1 + w2;
		weights.push(w3);

		// 因为每个分支结点都是由叶结点向上累加而成的
		// 路径权值和就是所有分支结点的和
		sum += w3;
	}

	cout << sum << endl;

	return 0;
}