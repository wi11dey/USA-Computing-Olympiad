/*
 ID: arka.ma1
 PROG: hamming
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

int hamming_distance(int a, int b, int num_bits) {
	int differences = 0;
	for (int i = 0; i < num_bits; i++) {
		if ((a & 1) != (b & 1)) {
			differences++;
		}
		a >>= 1;
		b >>= 1;
	}
	return differences;
}

int max_value(int num_bits) {
	int retval = 0;
	for (int i = 0; i < num_bits; i++) {
		retval <<= 1;
		retval |= 1;
	}
	return retval;
}

int main() {
	std::ifstream input("hamming.in");
	std::ofstream output("hamming.out");
	assert(input.is_open() && output.is_open());
	int n, b, d;
	input >> n >> b >> d;
	std::vector<int> codewords;
	codewords.reserve(n);
	int max = max_value(b);
	for (int value = 0; (int) codewords.size() < n && value <= max; value++) {
		bool is_codeword = true;
		for (std::vector<int>::iterator it = codewords.begin(); it != codewords.end();
		     it++) {
			if (hamming_distance(value, *it, b) < d) {
				is_codeword = false;
				break;
			}
		}
		if (is_codeword) {
			codewords.push_back(value);
		}
	}
	for (int i = 0; i < (int) codewords.size(); i++) {
		output << codewords[i];
		i++;
		for (int j = 1; j < 10 && i < (int) codewords.size(); j++, i++) {
			output << " " << codewords[i];
		}
		i--;
		output << std::endl;
	}
	input.close();
	output.close();
	return 0;
}
