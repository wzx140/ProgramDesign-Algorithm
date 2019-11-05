#include <iostream>
#include <queue>
#include <bitset>

using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::bitset;

// 1：Flip Game
// 在4x4的方格上，翻转棋子(黑->白，白->黑)
// 每次邻近的四个棋子也会被翻动(如果有的话)
// 最短几次可以全黑或者全白

// unsigned short类型 16位，正好可以存储16个格子的状态

struct State {
	unsigned short board;
	int count;
	State(unsigned short tBoard, int tCount) :board(tBoard), count(tCount) {}
};

bool getPiece(unsigned short board, int i, int j) {
	return !((board & (1 << i * 4 + j)) == 0);
}

// test
//void print(unsigned short board) {
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			bool piece = getPiece(board, i, j);
//			if (piece) {
//				cout << 'w';
//			} else {
//				cout << 'b';
//			}
//		}
//		cout << endl;
//	}
//}

void flipOne(unsigned short& board, int i, int j) {
	if (getPiece(board, i, j)) {
		board -= 1 << i * 4 + j;
	} else {
		board += 1 << i * 4 + j;
	}
}

unsigned short flip(unsigned short board, int i, int j) {
	flipOne(board, i, j);

	if (i > 0) {
		flipOne(board, i - 1, j);
	}

	if (i < 3) {
		flipOne(board, i + 1, j);
	}

	if (j > 0) {
		flipOne(board, i, j - 1);
	}

	if (j < 3) {
		flipOne(board, i, j + 1);
	}

	return board;
}

bool finish(unsigned short board) {
	bool piece = getPiece(board, 0, 0);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (getPiece(board, i, j) != piece) {
				return false;
			}
		}
	}

	return true;
}

int BFS(unsigned short board) {
	queue<State> open;
	bitset< 1 << 16 > aClose;

	// 放入初始棋盘
	State state(board, 0);
	open.push(state);

	while (!open.empty()) {
		State aState = open.front();
		open.pop();
		unsigned short aBoard = aState.board;
		int count = aState.count;
		aClose[aBoard] = true;

		if (finish(aBoard)) {
			return count;
		} else {

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					unsigned short temp = flip(aBoard, i, j);
					// 判重
					if (!aClose[temp]) {
						State nextState(temp, count + 1);
						open.push(nextState);
					}

				}
			}
		}
	}

	return -1;
}

int main(int argc, char *argv[]) {

	unsigned short board = 0;	// 棋盘

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			char ch;
			cin >> ch;
			if (ch == 'w') {
				board += (1 << (i * 4 + j));
			}
		}
	}

	int res = BFS(board);

	if (res == -1) {
		cout << "Impossible"<<endl;
	} else {
		cout << res << endl;
	}

	return 0;
}