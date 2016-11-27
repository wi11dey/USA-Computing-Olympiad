/*
 ID: arka.ma1
 PROG: wormhole
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <map>
#include <vector>
#include <list>
#include <algorithm>

struct wormhole {
	int x;
	int y;
//	int i;

	wormhole* next = NULL;
	wormhole* pair = NULL;
};

inline bool operator<(const wormhole& lhs, const wormhole& rhs) {
	return (lhs.y == rhs.y) ? lhs.x < rhs.x : lhs.y < rhs.y;
}

inline bool operator==(const wormhole& lhs, const wormhole& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator!=(const wormhole& lhs, const wormhole& rhs) {
	return !(lhs == rhs);
}

bool is_cycle(wormhole* starting_wormhole) {
	wormhole* current_wormhole = starting_wormhole;
	do {
		current_wormhole = current_wormhole->next;
		if (!current_wormhole) {
			return false;
		}
		current_wormhole = current_wormhole->pair;
	} while (*current_wormhole != *starting_wormhole);
	return true;
}

void _check_all_pairings(std::vector<wormhole*>& wormholes, bool paired[],
                         int& current_infinite_pairs) {
	int i = 0;
	while (i < (int) wormholes.size() && paired[i]) {
		i++;
	}
	if (i == (int) wormholes.size()) {
		for (std::vector<wormhole*>::iterator it = wormholes.begin();
		     it != wormholes.end(); it++) {
			if (is_cycle(*it)) {
				current_infinite_pairs++;
				return;
			}
		}
		return;
	}
	paired[i] = true;
	for (int j = i + 1; j < (int) wormholes.size(); j++) {
		if (!paired[j]) {
			paired[j] = true;
			wormholes[i]->pair = wormholes[j];
			wormholes[j]->pair = wormholes[i];
			_check_all_pairings(wormholes, paired, current_infinite_pairs);
			wormholes[i]->pair = NULL;
			wormholes[j]->pair = NULL;
			paired[j] = false;
		}
	}
	paired[i] = false;
}

int check_all_pairings(std::vector<wormhole*>& wormholes) {
	bool* paired = new bool[wormholes.size()];
	for (int i = 0; i < (int) wormholes.size(); i++) {
		paired[i] = false;
	}
	int retval = 0;
	_check_all_pairings(wormholes, paired, retval);
	delete[] paired;
	return retval;
}

bool compare_wormhole_ptrs(wormhole* a, wormhole* b) {
	return *a < *b;
}

int main() {
	std::ifstream input("wormhole.in");
	std::ofstream output("wormhole.out");
	assert(input.is_open() && output.is_open());
	int n;
	input >> n;
	std::vector<wormhole*> wormholes(n);
	{
		std::map<int, std::vector<wormhole*> > rows;
		for (int i = 0; i < n; i++) {
			wormhole* wormhole = new struct wormhole;
			input >> wormhole->x >> wormhole->y;
//			wormhole->i = i;
			wormholes[i] = wormhole;
			rows[wormhole->y].push_back(wormhole);
		}
		for (std::map<int, std::vector<wormhole*> >::iterator it1 = rows.begin();
		     it1 != rows.end(); it1++) {
			std::vector<wormhole*> current_row = it1->second;
			std::sort(current_row.begin(), current_row.end(), compare_wormhole_ptrs);
			std::vector<wormhole*>::iterator it2;
			for (it2 = current_row.begin(); it2 != current_row.end() - 1; it2++) {
				(**it2).next = *(it2 + 1);
			}
		}
	}
	output << check_all_pairings(wormholes) << std::endl;
	for (std::vector<wormhole*>::iterator it = wormholes.begin();
	     it != wormholes.end(); it++) {
		delete *it;
	}
	input.close();
	output.close();
	return 0;
}
