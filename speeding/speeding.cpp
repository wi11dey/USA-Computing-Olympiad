/*
 ID: arkamajumdar
 PROG: speeding
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <algorithm>

void set_speed(int array[], int start, int length, int speed) {
	for (int i = start; i < start + length; i++) {
		array[i] = speed;
	}
}

int main() {
	std::ifstream input("speeding.in");
	std::ofstream output("speeding.out");
	assert(input.is_open() && output.is_open());
	int n, m;
	input >> n >> m;
	int limit[100], bessie[100];
	int start = 0;
	for (int i = 0; i < n; i++) {
		int length, speed;
		input >> length >> speed;
		set_speed(limit, start, length, speed);
		start += length;
	}
	start = 0;
	for (int i = 0; i < m; i++) {
		int length, speed;
		input >> length >> speed;
		set_speed(bessie, start, length, speed);
		start += length;
	}
	int max = 0;
	for (int i = 0; i < 100; i++) {
		max = std::max(max, std::max(0, bessie[i] - limit[i]));
	}
	output << max << std::endl;
	input.close();
	output.close();
	return 0;
}
