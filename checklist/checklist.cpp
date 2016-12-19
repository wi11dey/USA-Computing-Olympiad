/*
 ID: arkamajumdar
 PROG: checklist
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
	std::ifstream input("checklist.in");
	std::ofstream output("checklist.out");
	int h, g;
	input >> h >> g;
	std::vector<cow> holsteins(h), guernseys(g);
	for (int i = 0; i < h; i++) {
		input >> holsteins[i].x;
		input >> holsteins[i].y;
	}
	for (int i = 0; i < g; i++) {
		input >> guernseys[i].x;
		input >> guernseys[i].y;
	}
	
	return 0;
}
