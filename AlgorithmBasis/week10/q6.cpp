#include <iostream>
#include <queue>

using std::endl;
using std::cin;
using std::cout;
using std::queue;

// 6：献给阿尔吉侬的花束

struct State {
	int time = 0;
	int x = 0, y = 0;
};

// 上下左右
int dir[4][2] = { {0,1} ,{0,-1} ,{-1,0} ,{1,0} };

// 迷宫大小
int r = 0, c = 0;

// 迷宫,这里visted和迷宫放在一起
bool visit[300][300];

// 记录open1与open2中的元素
int exist1[300][300];
int exist2[300][300];

int expand(State state, queue<State>& open, int exist1[300][300], int exist2[300][300]) {

	for (int i = 0; i < 4; i++) {
		int newX = state.x + dir[i][0];
		int newY = state.y + dir[i][1];

		// 超出边界
		if (newX < 0 || newX >= c || newY < 0 || newY >= r) {
			continue;
		}

		// 找到交集
		if (exist2[newX][newY] >= 0) {
			return state.time + 1 + exist2[newX][newY];
		}

		// 已走过或者有墙
		if (visit[newX][newY]) {
			continue;
		}

		State newState;
		newState.x = newX;
		newState.y = newY;
		newState.time = state.time + 1;

		visit[newX][newY] = true;
		exist1[newX][newY] = newState.time;
		open.push(newState);
	}

	return -1;
}

// 双向广搜
int dbfs(State& begin, State& end) {

	if (begin.x == end.x && begin.y == end.y) {
		return 0;
	}

	for (int i = 0; i < c ; i++){
		for (int j = 0; j < r ; j++){
			exist1[i][j] = -1;
			exist2[i][j] = -1;
		}
	}

	queue<State> open1;
	queue<State> open2;
	open1.push(begin);
	open2.push(end);
	exist1[begin.x][begin.y] = 0;
	exist2[end.x][end.y] = 0;

	while (!open1.empty() || !open2.empty()) {

		// 判断该拓展哪一边
		bool open1EX = true;
		if (open1.empty()) {
			open1EX = false;
		} else if (open2.empty()) {
			open1EX = true;
		} else if (open1.size() <= open2.size()) {
			open1EX = true;
		} else {
			open1EX = false;
		}

		if (open1EX) {
			// 拓展正向队列
			State state = open1.front();
			open1.pop();
			int res = expand(state, open1, exist1, exist2);
			if (res != -1) {
				return res;
			}
		} else {
			// 拓展反向队列
			State state = open2.front();
			open2.pop();
			int res = expand(state, open2, exist2, exist1);
			if (res != -1) {
				return res;
			}
		}
	}

	return -1;
}

//// 单向广搜
//int bfs(State& begin, State& end) {
//
//	queue<State> open;
//	open.push(begin);
//
//	while (!open.empty()) {
//
//		State state = open.front();
//		open.pop();
//
//		for (int i = 0; i < 4; i++) {
//			int newX = state.x + dir[i][0];
//			int newY = state.y + dir[i][1];
//
//			// 超出边界
//			if (newX < 0 || newX >= c || newY < 0 || newY >= r) {
//				continue;
//			}
//
//			// 找到奶酪
//			if (newX == end.x && newY == end.y) {
//				return state.time + 1;
//			}
//
//			// 已走过或者有墙
//			if (maze[newX][newY]) {
//				continue;
//			}
//
//			State newState;
//			newState.x = newX;
//			newState.y = newY;
//			newState.time = state.time + 1;
//
//			maze[newX][newY] = true;
//			open.push(newState);
//		}
//	}
//
//	return -1;
//}

int main(int argc, char *argv[]) {
	int t = 0;
	cin >> t;
	while (t--) {
		cin >> r >> c;

		State begin;
		State end;

		char ch = '\0';
		for (int j = 0; j < r; j++) {
			for (int i = 0; i < c; i++) {
				cin >> ch;
				if (ch == 'S') {
					begin.x = i;
					begin.y = j;
					visit[i][j] = true;
				} else if (ch == 'E') {
					end.x = i;
					end.y = j;
					visit[i][j] = true;
				} else {
					visit[i][j] = ch == '#';
				}
			}
		}

		int res = dbfs(begin, end);
		if (res == -1) {
			cout << "oop!" << endl;
		} else {
			cout << res << endl;
		}
	}

	return 0;
}