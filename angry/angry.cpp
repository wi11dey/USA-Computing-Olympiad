/*
 ID: arkamajumdar
 PROG: angry
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>



int main() {
	std::ifstream input("angry.in");
	std::ofstream output("angry.out");
	assert(input.is_open() && output.is_open());
	int n;
	input >> n;
	std::vector<int> bales(n);
	for (int i = 0; i < n; i++) {
		int temp;
		input >> temp;
		bales[i] = temp;
	}
	std::sort(bales.begin(), bales.end());
	int max_distance = 0;
	for (int i = 1; i < n; i++) {
		int distance = bales[i] - bales[i - 1];
		if (distance > max_distance) {
		}
	}
	output << (max_distance / 2) + 1 << ".0" << std::endl;
	input.close();
	output.close();
	return 0;
}
