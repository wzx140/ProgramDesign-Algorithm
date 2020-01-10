#include <iostream>
#include <set>
#include <algorithm>

using std::endl;
using std::cin;
using std::cout;
using std::set;

// 2. 双队列
// stl库的set内部有序，所以使用set维护用户队列
// poj通过，但是cousera会compile error
// 具体的，可以手写avl树或者红黑树

struct User {
	int id = 0;
	int priority = 0;
	User(int x, int y) :id(x), priority(y) {}
	bool operator< (const User &user) const{
		return priority < user.priority;
	}
	bool operator== (const User &user) const{
		return priority == user.priority;
	}
};

int main(int argc, char *argv[]) {
	set<User> users;
	int order = 0, k = 0, p = 0;
	while (cin >> order && order) {
		if (order == 1) {
			cin >> k >> p;
			User user(k, p);
			auto search = users.find(user);
			if (search != users.end()) {
				users.erase(search);
			}
			users.insert(user);
		} else if (order == 2) {
			if (users.empty()) {
				cout << 0 << endl;
			} else {
				auto word = users.end();
				word--;
				cout << word->id << endl;
				users.erase(word);
			}

		} else if (order == 3) {
			if (users.empty()) {
				cout << 0 << endl;
			} else {
				cout << users.begin()->id << endl;
				users.erase(users.begin());
			}
		}
	}
	return 0;
}