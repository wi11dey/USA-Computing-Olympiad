/*
 ID: arka.ma1
 PROG: palsquare
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <algorithm>

/*
 * 2 <= "base" <= 20
 */
std::string to_base(int num, int base) {
	std::stringstream sstream;
	char digits[] = "0123456789ABCDEFGHIJ";
	int remainder;
	while (num != 0) {
		remainder = num % base;
		sstream << digits[remainder];
		num /= base;
	}
	std::string string = sstream.str();
	std::reverse(string.begin(), string.end());
	return string;
}

bool is_palindrome(std::string string) {
	std::string reversed(string);
	std::reverse(reversed.begin(), reversed.end());
	return string == reversed;
}

int main() {
	std::ifstream input("palsquare.in");
	std::ofstream output("palsquare.out");
	assert(input.is_open() && output.is_open());
	int base;
	input >> base;
	std::string conv_sq;
	for (int i = 1; i <= 300; i++) {
		conv_sq = to_base(i * i, base);
		if (is_palindrome(conv_sq)) {
			output << to_base(i, base) << " " << conv_sq << std::endl;
		}
	}
	input.close();
	output.close();
	return 0;
}
