/*
 ID: arkamajumdar
 PROG: marathon
 LANG: C++
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <limits>

struct checkpoint {
	int x, y;
};

int manhattan_distance(checkpoint a, checkpoint b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

int min(int a, int b) {
	return (a < b) ? a : b;
}

int main() {
	std::ifstream input("marathon.in");
	std::ofstream output("marathon.out");
	assert(input.is_open() && output.is_open());
	int n;
	input >> n;
	std::vector<checkpoint> checkpoints;
	std::vector<int> distances;
	for (int i = 0; i < n; i++) {
		checkpoint temp;
		input >> temp.x >> temp.y;
		checkpoints.push_back(temp);
	}
	int total = 0;
	for (int i = 0; i < n - 1; i++) {
		total += manhattan_distance(checkpoints[i], checkpoints[i + 1]);
	}
	int minimum_distance = std::numeric_limits<int>::max();
	for (int i = 1; i < n - 1; i++) {
		int temp_distance = total
		                    - manhattan_distance(checkpoints[i - 1], checkpoints[i])
		                    - manhattan_distance(checkpoints[i], checkpoints[i + 1])
		                    + manhattan_distance(checkpoints[i - 1], checkpoints[i + 1]);
		minimum_distance = min(minimum_distance, temp_distance);
	}
	output << minimum_distance << std::endl;
	input.close();
	output.close();
	return 0;
}
