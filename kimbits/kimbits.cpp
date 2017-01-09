/*
 ID: arka.ma1
 PROG: kimbits
 LANG: C++11
 */

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <deque>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

int main() {
	std::ifstream input("kimbits.in");
#ifdef DEBUG
	std::ostream& output = std::cout;
#else
	std::ofstream output("kimbits.out");
#endif
	int n, l, i;
	input >> n >> l >> i;
	for (int j = 0; j <= l; i++) {
		std::vector<bool> bits(n, false);
		std::fill(bits.end() - j, bits.end(), true);
		int k = 0;
		do {
			k++;
			if (k == i) {
				for (bool bit : bits) {
					output << (bit ? '1' : '0');
				}
				output << std::endl;
			}
		} while (std::next_permutation(bits.begin(), bits.end()));
	}
	return 0;
}
