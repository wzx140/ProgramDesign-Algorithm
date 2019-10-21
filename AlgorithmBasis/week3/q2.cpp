#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 2： 文件结构“图”

string split = "|     ";

// 先输出目录，文件暂存，排序后输出
// index用引用传递是防止目录文件重复输出
void recursive(vector<string> &files, vector<string> &cache, int &index, int level) {

	// 递归终点
	if (index >= files.size()) {
		return;
	}

	string file = files[index];
	int n = files.size();

	if (file[0] == 'f') {

		// 缓存文件
		cache.push_back(file);

	} else if (file[0] == 'd'|| file == "ROOT") {
		// 进目录
		level++;
		// 打印目录
		for (int i = 0; i < level; i++) {
			cout << split;
		}
		cout << file << endl;

		// 新建缓存，递归目录
		vector<string> newCache;
		index += 1;
		for (; index < n&&files[index] != "]"; index++) {
			string subFile = files[index];
			if (subFile[0] == 'd') {
				// 下一级目录
				// index引用传递防止当前目录遍历子目录下的文件，造成重复输出
				recursive(files, newCache, index, level);

			} else if (subFile[0] == 'f') {
				int newIndex = index;
				recursive(files, cache, newIndex, level);
			}

		}

		// 打印目录内文件
		recursive(files, cache, index, level);
		cache.clear();

		// 出目录
		level--;

	} else if (file == "]") {
		// 目录到底

		// 升序排列后,打印
		sort(cache.begin(), cache.end());
		for (int i = 0; i < cache.size(); i++) {
			// 文件
			for (int j = 0; j < level; j++) {
				cout << split;
			}
			cout << cache[i] << endl;
		}
	}

}

int main(int argc, char *argv[]) {

	string file;
	int index = 1;
	while (getline(cin, file) && file != "#") {

		vector<string> files;	// 输入数据
		vector<string> cache;	// 暂存数据(文件)
		while (file != "*") {
			files.push_back(file);
			getline(cin, file);
		}
		cout << "DATA SET " << index++ << ":" << endl;

		// 添加ROOT根目录，便于遍历
		files.insert(files.begin(), "ROOT");
		files.push_back("]");

		int index = 0;
		recursive(files, cache, index, -1);
		cout << endl;
	}

	return 0;
}