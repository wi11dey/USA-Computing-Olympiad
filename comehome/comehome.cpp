/*
 ID: arka.ma1
 PROG: comehome
 LANG: C++11
 */

#include <algorithm>
#include <array>
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

using pasture_name = char;

using distance = int;

struct pasture {
	distance m_distance;

	bool m_visited;

	struct adjacent_pasture {
		pasture& m_pasture;

		distance m_weight;
	};

	std::forward_list<adjacent_pasture> m_adjacents;

	pasture() :
			m_distance(std::numeric_limits<distance>::max()), m_visited(false), m_adjacents() {
	}
};

bool contains_cow(pasture_name name) {
	return name >= 'A' && name < 'Z';
}

std::pair<pasture_name, pasture> dijkstra(std::unordered_map<pasture_name, pasture>& adjacency_list) {
	adjacency_list['Z'].m_distance = 0;
	while (true) {
		bool done = true;
		distance min_distance = std::numeric_limits<distance>::max();
		pasture_name closest_pasture_name;
		pasture* closest_pasture_ptr = nullptr;
		for (std::pair<const pasture_name, pasture>& pair : adjacency_list) {
			if (!pair.second.m_visited && pair.second.m_distance < min_distance) {
				done = false;
				min_distance = pair.second.m_distance;
				closest_pasture_name = pair.first;
				closest_pasture_ptr = &pair.second;
			}
		}
		if (done) {
			break;
		}
		closest_pasture_ptr->m_visited = true;
		if (contains_cow(closest_pasture_name)) {
			return std::make_pair(closest_pasture_name, *closest_pasture_ptr);
		}
		for (pasture::adjacent_pasture adjacent : closest_pasture_ptr->m_adjacents) {
			distance new_distance = closest_pasture_ptr->m_distance + adjacent.m_weight;
			if (new_distance < adjacent.m_pasture.m_distance) {
				adjacent.m_pasture.m_distance = new_distance;
			}
		}
	}
	throw std::invalid_argument("no cow reached the barn");
}

int main() {
	std::ifstream input("comehome.in");
	std::ofstream output("comehome.out");
	int p;
	input >> p;
	std::unordered_map<pasture_name, pasture> adjacency_list;
	for (int i = 0; i < p; i++) {
		pasture_name source, destination;
		distance weight;
		input >> source >> destination >> weight;
		adjacency_list[source].m_adjacents.push_front( {
				adjacency_list[destination], weight });
		adjacency_list[destination].m_adjacents.push_front( {
						adjacency_list[source], weight });
	}
	std::pair<pasture_name, pasture> pair = dijkstra(adjacency_list);
	output << pair.first << " " << pair.second.m_distance << std::endl;
	return 0;
}
