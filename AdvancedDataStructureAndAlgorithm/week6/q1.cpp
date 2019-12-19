#include <iostream>
#include <map>
#include <string>
#include <set>

using std::endl;
using std::cin;
using std::cout;
using std::map;
using std::string;
using std::set;
using std::make_pair;

1. 倒排索引

// poj上通过,不知道为什么在cousera出现编译错误
// 在下面可以找到cousera通过的代码
// http://mypaper.pchome.com.tw/zerojudge/post/1326623527
int main(int argc, char *argv[]) {
	map<string, set<int>> inverseIndex;
	string word;

	int n = 0, c = 0, m = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> c;
		for (int j = 0; j < c; j++) {
			cin >> word;
			inverseIndex[word].insert(i);
		}
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> word;
		if (inverseIndex.find(word) != inverseIndex.end()) {
			for (set<int>::iterator it = inverseIndex[word].begin(); it != inverseIndex[word].end(); it++) {
				cout << *it << "";
			}
		} else {
			cout << "NOT FOUND";
		}
		cout << endl;
	}
	return 0;
}
