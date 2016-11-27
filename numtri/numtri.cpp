/*
 ID: arka.ma1
 PROG: numtri
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>

struct node {
	int value;
	bool visited;
};

inline bool within_range(int r, int i, int j) {
	return i < r && j <= i;
}

int max_sum(int r, node** nodes, int i, int j) {
	if (!within_range(r, i, j)) {
		return 0;
	}
	node& temp = nodes[i][j];
	if (!temp.visited) {
		temp.value += std::max(max_sum(r, nodes, i + 1, j), max_sum(r, nodes, i + 1,
		                                                            j + 1));
		temp.visited = true;
	}
	return temp.value;
}

int main() {
	std::ifstream input("numtri.in");
	std::ofstream output("numtri.out");
	assert(input.is_open() && output.is_open());
	int r;
	input >> r;
	node** nodes = new node*[r];
	for (int i = 0; i < r; i++) {
		nodes[i] = new node[i + 1];
		for (int j = 0; j < i + 1; j++) {
			input >> nodes[i][j].value;
			nodes[i][j].visited = false;
		}
	}
	output << max_sum(r, nodes, 0, 0) << std::endl;
	for (int i = 0; i < r; i++) {
		delete[] nodes[i];
	}
	delete[] nodes;
	input.close();
	output.close();
	return 0;
}
