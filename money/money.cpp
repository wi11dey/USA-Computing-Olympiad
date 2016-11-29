/*
 ID: arka.ma1
 PROG: money
 LANG: C++11
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using money_units = long long;

int main() {
	std::ifstream input("money.in");
	std::ofstream output("money.out");
	std::vector<money_units> coins;
	decltype(coins)::size_type v;
	money_units n;
	input >> v >> n;
	coins.reserve(v);
	for (decltype(coins)::size_type i = 0; i < v; ++i) {
		money_units coin;
		input >> coin;
		coins.push_back(coin);
	}
	std::sort(coins.begin(), coins.end()); // just to make sure
	std::vector<std::vector<long long>> solutions(n + 1,
	                                                 std::vector<long long>(v, 0));
	std::fill(solutions[0].begin(), solutions[0].end(), 1);
	for (money_units i = 1; i <= n; ++i) {
		bool smallest_coin = true;
		for (decltype(coins)::size_type j = 0; j < v; ++j) {
			if (!smallest_coin) {
				solutions[i][j] += solutions[i][j - 1];
			}
			smallest_coin = false;
			if (i >= coins[j]) {
				solutions[i][j] += solutions[i - coins[j]][j];
			}
		}
	}
	output << solutions[n][v - 1] << std::endl;
	return 0;
}
