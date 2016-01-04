/*
 ID: arka.ma1
 PROG: sort3
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream input("sort3.in");
	std::ofstream output("sort3.out");
	assert(input.is_open() && output.is_open());
	int n;
	input >> n;
	std::vector<int> sequence(n);
	for (int i = 0; i < n; i++) {
		input >> sequence[i];
	}
	std::vector<int> sorted_sequence(sequence);
	std::sort(sorted_sequence.begin(), sorted_sequence.end());
	int need_swapping[4][4] = { { 0 } };
	for (int i = 0; i < n; i++) {
		need_swapping[sequence[i]][sorted_sequence[i]]++;
	}
	int swaps = 0;
	// perfect 1-2 swaps
	{
		int temp = std::min(need_swapping[1][2], need_swapping[2][1]);
		swaps += temp;
		need_swapping[1][2] -= temp;
		need_swapping[2][1] -= temp;
	}
	// perfect 1-3 swaps
	{
		int temp = std::min(need_swapping[1][3], need_swapping[3][1]);
		swaps += temp;
		need_swapping[1][3] -= temp;
		need_swapping[3][1] -= temp;
	}
	// perfect 2-3 swaps
	{
		int temp = std::min(need_swapping[2][3], need_swapping[3][2]);
		swaps += temp;
		need_swapping[2][3] -= temp;
		need_swapping[3][2] -= temp;
	}
	// leftovers
	swaps += 2 * (need_swapping[2][1] + need_swapping[3][1]);
	output << swaps << std::endl;
	input.close();
	output.close();
	return 0;
}
