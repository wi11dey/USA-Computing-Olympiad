/*
 ID: arka.ma1
 PROG: skidesign
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <limits>

int min(int a, int b) {
	return (a < b) ? a : b;
}

int main() {
	std::ifstream input("skidesign.in");
	std::ofstream output("skidesign.out");
	assert(input.is_open() && output.is_open());
	int n;
	input >> n;
	std::vector<int> hills;
	for (int i = 0; i < n; i++) {
		int hill;
		input >> hill;
		hills.push_back(hill);
	}
	int minimum_cost = std::numeric_limits<int>::max();
	for (int lower = 0; lower < n; lower++) {
		int upper = lower + 17;
		int temp = 0;
		for (int i = 0; i < n; i++) {
			int sq_root = 0;
			if (hills[i] < lower) {
				sq_root = lower - hills[i];
			} else if (hills[i] > upper) {
				sq_root = hills[i] - upper;
			}
			temp += sq_root * sq_root;
		}
		minimum_cost = min(minimum_cost, temp);
	}
	output << minimum_cost << std::endl;
	input.close();
	output.close();
	return 0;
}
