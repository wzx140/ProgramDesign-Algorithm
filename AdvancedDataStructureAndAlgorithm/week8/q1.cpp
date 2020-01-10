#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::endl;
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::sort;
using std::min;
using std::max;

// 1. Shortest Prefixes
// 定义单词前缀为非空的字符串，包括单词本身
// 输入2~1000行单词，找出每个单词的最短前缀(不产生歧义)
// 注：单词car不会对carriage产生歧义，car会被识别为car而不是carriage

struct Word {
	string data;
	int prefix = -1;
}words[1005];

bool cmp(Word* a, Word* b) {
	return a->data < b->data;
}

int main(int argc, char *argv[]) {

	int count = 0;
	// 以指针形式保存数组，防止words数组顺序变化
	Word* pointer[1005];
	while (cin >> words[count].data) {
		pointer[count] = &words[count];
		count++;
	}
	sort(pointer, pointer + count, cmp);

	// 每个字符串与左右两个字符串比较，当前最长的前缀即为全局最长的前缀
	int pos1 = 0, pos2 = 0;
	for (int i = 0; i < count - 1; i++) {
		// 上一次比较中word_i与word_i+1的最长前缀位置，可以当做本次word_i与word_i-1比较的结果
		pos1 = pos2;

		int length = min(pointer[i]->data.size(), pointer[i + 1]->data.size());
		for (pos2 = 0; pos2 < length; pos2++) {
			if (pointer[i]->data[pos2] != pointer[i + 1]->data[pos2]) {
				break;
			}
		}
		pointer[i]->prefix = max(pos1, pos2);
	}
	pointer[count - 1]->prefix = pos2;

	for (int i = 0; i < count; i++) {
		int prefix = words[i].prefix;
		if (prefix >= words[i].data.size()) {
			cout << words[i].data << ' ' << words[i].data << endl;
		} else {
			cout << words[i].data << ' ' << words[i].data.substr(0, prefix + 1) << endl;
		}
	}

	return 0;
}