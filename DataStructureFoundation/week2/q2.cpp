#include <map>
#include <iostream>
#include <functional>

using namespace std;

// 2. 多项式加法

int main() {
	int n;
	cin >> n;
	while (n--) {
		map <int, int, greater<int> > poly;

		// 读入多项式，第二次读入时求和
		int i = 2;
		while (i--) {
			while (1) {
				int degree = 0;
				int coefficient = 0;
				cin >> coefficient;
				cin >> degree;

				if (degree < 0) {
					break;
				}

				if (coefficient == 0) {
					continue;
				}

				if (poly.find(degree) != poly.end()) {
					poly[degree] += coefficient;
				} else {
					poly.insert(make_pair(degree, coefficient));
				}
			}
		}

		for (map<int, int>::iterator it = poly.begin(); it != poly.end(); it++) {
			if (it->second != 0) {
				cout << "[ " << it->second << ' ' << it->first << " ] ";
			}
		}

		cout << endl;
	}
}