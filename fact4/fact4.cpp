/*
 ID: arka.ma1
 PROG: fact4
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
	std::ifstream input("fact4.in");
#ifdef DEBUG
	std::ostream& output = std::cout;
#else
	std::ofstream output("fact4.out");
#endif
	int n;
	input >> n;
	int factorial = 1;
	for (int i = 2; i <= n; i++) {
		factorial *= i;
		while (factorial % 10 == 0) {
			factorial /= 10;
		}
		factorial %= 10000;
	}
	output << factorial % 10 << std::endl;
	return 0;
}
