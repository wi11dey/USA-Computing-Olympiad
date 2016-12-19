/*
 ID: arkamajumdar
 PROG: moocast
 LANG: C++11
 */

#include <algorithm>
#include <array>
#include <cstddef>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct cow {
	int x, y;
};

int distance(const cow& a, const cow& b) {
	int delta_x = a.x - b.x;
	int delta_y = a.y - b.y;
	return delta_x * delta_x + delta_y * delta_y;
}

int main() {
	std::ifstream input("moocast.in");
	std::ofstream output("moocast.out");
	int n;
	input >> n;
	std::vector<cow> cows(n);
	for (int i = 0; i < n; i++) {
		input >> cows[i].x;
		input >> cows[i].y;
	}
	int max = 0;
	for (int i = 0; i < n; i++) {
		int min = std::numeric_limits<int>::max();
		for (int j = 0; j < n; j++) {
			if (i != j) {
				min = std::min(min, distance(cows[j], cows[i]));
			}
		}
		max = std::max(max, min);
	}
	output << max << std::endl;
	return 0;
}
