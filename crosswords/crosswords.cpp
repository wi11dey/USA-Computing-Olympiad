/*
 ID: arkamajumdar
 PROG: crosswords
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

static int n, m;
static bool crossword[50][50];

bool get_crossword(int i, int j) {
	if (i < 0 || i >= n || j < 0 || j >= m) {
		return false;
	}
	return crossword[i][j];
}

struct clue {
	int i, j;
	
	clue(int i, int j) :
		i(i), j(j) {
	}
};

int main() {
	std::ifstream input("crosswords.in");
	std::ofstream output("crosswords.out");
	assert(input.is_open() && output.is_open());
	input >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c;
			input >> c;
			if (c == '.') {
				crossword[i][j] = true;
			} else {
				crossword[i][j] = false;
			}
		}
	}
	std::vector<clue> clues;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((get_crossword(i, j) && !get_crossword(i - 1, j)
			     && get_crossword(i + 1, j) && get_crossword(i + 2, j))
			    || (get_crossword(i, j) && !get_crossword(i, j - 1)
			        && get_crossword(i, j + 1)
			        && get_crossword(i, j + 2))) {
				clues.push_back(clue(i, j));
			}
		}
	}
	output << clues.size() << std::endl;
	for (std::vector<clue>::iterator it = clues.begin(); it != clues.end();
	     it++) {
		output << it->i + 1 << " " << it->j + 1 << std::endl;
	}
	/* ... other cleaning up ... */
	input.close();
	output.close();
	return 0;
}
