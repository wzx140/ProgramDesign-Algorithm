#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// 1. 英语数字转换器
// 考虑 100前会有前缀(<10) 1000和1000000前会有前缀(<1000)

map<string, int> numberMap;

// 字符串分割
void SplitString(const string& source, vector<std::string>& res, const string& split) {
	int pos1, pos2;
	pos2 = source.find(split);
	pos1 = 0;
	while (pos2 != string::npos) {
		res.push_back(source.substr(pos1, pos2 - pos1));

		pos1 = pos2 + split.size();
		pos2 = source.find(split, pos1);
	}
	if (pos1 != source.length()) {
		res.push_back(source.substr(pos1));
	}
}

int main(int argc, char *argv[]) {

	// 初始化
	numberMap["zero"] = 0;
	numberMap["one"] = 1;
	numberMap["two"] = 2;
	numberMap["three"] = 3;
	numberMap["four"] = 4;
	numberMap["five"] = 5;
	numberMap["six"] = 6;
	numberMap["seven"] = 7;
	numberMap["eight"] = 8;
	numberMap["nine"] = 9;
	numberMap["ten"] = 10;
	numberMap["eleven"] = 11;
	numberMap["twelve"] = 12;
	numberMap["thirteen"] = 13;
	numberMap["fourteen"] = 14;
	numberMap["fifteen"] = 15;
	numberMap["sixteen"] = 16;
	numberMap["seventeen"] = 17;
	numberMap["eighteen"] = 18;
	numberMap["nineteen"] = 19;
	numberMap["twenty"] = 20;
	numberMap["thirty"] = 30;
	numberMap["forty"] = 40;
	numberMap["fifty"] = 50;
	numberMap["sixty"] = 60;
	numberMap["seventy"] = 70;
	numberMap["eighty"] = 80;
	numberMap["ninety"] = 90;
	numberMap["hundred"] = 100;
	numberMap["thousand"] = 1000;
	numberMap["million"] = 1000000;

	while (true) {
		string str;
		getline(cin, str);
		if (str.empty()) {
			break;
		} else {

			vector<string> numbers;
			SplitString(str, numbers, " ");

			// 符号
			int sign = 1;
			if (numbers[0] == "negative") {
				sign = -1;
				numbers.erase(numbers.begin());
			}

			int n = numbers.size();
			int res = 0;	// 结果
			int prefix = 0;	// 前缀
			for (int i = 0; i < n ; i++){

				int num = numberMap[numbers[i]];

				if(num ==100){
					// 100 可能作为前缀
					prefix *= 100;

				}else if(num==1000){
					// 1000不可能作为前缀
					prefix *= 1000;
					res += prefix;
					prefix = 0;

				} else if (num == 1000000) {
					// 10000000不可能作为前缀
					prefix *= 1000000;
					res += prefix;
					prefix = 0;

				} else {
					// <100的数不可能有前缀
					prefix += num;
				}
			}
			res += prefix;
			
			cout << res * sign << endl;
		}
	}

	return 0;
}