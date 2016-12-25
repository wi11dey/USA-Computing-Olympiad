/*
 ID: arka.ma1
 PROG: inflate
 LANG: C++11
 */

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <deque>
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
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define OUTPUT output

using minutes = int;

using points = int;

struct category {
	minutes m_minutes;

	points m_points;
};

int main() {
	std::ifstream input("inflate.in");
	std::ofstream output("inflate.out");
	minutes m;
	std::vector<category>::size_type n;
	input >> m >> n;
	std::vector<category> categories(n);
	for (std::vector<category>::size_type i = 0; i < n; i++) {
		input >> categories[i].m_points;
		input >> categories[i].m_minutes;
	}
	std::vector<points> solutions(m + 1);
	solutions[0] = 0;
	for (minutes i = 1; i <= m; i++) {
		points max = 0;
		for (std::vector<category>::size_type j = 0; j < n; j++) {
			if (categories[j].m_minutes <= i) {
				max = std::max(max,
						solutions[i - categories[j].m_minutes]
								+ categories[j].m_points);
			}
		}
		solutions[i] = max;
	}
	OUTPUT << solutions[m] << std::endl;
	return 0;
}
