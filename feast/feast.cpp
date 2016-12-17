/*
 ID: arka.ma1
 PROG: feast
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

int maximum_fullness(int t, int a, int b) {
	std::vector<int> solutions(t + 1);
	solutions[0] = 0;
	for (int i = 1; i <= t; i++) {
		int max = 0;
		if (a <= i) {
			max = std::max(max, a + solutions[i - a]);
		}
		if (b <= i) {
			max = std::max(max, b + solutions[i - b]);
		}
		solutions[i] = max;
	}
	return solutions[t];
}

int main() {
	std::ifstream input("feast.in");
	std::ofstream output("feast.out");
	int t, a, b;
	input >> t >> a >> b;
	int fullness = maximum_fullness(t, a, b);
	fullness /= 2;
	t = t - fullness;
	fullness += maximum_fullness(t, a, b);
	output << fullness << std::endl;
	return 0;
}
