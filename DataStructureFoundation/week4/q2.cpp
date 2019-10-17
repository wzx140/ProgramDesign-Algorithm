#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 2. 拼写检查

// 0->相等 1->相似 -1->不相似
int check(string pattern, string word) {

	int length1 = word.size();
	int length2 = pattern.size();

	if (length1 == length2) {

		int diff = 0;
		for (int j = 0; j < length1; j++) {
			if (word[j] != pattern[j]) {
				diff++;
			}
			// 多余一个字符不相等
			if (diff > 1) {
				return -1;
			}
		}

		if (diff == 0) {
			// 所有字母都相同
			return 0;
		} else if (diff == 1) {
			// 只有一个字母不相同，相似
			return 1;
		}

	} else if (length1 - length2 == 1) {
		// 删除word中的一个字符与pattern比较
		// 在遇到不相等的字符时，pattern的index停止移动一次(相当于word删去一个字符)
		int index1 = 0;
		int index2 = 0;
		int flag = false;	// 是否进行过删除字符操作
		for (; index1 < length1, index2 < length2; index1++, index2++) {
			if (word[index1] != pattern[index2]) {
				if (flag) {
					return -1;
				} else {
					// word中删去一个字符
					index2--;
					flag = true;
				}
			}
		}

		return 1;

	} else if (length1 - length2 == -1) {
		// 删除pattern中的一个字符与word比较
		// 在遇到不相等的字符时，word的index停止移动一次(相当于pattern删去一个字符)
		int index1 = 0;
		int index2 = 0;
		bool flag = false;	// 是否进行过删除字符操作
		for (; index1 < length1, index2 < length2; index1++, index2++) {
			if (word[index1] != pattern[index2]) {
				if (flag) {
					return -1;
				} else {
					// pattern中删去一个字符
					index1--;
					flag = true;
				}
			}
		}

		return 1;

	} else {
		return -1;
	}
}

int main(int argc, char *argv[]) {
	vector<string> dict;

	// 读入字典
	string word = "";
	while (getline(cin, word) && word != "#") {
		dict.push_back(word);
	}

	int n = dict.size();

	// 读入单词
	while (getline(cin, word) && word != "#") {
		if (!word.empty()) {

			vector<int> similarity;

			int res = -1;
			for (int i = 0; i < n; i++) {
				res = check(dict[i], word);
				if (res == 0) {
					cout << word << " is correct" << endl;
					break;

				} else if (res == 1) {
					similarity.push_back(i);
				}
			}

			if (res != 0) {
				cout << word << ": ";
				for (int j = 0; j < similarity.size(); j++) {
					cout << dict[similarity[j]] << " ";
				}
				cout << endl;
			}
		}
	}

	return 0;
}