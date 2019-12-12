#include <iostream>

using std::endl;
using std::cin;
using std::cout;

// 3. 发现它，抓住它
// 与数据结构基础week7 q3食物链类似，这里更简单一点

int parent[100005];
// 与根结点的相关性，true相关，false不相关
bool tag[100005];
int count[100005];

// 路径压缩
int find(int x) {
	if (parent[x] == x) {
		return x;
	}

	int p = parent[x];
	parent[x] = find(parent[x]);
	// 自顶向下更新父子关系
	tag[x] = !(tag[p] ^ tag[x]);
	return parent[x];
}

// 加权归并
void aUnion(int x1, int x2) {
	int p1 = find(x1);
	int p2 = find(x2);
	if (count[p1] < count[p2]) {
		int temp = p1;
		p1 = p2;
		p2 = temp;
	}
	// 更新父子关系
	tag[p2] = tag[x1] ^ tag[x2];
	parent[p2] = p1;
	count[p1] += count[p2];
}

int main(int argc, char *argv[]) {
	int t = 0;
	cin >> t;
	while (t--) {
		int n = 0, m = 0;
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			tag[i] = true;
			count[i] = 1;
		}
		char flag = '\0';
		int x1 = 0, x2 = 0;
		for (int i = 0; i < m; i++) {
			cin >> flag >> x1 >> x2;
			if (flag == 'D') {
				aUnion(x1, x2);
			} else {
				int p1 = find(x1);
				int p2 = find(x2);
				if (p1 != p2) {
					cout << "Not sure yet." << endl;
				} else if (tag[x1] != tag[x2]) {
					cout << "In different gangs." << endl;
				} else if (tag[x1] == tag[x2]) {
					cout << "In the same gang." << endl;
				}
			}
		}
	}
	return 0;
}