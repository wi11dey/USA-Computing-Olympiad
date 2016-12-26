/*
 ID: arka.ma1
 PROG: ttwo
 LANG: C++11
 */

#include <algorithm>
#include <array>
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

enum square {
	EMPTY, OBSTACLE
};

enum direction {
	NORTH = 0, EAST, SOUTH, WEST
};

struct player {
	int m_r, m_c;

	direction m_direction;

	friend bool operator==(const player& a, const player& b) {
		return a.m_r == b.m_r && a.m_c == b.m_c;
	}

	friend bool operator!=(const player& a, const player& b) {
		return !(a == b);
	}

	bool move_forward(const std::array<std::array<square, 10>, 10>& forest) {
		int next_r = m_r;
		int next_c = m_c;
		switch (m_direction) {
		case NORTH:
			next_r--;
			break;
		case EAST:
			next_c++;
			break;
		case SOUTH:
			next_r++;
			break;
		case WEST:
			next_c--;
			break;
		}
		if (next_r < 0 || next_c < 0 || next_r >= 10 || next_c >= 10) {
			return false;
		}
		if (forest[next_r][next_c] == OBSTACLE) {
			return false;
		}
		m_r = next_r;
		m_c = next_c;
		return true;
	}

	void rotate() {
		m_direction = static_cast<direction>((m_direction + 1) % 4);
	}

	player() :
			m_r(0), m_c(0), m_direction(NORTH) {
	}
};

struct state {
	player m_cows;

	player m_farmer_john;

	friend bool operator==(const state& a, const state& b) {
		return a.m_cows == b.m_cows && a.m_farmer_john == b.m_farmer_john;
	}
};

namespace std {
template<>
struct hash<state> {
	size_t operator()(const state& state) const {
		size_t hash = 0;
		hash += state.m_cows.m_r;
		hash *= 10;
		hash += state.m_cows.m_c;
		hash *= 10;
		hash += state.m_cows.m_direction;
		hash *= 10;
		hash += state.m_farmer_john.m_r;
		hash *= 10;
		hash += state.m_farmer_john.m_c;
		hash *= 10;
		hash += state.m_farmer_john.m_direction;
		return hash;
	}
};
}

int main() {
	std::ifstream input("ttwo.in");
	std::ofstream output("ttwo.out");
	std::array<std::array<square, 10>, 10> forest;
	player cows, farmer_john;
	cows.m_direction = NORTH;
	farmer_john.m_direction = NORTH;
	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			char ch;
			input >> ch;
			switch (ch) {
			case '.':
				forest[r][c] = EMPTY;
				break;
			case '*':
				forest[r][c] = OBSTACLE;
				break;
			case 'C':
				forest[r][c] = EMPTY;
				cows.m_r = r;
				cows.m_c = c;
				break;
			case 'F':
				forest[r][c] = EMPTY;
				farmer_john.m_r = r;
				farmer_john.m_c = c;
			}
		}
	}
	std::unordered_set<state> visited;
	int minutes = 0;
	while (cows != farmer_john) {
		if (!cows.move_forward(forest)) {
			cows.rotate();
		}
		if (!farmer_john.move_forward(forest)) {
			farmer_john.rotate();
		}
		state now = { cows, farmer_john };
		if (visited.find(now) != visited.end()) {
			minutes = 0;
			break;
		}
		visited.insert(std::move(now));
		minutes++;
	}
	output << minutes << std::endl;
	return 0;
}
