/*
 ID: arka.ma1
 PROG: dualpal
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <algorithm>

/*
 * @param base 2 <= "base" <= 10
 */
std::string to_base(int num, int base) {
	std::stringstream sstream;
	char digits[] = "0123456789";
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
	std::ifstream input("dualpal.in");
	std::ofstream output("dualpal.out");
	assert(input.is_open() && output.is_open());
	int n, s;
	input >> n >> s;
	int num_found = 0;
	for (int i = s + 1; num_found < n; i++) {
		int num_palindromes = 0;
		for (int j = 2; j <= 10; j++) {
			if (is_palindrome(to_base(i, j))) {
				num_palindromes++;
			}
			if (num_palindromes >= 2) {
				output << i << std::endl;
				num_found++;
				break;
			}
		}
	}
	input.close();
	output.close();
	return 0;
}
