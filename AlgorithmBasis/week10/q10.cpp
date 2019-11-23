#include <iostream>
#include <algorithm>

using std::endl;
using std::cin;
using std::cout;
using std::sort;

// 10：怀表问题
// 因为k可能小于n，所以只考虑（剩余组件个数，上一个表扣类型）直接dfs，可能存在 两条路径中的子路径可能重复 的情况
// 即 多条路径的已选定部分不同，但是接下来可以选择一样的路径满足要求，所以这里的接下来的这部分路径就重复计算了
// 所以我们需要保存当前状态下的组合个数的数组

// 首尾状态(3->LL 2->LV 1->VL 0->VV)
// LL LV VL VV 的个数
long long dp[4][40][40][40][40];

// 表链长度
int k = 0;
// 表链组件个数
int n = 0;

// 剩余组件个数，剩余表扣状态
long long int dfs(int num, int chains[4], int dial) {

	// 可行性剪枝
	if (chains[0] < 0 || chains[1] < 0 || chains[2] < 0 || chains[3] < 0) {
		return 0;
	}

	// 防止重复计算
	if (dp[dial][chains[0]][chains[1]][chains[2]][chains[3]] != -1) {
		return dp[dial][chains[0]][chains[1]][chains[2]][chains[3]];
	}

	// 表链终点
	if (num == 1) {
		int left = dial >> 1;
		int right = dial & 1;
		return chains[(right << 1) + left] > 0;
	}

	// 递推公式
	// dp[LL][ll][lv][vl][vv] = dp[LL][ll-1][lv][vl][vv] + dp[LV][ll][lv-1][vl][vv]
	int temp[4] = { chains[0],chains[1],chains[2],chains[3] };
	int left = dial >> 1;
	int right = dial & 1;
	temp[(right << 1) + 1]--;
	long long dp1 = dfs(num - 1, temp, (left << 1) + 1);
	temp[(right << 1) + 1]++;
	temp[right << 1]--;
	long long dp2 = dfs(num - 1, temp, left << 1);
	dp[dial][chains[0]][chains[1]][chains[2]][chains[3]] = dp1 + dp2;

	return dp[dial][chains[0]][chains[1]][chains[2]][chains[3]];
}

int main(int argc, char *argv[]) {
	char ch = '\0';

	while (cin >> n >> k) {

		// 表盘 3->LL 2->LV 1->VL 0->VV
		int dial = 0;
		cin >> ch;
		dial |= (ch == 'L' ? 2 : 0);
		cin >> ch;
		dial |= (ch == 'L' ? 1 : 0);

		// 表链组件数目
		int chains[4] = { 0,0,0,0 };
		for (int i = 0; i < n; i++) {
			int chain = 0;
			cin >> ch;
			chain |= (ch == 'L' ? 2 : 0);
			cin >> ch;
			chain |= (ch == 'L' ? 1 : 0);

			chains[chain]++;
		}

		// 初始化
		for (int LL = 0; LL < 40; LL++) {
			for (int LV = 0; LV < 40; LV++) {
				for (int VL = 0; VL < 40; VL++) {
					for (int VV = 0; VV < 40; VV++) {
						for (int d = 0; d < 4; d++) {
							dp[d][LL][LV][VL][VV] = -1;
						}
					}
				}
			}
		}

		long long int res = dfs(k, chains, dial);
		if (res == 0) {
			cout << "NO" << endl;
		} else {
			cout << "YES" << endl;
			cout << res << endl;
		}
	}
	return 0;
}