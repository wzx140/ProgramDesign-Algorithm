#include <iostream>
#include <string>

using namespace std;

// 3. 前缀中的周期

int nex[1000010];

void initNext(int len, string a) {
	nex[0] = 0;
	int k;
	for (int i = 1; i < len; i++) {
		k = nex[i - 1];
		while (a[i] != a[k] && k > 0) {
			k = nex[k - 1];
		}
		if (a[i] == a[k]) {
			nex[i] = k + 1;
		} else {
			nex[i] = 0;
		}
	}

}

int main(int argc, char *argv[]) {
	string a;

	int len;
	int index = 1;
	while (cin >> len && len != 0) {
		cin.get();	// 丢弃换行符
		getline(cin, a);
		initNext(len, a);
		cout << "Test case #" << index++ << endl;
		for (int i = 1; i < len; i++) {
			if ((i + 1) % (i + 1 - nex[i]) == 0 && nex[i] != 0) {
				cout << i + 1 << " " << (i + 1) / (i + 1 - nex[i]) << endl;
			}
		}
		cout << endl;
	}

	return 0;
}