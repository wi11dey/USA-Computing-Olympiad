/*
 ID: arka.ma1
 PROG: combo
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <vector>

int wrap(int x, int n) {
	x %= n;
	return (x < 1) ? n - abs(x) : x;
}

struct combo {
	int digits[3];
	
	bool operator==(const struct combo& other) const {
		return (digits[0] == other.digits[0]) && (digits[1] == other.digits[1])
		       && (digits[2] == other.digits[2]);
	}
};

void find_combos(struct combo actual, int n,
                 std::vector<struct combo>& combos) {
	for (int a = -2; a <= 2; a++) {
		for (int b = -2; b <= 2; b++) {
			for (int c = -2; c <= 2; c++) {
				struct combo temp = {
					{
						wrap(actual.digits[0] + a, n), wrap(
						    actual.digits[1] + b, n), wrap(
						        actual.digits[2] + c, n)
					}
				};
				if (std::find(combos.begin(), combos.end(), temp)
				    == combos.end()) {
					combos.push_back(temp);
				}
			}
		}
	}
}

int count_all_combos(struct combo farmer_john, struct combo master, int n) {
	std::vector<struct combo> combos;
	find_combos(farmer_john, n, combos);
	find_combos(master, n, combos);
	return (int) combos.size();
}

int main() {
	std::ifstream input("combo.in");
	std::ofstream output("combo.out");
	assert(input.is_open() && output.is_open());
	int n;
	input >> n;
	struct combo farmer_john, master;
	for (int i = 0; i < 3; i++) {
		input >> farmer_john.digits[i];
	}
	for (int i = 0; i < 3; i++) {
		input >> master.digits[i];
	}
	output << count_all_combos(farmer_john, master, n) << std::endl;
	input.close();
	output.close();
	return 0;
}
