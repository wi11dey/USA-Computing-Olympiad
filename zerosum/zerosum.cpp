/*
 ID: arka.ma1
 PROG: zerosum
 LANG: C++11
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>

int sgn(int n) {
	if (n < 0) {
		return -1;
	} else if (n > 0) {
		return 1;
	} else {
		return 0;
	}
}

int evaluate(const std::string& calculation) {
	std::vector<int> values;
	bool first = true;
	for (auto it = calculation.begin(); it != calculation.end();) {
		char operation;
		if (first) {
			first = false;
			operation = '+';
		} else {
			operation = *it;
			++it;
		}
		int number = *it - '0';
		++it;
		if (operation == '+') {
			values.push_back(number);
		} else if (operation == '-') {
			values.push_back(-number);
		} else if (operation == ' ') {
			values.back() = values.back() * 10 + sgn(values.back()) * number;
		}
	}
	int sum = 0;
	for (int i : values) {
		sum += i;
	}
	return sum;
}

void zerosum(int current, int max, std::string&& current_calculation,
             std::vector<std::string>& result) {
	current_calculation += std::to_string(current);
	if (current == max) {
		if (evaluate(current_calculation) == 0) {
			result.push_back(std::move(current_calculation));
		}
		return;
	}
	static constexpr char operations[] = { '+', '-', ' ' };
	for (char operation : operations) {
		zerosum(current + 1, max, current_calculation + operation, result);
	}
}

int main() {
	std::ifstream input("zerosum.in");
	std::ofstream output("zerosum.out");
	int n;
	input >> n;
	std::vector<std::string> result;
	zerosum(1, n, "", result);
	std::sort(result.begin(), result.end());
	for (const std::string& calculation : result) {
		output << calculation << std::endl;
	}
	return 0;
}
