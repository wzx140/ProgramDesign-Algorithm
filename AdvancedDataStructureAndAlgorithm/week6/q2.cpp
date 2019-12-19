#include <iostream>
#include <set>

using std::endl;
using std::cin;
using std::cout;
using std::set;

// 2.倒排索引查询

// poj上通过,不知道为什么在cousera出现编译错误
// 在下面可以找到cousera通过的代码
// http://mypaper.pchome.com.tw/zerojudge/post/1326623527
int main(int argc, char *argv[]) {
	set<int> bitMap[100];
	int n = 0, m = 0, c = 0, index = 0, op = 0;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> c;
		for (int j = 0; j < c; j++) {
			cin >> index;
			bitMap[i].insert(index);
		}
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		// res保存相交的结果，inverse保存不出现的文档编号
		set<int> res, inverse;
		bool flag = true;

		for (int j = 0; j < n; j++) {
			cin >> op;
			if (op == 1 && !flag) {
				for (set<int>::iterator it = res.begin(); it != res.end();) {
					if (bitMap[j].find(*it) == bitMap[j].end()) {
						it = res.erase(it);
					} else {
						it++;
					}
				}
			} else if (op == 1 && flag) {
				// 首次取交集
				for (set<int>::iterator it = bitMap[j].begin(); it != bitMap[j].end(); it++) {
					res.insert(*it);
				}
				flag = false;
			} else if (op == -1) {
				for (set<int>::iterator it = bitMap[j].begin(); it != bitMap[j].end(); it++) {
					inverse.insert(*it);
				}
			}
		}
		for (set<int>::iterator it = inverse.begin(); it != inverse.end(); it++) {
			res.erase(*it);
		}
		// 输出
		if (res.empty()) {
			cout << "NOT FOUND" << endl;
		} else {
			for (set<int>::iterator it = res.begin(); it != res.end(); it++) {
				cout << *it << " ";
			}
			cout << endl;
		}
	}
	return 0;
}
