/*
 ID: arka.ma1
 PROG: agrinet
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

using fiber_length = int;

struct farm {
	fiber_length m_distance;

	bool m_visited;

	std::vector<fiber_length> m_adjacents;

	farm(decltype(m_adjacents)::size_type num_adjacents) :
			m_distance(std::numeric_limits<fiber_length>::max()), m_visited(
					false), m_adjacents(num_adjacents) {
	}
};

void prim(std::vector<farm>& adjacency_matrix) {
	adjacency_matrix[0].m_distance = 0;
	while (true) {
		bool done = true;
		fiber_length min_distance = std::numeric_limits<fiber_length>::max();
		std::vector<farm>::size_type current_farm;
		for (std::vector<farm>::size_type i = 0; i < adjacency_matrix.size();
				i++) {
			if (!adjacency_matrix[i].m_visited
					&& adjacency_matrix[i].m_distance < min_distance) {
				done = false;
				min_distance = adjacency_matrix[i].m_distance;
				current_farm = i;
			}
		}
		if (done) {
			break;
		}
		adjacency_matrix[current_farm].m_visited = true;
		for (std::vector<farm>::size_type i = 0; i < adjacency_matrix.size();
				i++) {
			if (!adjacency_matrix[i].m_visited
					&& adjacency_matrix[current_farm].m_adjacents[i]
							< adjacency_matrix[i].m_distance) {
				adjacency_matrix[i].m_distance =
						adjacency_matrix[current_farm].m_adjacents[i];
			}
		}
	}
}

int main() {
	std::ifstream input("agrinet.in");
	std::ofstream output("agrinet.out");
	std::vector<farm>::size_type n;
	input >> n;
	std::vector<farm> adjacency_matrix(n, farm(n));
	for (std::vector<farm>::size_type i = 0; i < n; i++) {
		for (std::vector<fiber_length>::size_type j = 0; j < n; j++) {
			fiber_length length;
			input >> length;
			adjacency_matrix[i].m_adjacents[j] = length;
		}
	}
	prim(adjacency_matrix);
	fiber_length sum = 0;
	for (const farm& farm : adjacency_matrix) {
		sum += farm.m_distance;
	}
	OUTPUT << sum << std::endl;
	return 0;
}
