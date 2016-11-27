/*
 ID: arka.ma1
 PROG: crypt1
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <algorithm>

int get_num_length(int num) {
	std::ostringstream osstream;
	osstream << num;
	return (int) osstream.str().length();
}

bool is_valid(int num, int n, int digits[]) {
	std::ostringstream osstream;
	osstream << num;
	std::string stringified = osstream.str();
	for (std::string::iterator it = stringified.begin();
	     it != stringified.end(); it++) {
		if (std::find(digits, digits + n, *it - '0') == (digits + n)) {
			return false;
		}
	}
	return true;
}

int main() {
	std::ifstream input("crypt1.in");
	std::ofstream output("crypt1.out");
	assert(input.is_open() && output.is_open());
	int n;
	input >> n;
	int* digits = new
	int[n]; // never gave a bound for n in the problem description...
	for (int i = 0; i < n; i++) {
		int digit;
		input >> digit;
		digits[i] = digit;
	}
	int solutions = 0, abc, partial_product1, partial_product2, final;
	for (int a = 0; a < n; a++) {
		for (int b = 0; b < n; b++) {
			for (int c = 0; c < n; c++) {
				for (int d = 0; d < n; d++) {
					for (int e = 0; e < n; e++) {
						abc = digits[a] * 100 + digits[b] * 10 + digits[c];
						partial_product1 = digits[e] * abc;
						partial_product2 = digits[d] * abc;
						final = partial_product1 + partial_product2 * 10;
						if (get_num_length(partial_product1) == 3
						    && get_num_length(partial_product2) == 3
						    && get_num_length(final) == 4
						    && is_valid(partial_product1, n, digits)
						    && is_valid(partial_product2, n, digits)
						    && is_valid(final, n, digits)) {
							solutions++;
						}
					}
				}
			}
		}
	}
	output << solutions << std::endl;
	delete[] digits;
	input.close();
	output.close();
	return 0;
}
