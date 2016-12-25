/*
 ID: arka.ma1
 PROG: contact
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

using occurences = int;

int main() {
	std::ifstream input("contact.in");
#ifdef DEBUG
	std::ostream& output = std::cout;
#else
	std::ofstream output("contact.out");
#endif
	std::string::size_type a, b;
	int n;
	input >> a >> b >> n;
	std::string sequence = "";
	std::string line;
	while (input >> line) {
		sequence += line;
	}
	std::unordered_map<std::string, occurences> bit_patterns;
	for (std::string::size_type length = a; length <= b && length <= sequence.length(); length++) {
		for (std::string::size_type pos = 0; pos <= sequence.length() - length;
				pos++) {
			bit_patterns[sequence.substr(pos, length)]++;
		}
	}
	std::map<occurences, std::forward_list<std::string>,
			std::greater<occurences>> sorted_bit_patterns;
	for (std::pair<const std::string, occurences>& pair : bit_patterns) {
		sorted_bit_patterns[pair.second].push_front(std::move(pair.first));
	}
	int i = 1;
	for (std::pair<const occurences, std::forward_list<std::string>>& pair : sorted_bit_patterns) {
		if (i > n) {
			break;
		}
		output << pair.first << std::endl;
		pair.second.sort(
				[] (const std::string& a, const std::string& b) {
					if (a.length() != b.length()) {
						return a.length() < b.length();
					}
					for (std::string::size_type i = 0, j = 0; i < a.length() && j < b.length(); i++, j++) {
						if (a[i] != b[j]) {
							return a[i] == '0';
						}
					}
					return false;
				});
		int j = 0;
		for (const std::string& bit_pattern : pair.second) {
			if (j != 0) {
				if (j % 6 == 0) {
					output << std::endl;
				} else {
					output << " ";
				}
			}
			output << bit_pattern;
			j++;
		}
		output << std::endl;
		i++;
	}
	return 0;
}
