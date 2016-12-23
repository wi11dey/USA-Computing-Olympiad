/*
 ID: arka.ma1
 PROG: fracdec
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

int main() {
	std::ifstream input("fracdec.in");
	std::ofstream output("fracdec.out");
	int n, d;
	input >> n >> d;
	std::ostringstream result;
	std::string::size_type repeat_start_index;
	bool repeats;
	std::unordered_map<int, std::string::size_type> remainder_indexes;
	for (int i = 0;; i++) {
		result << n / d;
		if (i == 0) {
			result << ".";
		}
		int remainder = n % d;
		if (remainder == 0) {
			if (i == 0) {
				result << "0";
			}
			repeats = false;
			break;
		}
		auto prev_remainder_iterator = remainder_indexes.find(remainder);
		if (prev_remainder_iterator != remainder_indexes.end()) {
			repeat_start_index = prev_remainder_iterator->second;
			repeats = true;
			break;
		}
		remainder_indexes[remainder] = result.tellp();
		n = remainder * 10;
	}
	std::string result_str = result.str();
	if (repeats) {
		result_str.insert(repeat_start_index, "(");
		result_str.append(")");
	}
	std::string::size_type remaining = result_str.length();
	std::string::size_type pos = 0;
	while (remaining > 76) {
		output << result_str.substr(pos, 76) << std::endl;
		remaining -= 76;
		pos += 76;
	}
	output << result_str.substr(pos, remaining) << std::endl;
	return 0;
}
