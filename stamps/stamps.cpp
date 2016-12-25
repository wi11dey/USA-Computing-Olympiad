/*
 ID: arka.ma1
 PROG: stamps
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

using stamp_value = int;

using num_stamps = int;

int main() {
	std::ifstream input("stamps.in");
#ifdef DEBUG
	std::ostream& output = std::cout;
#else
	std::ofstream output("stamps.out");
#endif
	num_stamps k;
	std::vector<stamp_value>::size_type n;
	input >> k >> n;
	std::vector<stamp_value> stamps(n);
	for (std::vector<stamp_value>::size_type i = 0; i < n; i++) {
		input >> stamps[i];
	}
	std::deque<num_stamps> solutions;
	solutions.push_back(0);
	for (stamp_value i = 1;; i++) {
		solutions.push_back(std::numeric_limits<stamp_value>::max());
		for (stamp_value stamp : stamps) {
			if (stamp <= i && solutions[i - stamp] + 1 < solutions[i]) {
				solutions[i] = solutions[i - stamp] + 1;
			}
		}
		if (solutions[i] > k) {
			output << i - 1 << std::endl;
			return 0;
		}
	}
	return 0;
}
