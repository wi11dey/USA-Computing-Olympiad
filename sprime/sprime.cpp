/*
 ID: arka.ma1
 PROG: sprime
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <set>
#include <cmath>

bool is_prime(int num) {
	if (num == 0 || num == 1) {
		return false;
	}
	for (int i = 2; i <= sqrt(num); i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

void _check_superprimes(int start, int depth, int n,
                        std::set<int>& current_superprimes) {
	if (depth == n) {
		current_superprimes.insert(start);
		return;
	}
	for (int d = 1; d <= 9; d++) {
		int test = 10 * start + d;
		if (is_prime(test)) {
			_check_superprimes(test, depth + 1, n, current_superprimes);
		}
	}
}

std::set<int> check_superprimes(int n) {
	std::set<int> retval;
	_check_superprimes(0, 0, n, retval);
	return retval;
}

int main() {
	std::ifstream input("sprime.in");
	std::ofstream output("sprime.out");
	assert(input.is_open() && output.is_open());
	int n;
	input >> n;
	std::set<int> superprimes = check_superprimes(n);
	for (std::set<int>::iterator it = superprimes.begin(); it != superprimes.end();
	     it++) {
		output << *it << std::endl;
	}
	input.close();
	output.close();
	return 0;
}
