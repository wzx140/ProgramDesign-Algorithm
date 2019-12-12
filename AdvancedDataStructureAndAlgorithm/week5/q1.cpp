#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using std::endl;
using std::cin;
using std::cout;
using std::sort;
using std::strcmp;
using std::getchar;
using std::scanf;
using std::printf;

// 1. 词典
// 根据题目建议使用了c语言的io，在vs2017会有warning，在预编译命令中加入_CRT_SECURE_NO_WARNINGS可消除warning
// 以下使用快排+二分，直接使用map也可以

struct Entry {
	char forigen[12];
	char english[12];
	bool operator < (const Entry &entry) const {
		return strcmp(forigen, entry.forigen) < 0;
	}
};

Entry dict[100005];
int dictSize = 0;

int binarySearch(char target[12]) {
	int res = -1;
	int left = 0;
	int right = dictSize - 1;
	int middle = 0;
	while (left <= right) {
		int middle = (right - left) / 2 + left;
		if (strcmp(dict[middle].forigen, target) < 0) {
			left = middle + 1;
		} else if (strcmp(dict[middle].forigen, target) > 0) {
			right = middle - 1;
		} else {
			res = middle;
			break;
		}
	}
	return res;
}

int main(int argc, char *argv[]) {
	dictSize = 0;
	while (true) {
		char initChar = getchar();
		if (initChar == '\n') {
			break;
		}
		dict[dictSize].english[0] = initChar;
		scanf("%s %s", dict[dictSize].english + 1, dict[dictSize].forigen);
		getchar();
		dictSize++;
	}

	sort(dict, dict + dictSize);

	char target[12];
	while (scanf("%s", target) != EOF) {
		
		int res = binarySearch(target);
		if (res != -1) {
			printf("%s\n", dict[res].english);
		} else {
			printf("eh\n");
		}
	}
	return 0;
}