/*
 ID: arkamajumdar
 PROG: radio
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <limits>

struct point {
	int x, y;
	
	inline friend point operator+(const point& lhs, const point& rhs) {
		point retval = { lhs.x + rhs.x, lhs.y + rhs.y };
		return retval;
	}
};

point move(point current, char direction) {
	static const point north = { 0, 1 }, south = { 0, -1 }, east = { 1, 0 },
	                   west = { -1, 0 };
	switch (direction) {
	case 'N':
		return current + north;
	case 'S':
		return current + south;
	case 'E':
		return current + east;
	case 'W':
		return current + west;
	default:
		return current;
	}
}

int square_distance(const point& a, const point& b) {
	int term1 = a.x - b.x, term2 = a.y - b.y;
	return term1 * term1 + term2 * term2;
}

int clamp_max(int num, int max) {
	if (num > max) {
		return max;
	}
	return num;
}

struct state {

};

int main() {
	std::ifstream input("radio.in");
	std::ofstream output("radio.out");
	assert(input.is_open() && output.is_open());
	int n, m;
	input >> n >> m;
	point f;
	input >> f.x >> f.y;
	point b;
	input >> b.x >> b.y;
	std::vector<char> farmer_john(n), bessie(m);
	for (int i = 0; i < n; i++) {
		input >> farmer_john[i];
	}
	for (int i = 0; i < m; i++) {
		input >> bessie[i];
	}
	int fi = 0, bi = 0;
	int total_distance = 0;
	while (fi < n || bi < m) {
		point f_move = move(f, farmer_john[clamp_max(fi, n - 1)]), b_move =
		                   move(b, bessie[clamp_max(bi, m - 1)]);
		int case1 = square_distance(f_move, b), case2 = square_distance(f,
		                                                                b_move), case3 = square_distance(f_move, b_move);
		int min_distance = std::min(case1, std::min(case2, case3));
#define SET_F       fi++;\
	f = f_move;
#define SET_B       bi++;\
	b = b_move;
		if (min_distance == case3) {
			SET_F
			SET_B
		} else {
			if (case1 == case2) {
				if (n > m) {
					SET_F
				} else {
					SET_B
				}
			} else {
				if (min_distance == case1) {
					SET_F
				} else {
					SET_B
				}
			}
		}
		total_distance += min_distance;
	}
	output << total_distance << std::endl;
	input.close();
	output.close();
	return 0;
}
