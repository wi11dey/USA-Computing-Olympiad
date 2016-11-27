/*
 ID: arka.ma1
 PROG: barn1
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

inline int min(int a, int b) {
	return (a < b) ? a : b;
}

inline int max(int a, int b) {
	return (a > b) ? a : b;
}

struct board_range {
	int start;
	int end;
	
	int distance() const {
		return end - start + 1;
	}
};

struct barn {
	int size;
	bool* stalls, *boards;
	
	barn(int s) {
		size = ++s;
		stalls = new bool[s];
		boards = new bool[s];
		for (int i = 0; i < s; i++) {
			stalls[i] = boards[i] = false;
		}
	}
	
	~barn() {
		delete[] stalls;
		delete[] boards;
	}
	
	void lay_board(struct board_range range, bool cover = true) {
		for (int i = range.start; i <= range.end && i < size; i++) {
			boards[i] = cover;
		}
	}
};

std::vector<struct board_range> find_gaps(struct board_range within,
                                          const struct barn& barn) {
	std::vector<struct board_range> retval;
	struct board_range temp = { 0, 0 };
	bool in_gap = false;
	for (int i = within.start; i <= within.end && i < barn.size; i++) {
		if (!in_gap && !barn.stalls[i]) {
			in_gap = true;
			temp.start = i;
		} else if (in_gap && barn.stalls[i]) {
			in_gap = false;
			temp.end = i - 1;
			retval.push_back(temp);
		}
	}
	return retval;
}

bool compare_range_distances(const struct board_range& a,
                             const struct board_range& b) {
	return a.distance() > b.distance();
}

int main() {
	std::ifstream input("barn1.in");
	std::ofstream output("barn1.out");
	assert(input.is_open() && output.is_open());
	int m, s, c;
	input >> m >> s >> c;
	struct barn barn(s);
	struct board_range first_board = { s, 1 };
	for (int i = 0; i < c; i++) {
		int stall_number;
		input >> stall_number;
		first_board.start = min(first_board.start, stall_number);
		first_board.end = max(first_board.end, stall_number);
		barn.stalls[stall_number] = true;
	}
	barn.lay_board(first_board);
	std::vector<struct board_range> gaps = find_gaps(first_board, barn);
	std::sort(gaps.begin(), gaps.end(), compare_range_distances);
	std::vector<struct board_range>::iterator iterator = gaps.begin();
	for (int i = 1; iterator != gaps.end() && i < m; iterator++, i++) {
		barn.lay_board(*iterator, false);
	}
	int covered_stalls = 0;
	for (int i = 0; i < barn.size; i++) {
		if (barn.boards[i]) {
			covered_stalls++;
		}
	}
	output << covered_stalls << std::endl;
	input.close();
	output.close();
	return 0;
}
