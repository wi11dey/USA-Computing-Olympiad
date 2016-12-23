/*
 ID: arka.ma1
 PROG: maze1
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

using distance = int;

struct square;

struct maze: public std::vector<std::vector<square>> {
	const size_type m_w, m_h;

	maze(size_type w, size_type h) :
			std::vector<std::vector<square>>(w, std::vector<square>(h)), m_w(w), m_h(
					h) {
	}
};

struct square {
	bool m_north, m_south, m_east, m_west;

	distance m_distance;

	bool m_visited;
};

struct square_location {
	maze::size_type m_i, m_j;
};

void dijkstra(square_location source, maze& maze) {
	for (maze::size_type i = 0; i < maze.m_w; i++) {
		for (maze::size_type j = 0; j < maze.m_h; j++) {
			maze[i][j].m_distance = std::numeric_limits<distance>::max();
			maze[i][j].m_visited = false;
		}
	}
	maze[source.m_i][source.m_j].m_distance = 0;
	while (true) {
		distance min_distance = std::numeric_limits<distance>::max();
		square_location current;
		bool empty = true;
		for (maze::size_type i = 0; i < maze.size(); i++) {
			for (maze::size_type j = 0; j < maze[i].size(); j++) {
				if (!maze[i][j].m_visited
						&& maze[i][j].m_distance < min_distance) {
					empty = false;
					min_distance = maze[i][j].m_distance;
					current = {i, j};
				}
			}
		}
		if (empty) {
			break;
		}
		square& current_square = maze[current.m_i][current.m_j];
		current_square.m_visited = true;
		auto check_neighbor =
				[&maze] (const square& source, square_location neighbor) {
					distance new_distance = source.m_distance + 1;
					if (new_distance < maze[neighbor.m_i][neighbor.m_j].m_distance) {
						maze[neighbor.m_i][neighbor.m_j].m_distance = new_distance;
					}
				};
		if (current_square.m_north) {
			check_neighbor(current_square, { current.m_i, current.m_j - 1 });
		}
		if (current_square.m_south) {
			check_neighbor(current_square, { current.m_i, current.m_j + 1 });
		}
		if (current_square.m_east) {
			check_neighbor(current_square, { current.m_i + 1, current.m_j });
		}
		if (current_square.m_west) {
			check_neighbor(current_square, { current.m_i - 1, current.m_j });
		}
	}
}

int main() {
	std::ifstream input("maze1.in");
	std::ofstream output("maze1.out");
	std::string line;
	std::getline(input, line);
	std::istringstream first_line(line);
	maze::size_type w, h;
	first_line >> w >> h;
	maze maze(w, h);
	std::vector<square_location> exits;
	exits.reserve(2);
	for (maze::size_type i = 0; i < 2 * h + 1; i++) {
		std::getline(input, line);
		for (maze::size_type j = 0; j < 2 * w + 1; j++) {
			maze::size_type k, l;
			if (i % 2 == 0 && j % 2 != 0 && line[j] == ' ') {
				k = (j - 1) / 2;
				l = i / 2;
				if (l == 0) {
					exits.push_back( { k, l });
				} else if (l == h) {
					exits.push_back( { k, l - 1 });
				} else {
					maze[k][l].m_north = true;
					maze[k][l - 1].m_south = true;
				}
			} else if (i % 2 != 0 && j % 2 == 0 && line[j] == ' ') {
				k = j / 2;
				l = (i - 1) / 2;
				if (k == 0) {
					exits.push_back( { k, l });
				} else if (k == w) {
					exits.push_back( { k - 1, l });
				} else {
					maze[k][l].m_west = true;
					maze[k - 1][l].m_east = true;
				}
			}
		}
	}
	std::vector<std::vector<distance>> min_distances(w,
			std::vector<distance>(h, std::numeric_limits<distance>::max()));
	for (square_location exit : exits) {
		dijkstra(exit, maze);
		for (maze::size_type i = 0; i < w; i++) {
			for (maze::size_type j = 0; j < h; j++) {
				min_distances[i][j] = std::min(min_distances[i][j],
						maze[i][j].m_distance);
			}
		}
	}
	distance max = 0;
	for (maze::size_type i = 0; i < w; i++) {
		for (maze::size_type j = 0; j < h; j++) {
			max = std::max(max, min_distances[i][j]);
		}
	}
	output << max + 1 << std::endl;
	return 0;
}
