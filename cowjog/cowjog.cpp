/*
 ID: arkamajumdar
 PROG: cowjog
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

struct cow {
	int position, speed;
};

int main() {
	std::ifstream input("cowjog.in");
	std::ofstream output("cowjog.out");
	assert(input.is_open() && output.is_open());
	int n;
	input >> n;
	std::vector<cow> cows;
	cows.reserve(n);
	for (int i = 0; i < n; i++) {
		cow temp;
		input >> temp.position >> temp.speed;
		cows.push_back(temp);
	}
	std::reverse(cows.begin(), cows.end());
	int groups = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++, i++) {
			if (cows[j].speed > cows[i].speed) {
				cows[j].speed = cows[i].speed;
			} else {
				break;
			}
		}
		groups++;
	}
	output << groups << std::endl;
	input.close();
	output.close();
	return 0;
}
