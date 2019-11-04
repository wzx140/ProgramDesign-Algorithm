#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// 3. 食物链

// 运用并查集的思想
// 参考	https://blog.csdn.net/freezhanacmore/article/details/8767413
// 这里添加了rank属性
// 0表示与根结点是同类
// 1表示它吃根结点
// 2表示根结点吃它

// 父指针索引序列
int parents[50000];
int rank[50000];
// 集合中结点的数量
int amount[50000];

int n = 0;
int k = 0;

// 查找
int find(int x) {

	if (x == parents[x]) {
		return x;
	}

	int temp = parents[x];
	// 路径压缩
	parents[x] = find(parents[x]);
	// 更新父子关系
	rank[x] = (rank[temp] + rank[x]) % 3;
	return parents[x];
}

// 归并
void aUnion(int x, int y, int d) {
	int root1 = find(x);
	int root2 = find(y);

	if (root1 != root2) {
		// 加权归并
		int count1 = amount[root1];
		int count2 = amount[root2];
		// 交换
		if (count1 < count2) {
			int temp = root1;
			root1 = root2;
			root2 = temp;
			temp = x;
			x = y;
			y = temp;
			d = (d == 2) ? (d + 1) : d;
		}
		// 归并
		parents[root2] = root1;
		// 更新父子关系
		rank[root2] = (rank[x] - rank[y] + 2 + d) % 3;
		amount[root1] += amount[root2];
	}
}

int main(int argc, char *argv[]) {
	cin >> n;
	cin >> k;

	// 初始化
	for (int i = 0; i < n; i++) {
		parents[i] = i;
		rank[i] = 0;
		amount[i] = 1;
	}

	// 说谎次数
	int count = 0;

	while (k--) {
		int d = 0;
		int x = 0;
		int y = 0;
		cin >> d >> x >> y;

		if (x > n || y > n || (d == 2 && x == y)) {
			count++;
		} else {

			if (find(x) == find(y)) {
				if (d == 1 && (rank[x] != rank[y])) {
					count++;

				} else if (d == 2 &&
					((rank[x] + 1) % 3 != rank[y])) {
					count++;
				}

			} else {
				aUnion(x, y, d);
			}
		}
	}

	cout << count << endl;
	return 0;
}