/*
 ID: arka.ma1
 PROG: subset
 LANG: C++11
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream input("subset.in");
	std::ofstream output("subset.out");
	int n;
	input >> n;
	int sum = (n * (n + 1)) / 2;
	if (sum % 2 == 0) {
		sum /= 2;
		std::vector<unsigned long> solutions(sum + 1, 0);
		solutions[0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = sum - i; j >= 0; j--) {
				if (solutions[j]) {
					solutions[j + i] += solutions[j];
				}
			}
		}
		output << solutions[sum] / 2 << std::endl;
	} else {
		output << 0 << std::endl;
	}
	return 0;
}
