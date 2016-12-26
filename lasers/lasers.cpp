/*
 ID: arkamajumdar
 PROG: lasers
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

struct fence_post {
	int x, y;
	int mirrors;

	friend bool operator==(const fence_post& a, const fence_post& b) {
		return a.x == b.x && a.y == b.y;
	}
};

int main() {
	std::ifstream input("lasers.in");
	std::ofstream output("lasers.out");
	int n;
	fence_post laser, barn;
	input >> n >> laser.x >> laser.y >> barn.x >> barn.y;
	if (laser == barn) {
		output << 0 << std::endl;
		return 0;
	}
	std::unordered_map<int, std::vector<fence_post>> rows;
	std::unordered_map<int, std::vector<fence_post>> columns;
	rows[laser.y].push_back(laser);
	columns[laser.x].push_back(laser);
	for (int i = 0; i < n; i++) {
		fence_post fence_post;
		input >> fence_post.x;
		input >> fence_post.y;
		rows[fence_post.y].push_back(fence_post);
		columns[fence_post.x].push_back(fence_post);
	}
	rows[barn.y].push_back(barn);
	columns[barn.x].push_back(barn);
//	for (fence_post fence_post : rows[barn.y]) {
//
//	}
	output << -1 << std::endl;
	return 0;
}
