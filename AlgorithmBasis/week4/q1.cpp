#include <iostream>
#include <vector>
#include <map>

using namespace std;

// 1：集合加法
// 哈希查找，将集合的数以 值-该值的数量 的方式存入哈希表
// 遍历某个集合a，在另一个集合中查找 sum - a[i]，单个查找的时间复杂度为 O(1)
// 如果存在重复的值，是不适用哈希查找的，但本题只需返回符合要求的个数，并不要求返回两个数的索引

int search(map<int, int>& a, map<int, int>& b, int sum) {
	int count = 0;

	if (a.size() < b.size()) {
		map<int, int>::iterator iter = a.begin();
		while (iter != a.end()) {
			if (b.find(sum - iter->first) != b.end()) {
				// 两个集合符合要求的值的个数乘积
				count += iter->second * b[sum - iter->first];
			}
			iter++;
		}
	} else {
		map<int, int>::iterator iter = b.begin();
		while (iter != b.end()) {
			if (a.find(sum - iter->first) != a.end()) {
				// 两个集合符合要求的值的个数乘积
				count += iter->second * a[sum - iter->first];
			}
			iter++;
		}
	}

	return count;
}

int main(int argc, char *argv[]) {
	int n = 0;
	cin >> n;

	while (n--) {
		int sum = 0;
		cin >> sum;

		int setLength = 0;

		// 集合A
		cin >> setLength;
		map<int,int> a;
		while (setLength--) {
			int num = 0;
			cin >> num;
			a[num]++;
		}

		// 集合B
		cin >> setLength;
		map<int,int> b;
		while (setLength--) {
			int num = 0;
			cin >> num;
			b[num]++;
		}

		cout << search(a, b, sum) << endl;

	}
	return 0;
}