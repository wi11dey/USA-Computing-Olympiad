/*
 ID: arka.ma1
 PROG: humble
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

using humble_number = long;

using prime = int;

using times_used = int;

int main() {
	std::ifstream input("humble.in");
#ifdef DEBUG
	std::ostream& output = std::cout;
#else
	std::ofstream output("humble.out");
#endif
	std::vector<prime>::size_type k;
	std::vector<humble_number>::size_type n;
	input >> k >> n;
	std::vector<prime> s(k);
	for (std::vector<prime>::size_type i = 0; i < k; i++) {
		input >> s[i];
	}
	std::vector<times_used> times_primes_used(k, 0);
	std::vector<humble_number> humble_numbers(n + 1);
	humble_numbers[0] = 1;
	for (std::vector<humble_number>::size_type i = 1; i <= n; i++) {
		humble_number min = std::numeric_limits<humble_number>::max();
		std::forward_list<std::vector<prime>::size_type> primes_used;
		for (std::vector<prime>::size_type j = 0; j < k; j++) {
			humble_number number = humble_numbers[times_primes_used[j]] * s[j];
			if (number > humble_numbers[i - 1] && number <= min) {
				if (number < min) {
					min = number;
					primes_used.clear();
				}
				primes_used.push_front(j);
			}
		}
		humble_numbers[i] = min;
		for (std::vector<prime>::size_type j : primes_used) {
			times_primes_used[j]++;
		}
	}
	output << humble_numbers[n] << std::endl;
	return 0;
}
