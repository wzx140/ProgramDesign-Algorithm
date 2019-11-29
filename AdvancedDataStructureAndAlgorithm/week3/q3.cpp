#include <iostream>
#include <algorithm>

using std::endl;
using std::cin;
using std::cout;
using std::stable_sort;

// 3. DNA排序

struct DNA {
	char source[100];
	int reserve = 0;
	bool operator < (const DNA &dna) const {
		return reserve < dna.reserve;
	}
}dna[150];

int main(int argc, char *argv[]) {
	int m = 0, n = 0;
	cin >> m >> n;
	for (int i = 0; i < n; i++) {
		cin >> dna[i].source;
	}
	// 计算逆序数
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m ; j++) {
			for (int k = j + 1; k < m; k++) {
				if (dna[i].source[j] > dna[i].source[k]) {
					dna[i].reserve++;
				}
			}
		}
	}
	stable_sort(dna, dna + n);

	for (int i = 0; i < n; i++) {
		cout << dna[i].source << endl;
	}
	return 0;
}