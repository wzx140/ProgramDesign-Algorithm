#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::set_difference;
using std::set_intersection;
using std::set_union;
using std::inserter;
using std::sort;

// 2. 集合运算

int main(int argc, char *argv[]) {
	vector<int> a;
	vector<int> b;
	int n = 0, m = 0, num = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num;
		a.push_back(num);
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> num;
		b.push_back(num);
	}

	vector<int> a_b;
	vector<int> b_a;
	vector<int> res;
	set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(a_b, a_b.begin()));
	set_difference(b.begin(), b.end(), a.begin(), a.end(), std::inserter(b_a, b_a.begin()));
	set_union(a_b.begin(), a_b.end(), b_a.begin(), b_a.end(), std::inserter(res, res.begin()));
	sort(res.begin(), res.end());

	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << ' ';
	}

	return 0;
}