/*
 ID: arkamajumdar
 PROG: bphoto
 LANG: C++11
 */

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <deque>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using height = int;

using index = unsigned int;

struct cow {
	height m_height;

	index m_i;

	static bool compare_height(const cow& a, const cow& b) {
		return a.m_height < b.m_height;
	}
};

int main() {
	std::ifstream input("bphoto.in");
#ifdef DEBUG
	std::ostream& output = std::cout;
#else
	std::ofstream output("bphoto.out");
#endif
	size_t n;
	input >> n;
	std::vector<cow> cows(n);
	for (index i = 0; i < n; i++) {
		cows[i].m_i = i;
		input >> cows[i].m_height;
	}
	std::sort(cows.begin(), cows.end(), cow::compare_height);
	int unbalanced = 0;
	for (index i = 0; i < n; i++) {
		int left_greater = 0, right_greater = 0;
		for (index j = i + 1; j < n; j++) {
			if (cows[j].m_i > cows[i].m_i) {
				right_greater++;
			} else {
				left_greater++;
			}
		}
		if (std::max(left_greater, right_greater) > 2 * std::min(left_greater, right_greater)) {
			unbalanced++;
		}
	}
	output << unbalanced << std::endl;
	return 0;
}
