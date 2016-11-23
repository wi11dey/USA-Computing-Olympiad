/*
 ID: arka.ma1
 PROG: runround
 LANG: C++11
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

using number = unsigned long;
using digit = unsigned short;

bool all_true(const std::vector<bool>& test) {
	for (bool elem : test) {
		if (!elem) {
			return false;
		}
	}
	return true;
}

bool is_runaround_number(number n) {
	if (n == 0) {
		return true;
	}
	std::vector<digit> digits;
	std::set<digit> digit_set;
	while (n > 0) {
		digit new_digit = static_cast<digit>(n % 10);
		digits.push_back(new_digit);
		if (!digit_set.insert(new_digit).second) {
			return false;
		}
		n /= 10;
	}
	std::reverse(digits.begin(), digits.end());
	std::vector<bool> touched(digits.size(), false);
	std::vector<digit>::size_type i = 0;
	digit old;
	do {
		if (touched[i]) {
			return false;
		}
		touched[i] = true;
		old = digits[i];
		i = (i + old) % digits.size();
		if (digits[i] == old) {
			return false;
		}
	} while (i != 0);
	return all_true(touched);
}

int main() {
	std::ifstream input("runround.in");
	std::ofstream output("runround.out");
	number m;
	input >> m;
	do {
		m++;
	} while (!is_runaround_number(m));
	output << m << std::endl;
	return 0;
}
