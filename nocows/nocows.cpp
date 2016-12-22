/*
 ID: arka.ma1
 PROG: nocows
 LANG: C++11
 */

#include <algorithm>
#include <array>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

int main() {
	std::ifstream input("nocows.in");
	std::ofstream output("nocows.out");
	int n, k;
	input >> n >> k;
	std::vector<std::vector<int>> solution(n + 1, std::vector<int>(k + 1, 0));
	for (int i = 2; i <= k; i++) {
		for (int j = 3; j <= n; j += 2) {
			for (int k = 1; k <= j - 2; k++) {
				if (k == 1 || j - k - 1 == 1) {
					solution[1][i - 1] = 1;
				}
				solution[j][i] += solution[k][i - 1] * solution[j - k - 1][i - 1];
				solution[j][i] %= 9901;
			}
		}
	}
	for (int i = 1; i <= n; i += 2) {
		for (int j = 1; j <= k; j++) {
			std::cout << std::setw(3) << solution[i][j];
		}
		std::cout << std::endl;
	}
	output << (solution[n][k] - solution[n][k - 1] + 9901) % 9901 << std::endl;
	return 0;
}
