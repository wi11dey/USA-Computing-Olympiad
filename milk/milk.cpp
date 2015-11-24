/*
 ID: arka.ma1
 PROG: milk
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <limits>
#include <algorithm>

struct farmer {
	int price;
	int amount;
};

bool compare_price(const farmer& a, const farmer& b) {
	return a.price < b.price;
}

inline int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	std::ifstream input("milk.in");
	std::ofstream output("milk.out");
	assert(input.is_open() && output.is_open());
	int n, m;
	input >> n >> m;
	struct farmer* farmers = new struct farmer[m];
	for (int i = 0; i < m; i++) {
		int price, amount;
		input >> price >> amount;
		farmers[i].price = price;
		farmers[i].amount = amount;
	}
	std::sort(farmers, farmers + m, compare_price);
	int cost = 0, bought;
	for (int i = 0; i < m && n > 0; i++) {
		bought = min(n, farmers[i].amount);
		n -= bought;
		cost += farmers[i].price * bought;
	}
	output << cost << std::endl;
	delete[] farmers;
	input.close();
	output.close();
	return 0;
}
