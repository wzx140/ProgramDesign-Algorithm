#include <iostream>

using namespace std;

// 1. 约瑟夫问题

// 使用循环链表存储猴子序号
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

int main(int argc, char *argv[]) {
	int n = 0;
	int m = 0;
	cin >> n;
	cin >> m;

	// 初始化猴子线性表
	ListNode* temp = new ListNode(0);
	ListNode* tail = temp;
	ListNode* head = temp;
	for (int i = 1; i < n + 1; i++) {
		temp->next = new ListNode(i);
		temp = temp->next;
		tail = temp;
	}
	// 去除首部无效节点
	head = head->next;
	// 首尾相接
	tail->next = head;

	// 循环报数
	ListNode* curr = head;
	ListNode* pre = tail;
	while (pre != curr) {

		int cycle = m - 1;
		while (cycle != 0) {
			curr = curr->next;
			pre = pre->next;
			cycle--;
		}

		// 删除节点
		pre->next = curr->next;
		ListNode* temp = curr->next;
		delete curr;
		curr = temp;
	}

	cout << curr->val;
	return 0;
}