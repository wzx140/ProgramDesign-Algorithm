#include <iostream>
#include <stdio.h> 
#include <cstring>
#include <algorithm>

using std::endl;
using std::cin;
using std::cout;
using std::strcmp;
using std::sort;

// 2. Binary Search Heap Construction
// 构建treap结构。它是一种二叉树，每个结点中含有priority(数字)和label(小写字母组成的字符串)
// 对于priority，它是最大堆；对于label，它是二叉搜索树
// 由给定数据构建treap
// 下面两条给出treap结构的实现，但是用在本题中会超时
// https://blog.csdn.net/yang_yulei/article/details/46005845
// https://zh.wikipedia.org/wiki/%E6%A0%91%E5%A0%86
// 使用以下策略
// 1. 按Treap的label把所有结点升序排列
// 2. 逐个向树中插入元素，这个时候只需要考虑后插入元素的优先级即可
//		.优先级比上一个节点优先级高：将这个结点从根结点向下调整，找到优先级稍高的结点作为其右子结点
//		.优先级比上一个节点优先级低：将这个结点设为当前节点的右子结点

char labels[50005][105];

struct Node {
	int l, r;
	int labelIndex;
	int priority;
	bool operator < (const Node &p) const {
		return strcmp(labels[labelIndex], labels[p.labelIndex]) < 0;
	}
};

int construct(Node p[50005], int n) {
	int pre = 0, root = 0;
	for (int i = 1; i < n; i++) {
		if (p[i].priority < p[pre].priority) {
			// 优先级比上一个节点优先级低
			p[pre].r = i;
		} else {
			// 优先级比根结点优先级高
			if (p[root].priority < p[i].priority) {
				int temp = root;
				root = i;
				p[root].l = temp;
			} else {
				// 从root向下调整，直至找到优先级稍高的结点
				int iter = root;
				while (p[iter].r != -1 && p[p[iter].r].priority > p[i].priority) {
					iter = p[iter].r;
				}
				int temp = p[iter].r;
				p[iter].r = i;
				// 原来的右子结点作为当前的左子结点
				p[i].l = temp;
			}
		}
		pre = i;
	}
	return root;
}

void print(int k, Node p[50005]) {
	if (k == -1) return;
	cout << "(";
	if (p[k].l != -1) {
		print(p[k].l, p);
	}
	cout << labels[p[k].labelIndex] << "/" << p[k].priority;
	if (p[k].r != -1) {
		print(p[k].r, p);
	}
	cout << ")";
}


int main(int argc, char *argv[]) {
	int n = 0;
	Node p[50005];
	while (cin >> n && n != 0) {
		// 初始化
		for (int i = 0; i < 50005; i++) {
			p[i].l = p[i].r = -1;
			p[i].labelIndex = i;
		}
		for (int i = 0; i < n; i++) {
			scanf(" %[a-z]/%d", labels[i], &p[i].priority);
		}
		sort(p, p + n);
		int root = construct(p, n);
		print(root, p);
		cout << endl;
	}
	return 0;
}