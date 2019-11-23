#include <iostream>

using std::endl;
using std::cin;
using std::cout;

// 1：垃圾炸弹
// 别多想，就是暴力枚举
// https://www.cnblogs.com/Inkblots/p/4854052.html

struct Garbage {
	int x = 0;
	int y = 0;
	int num = 0;
};

// 垃圾点
Garbage garbages[21];
// 炸弹在每个街道爆炸所能达成的垃圾量
int street[1025][1025];

int main(int argc, char *argv[]) {
	int t = 0;
	cin >> t;

	while (t--) {

		int d = 0;
		int n = 0;
		cin >> d >> n;
		for (int j = 0; j < n; j++) {
			cin >> garbages[j].x >> garbages[j].y >> garbages[j].num;
		}

		for (int i = 0; i < 1025 ; i++){
			for (int j = 0; j < 1025 ; j++){
				street[i][j] = 0;
			}
		}
		
		int solution = 0;
		int sum = 0;
		for (int i = 0; i < n; i++) {
			// 从每个垃圾点的范围更新每个点爆炸的垃圾量
			for (int x = garbages[i].x - d; x <= garbages[i].x + d; x++) {
				if(x < 0 || x >= 1025){
					continue;
				}
				for (int y = garbages[i].y - d; y <= garbages[i].y + d; y++) {
					if (y < 0 || y >= 1025) {
						continue;
					}

					street[x][y] += garbages[i].num;
					if (sum < street[x][y]) {
						solution = 1;
						sum = street[x][y];
					} else if (sum == street[x][y]) {
						solution++;
					}
				}
			}
		}
		cout << solution << ' ' << sum << endl;
	}

	return 0;
}
