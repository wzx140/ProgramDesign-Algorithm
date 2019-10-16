#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// 1. 密码翻译

string lowerLetters = "bcdefghijklmnopqrstuvwxyza";
string upperLetters = "BCDEFGHIJKLMNOPQRSTUVWXYZA";

int main(int argc, char *argv[]) {
	int n = 0;
	cin >> n;
	cin.get();	// 丢弃换行符

	for (int i = 0; i < n; i++) {
		char str[100];
		cin.getline(str, 100);

		for (int j = 0; j < strlen(str); j++) {
			int ch = str[j];

			if (ch >= 65 && ch <= 90) {
				str[j] = upperLetters[ch - 65];
			} else if (ch >= 97 && ch <= 122) {
				str[j] = lowerLetters[ch - 97];
			}
		}
		cout << str << endl;
	}
	return 0;
}