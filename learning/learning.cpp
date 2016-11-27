/*
 ID: arkamajumdar
 PROG: learning
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

struct cow {
	int weight;
	bool spotted;
	
	inline friend bool operator<(const cow& a, const cow& b) {
		return a.weight < b.weight;
	}
};

int min(int a, int b) {
	return (a < b) ? a : b;
}

int main() {
	std::ifstream input("learning.in");
	std::ofstream output("learning.out");
	assert(input.is_open() && output.is_open());
	int n, a, b;
	input >> n >> a >> b;
	std::vector<cow> cows;
	cows.reserve(n);
	for (int i = 0; i < n; i++) {
		cow temp;
		std::string spotted;
		input >> spotted;
		if (spotted == "S") {
			temp.spotted = true;
		} else {
			temp.spotted = false;
		}
		input >> temp.weight;
		cows.push_back(temp);
	}
	// int total_new_cows = b - a + 1;
	std::sort(cows.begin(), cows.end());
	for (int i = 0; i < n; i++) {
		if (!cows[i].spotted) {
		}
	}
	output << "..." << std::endl;
	/* ... other cleaning up ... */
	input.close();
	output.close();
	return 0;
}
