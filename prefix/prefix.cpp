/*
 ID: arka.ma1
 PROG: prefix
 LANG: C++11
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>

int main() {
	std::ifstream input("prefix.in");
	std::ofstream output("prefix.out");
	std::vector<std::string> primitives;
	std::string str;
	while (true) {
		input >> str;
		if (str == ".") {
			break;
		}
		primitives.push_back(std::move(str));
	}
	std::string sequence;
	while (input >> str) {
		sequence += str;
	}
	std::vector<std::string::size_type> solutions(sequence.length() + 1, 0);
	for (int i = static_cast<int>(sequence.length()); i >= 0; i--) {
		for (const std::string& primitive : primitives) {
			if (primitive.length() > static_cast<std::string::size_type>(i)) {
				continue;
			}
			std::string::size_type start_pos = i - primitive.length();
			if (sequence.compare(start_pos, primitive.length(), primitive) == 0) {
				solutions[start_pos] = std::max(solutions[start_pos], primitive.length() + solutions[i]);
			}
		}
	}
	output << solutions[0] << std::endl;
	return 0;
}
