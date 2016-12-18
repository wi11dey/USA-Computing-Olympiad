/*
 ID: arka.ma1
 PROG: concom
 LANG: C++11
 */

#include <algorithm>
#include <array>
#include <cstddef>
#include <deque>
#include <fstream>
#include <functional>
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

using company = int;

using percentage = int;

int main() {
	std::ifstream input("concom.in");
	std::ofstream output("concom.out");
	int n;
	input >> n;
	percentage ownership[101][101]{};
	for (int k = 0; k < n; k++) {
		company i, j;
		percentage p;
		input >> i >> j >> p;
		ownership[i][j] = p;
	}
	bool controlled[101][101]{};
	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j <= 100; j++) {
			if (i != j && !controlled[i][j] && ownership[i][j] > 50) {
				controlled[i][j] = true;
				for (int k = 1; k <= 100; k++) {
					ownership[i][k] += ownership[j][k];
					if (controlled[j][k]) {
						controlled[i][k] = true;
					}
				}
				j = 0;
			}
		}
	}
	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j <= 100; j++) {
			if (i != j && controlled[i][j]) {
				output << i << " " << j << std::endl;
			}
		}
	}
	return 0;
}
