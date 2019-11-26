#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <functional>

using std::endl;
using std::cout;
using std::cin;
using std::sqrt;
using std::stable_sort;
using std::fixed;
using std::setprecision;
using std::greater;

// 1. 距离排序

struct Point {
	int x = 0;
	int y = 0;
	int z = 0;
}points[12];

struct Distance {
	int point1;
	int point2;
	double d;
	Distance() :point1(0), point2(0), d(0) {}
	Distance(int a, int b) {

		point1 = a;
		point2 = b;

		double dx = points[a].x - points[b].x;
		double dy = points[a].y - points[b].y;
		double dz = points[a].z - points[b].z;
		d = sqrt(dx * dx + dy * dy + dz * dz);
	}
	bool operator < (const Distance &distance) const {
		return d > distance.d;
	}
}distances[144];

int main(int argc, char *argv[]) {

	int n = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> points[i].x;
		cin >> points[i].y;
		cin >> points[i].z;
	}

	int num = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			distances[num++] = Distance(i, j);
		}
	}

	// 使用稳定的排序
	stable_sort(distances, distances + num);

	for (int i = 0; i < num; i++) {
		Point point1 = points[distances[i].point1];
		Point point2 = points[distances[i].point2];
		cout << "(" << point1.x << "," << point1.y << "," << point1.z << ")-(" << point2.x << "," << point2.y << "," << point2.z << ")" << "=" << fixed << setprecision(2) << distances[i].d << endl;
	}

	return 0;
}