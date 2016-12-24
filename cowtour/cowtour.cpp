/*
 ID: arka.ma1
 PROG: cowtour
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

using coordinate = int;

struct pasture {
	coordinate m_x, m_y;
};

using distance = double;

inline distance distance_between(const pasture& a, const pasture& b) {
	coordinate delta_x = a.m_x - b.m_x;
	coordinate delta_y = a.m_y - b.m_y;
	return std::sqrt(delta_x * delta_x + delta_y * delta_y);
}

int main() {
	std::ifstream input("cowtour.in");
	std::ofstream output("cowtour.out");
	std::vector<pasture>::size_type n;
	input >> n;
	std::vector<pasture> pastures(n);
	for (std::vector<pasture>::size_type i = 0; i < n; i++) {
		input >> pastures[i].m_x;
		input >> pastures[i].m_y;
	}
	std::vector<std::vector<distance>> distances(pastures.size(),
				std::vector<distance>(pastures.size(),
						std::numeric_limits<distance>::infinity()));
	for (std::vector<pasture>::size_type i = 0; i < n; i++) {
		for (std::vector<pasture>::size_type j = 0; j < n; j++) {
			char c;
			input >> c;
			if (c == '1') {
				distances[i][j] = distance_between(pastures[i], pastures[j]);
			} else if (i == j) {
				distances[i][j] = 0;
			}
		}
	}
	for (std::vector<pasture>::size_type k = 0; k < pastures.size(); k++) {
		for (std::vector<pasture>::size_type i = 0; i < pastures.size(); i++) {
			for (std::vector<pasture>::size_type j = 0; j < pastures.size();
					j++) {
				distance new_distance = distances[i][k] + distances[k][j];
				if (new_distance < distances[i][j]) {
					distances[i][j] = new_distance;
				}
			}
		}
	}
	std::vector<distance> diameters(n);
	for (std::vector<pasture>::size_type i = 0; i < n; i++) {
		for (std::vector<pasture>::size_type j = 0; j < n; j++) {
			if (distances[i][j] < std::numeric_limits<distance>::infinity()) {
				diameters[i] = std::max(diameters[i], distances[i][j]);
			}
		}
	}
	distance min_diameter = std::numeric_limits<distance>::infinity();
	for (std::vector<pasture>::size_type i = 0; i < n; i++) {
		for (std::vector<pasture>::size_type j = i + 1; j < n; j++) {
			if (distances[i][j] == std::numeric_limits<distance>::infinity()) {
				min_diameter = std::min(min_diameter, diameters[i] + distance_between(pastures[i], pastures[j]) + diameters[j]);
			}
		}
	}
	for (std::vector<pasture>::size_type i = 0; i < n; i++) {
		min_diameter = std::max(min_diameter, diameters[i]);
	}
	output << std::fixed << std::setprecision(6) << min_diameter << std::endl;
	return 0;
}
