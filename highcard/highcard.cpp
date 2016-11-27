/*
 ID: arkamajumdar
 PROG: highcard
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
	std::ifstream input("highcard.in");
	std::ofstream output("highcard.out");
	assert(input.is_open() && output.is_open());
	int n;
	input >> n;
	std::set<int> elise_cards;
	for (int i = 0; i < n; i++) {
		int card;
		input >> card;
		elise_cards.insert(card);
	}
	std::set<int> bessie_cards;
	std::vector<int> all_cards;
	all_cards.reserve(2 * n);
	for (int i = 1; i <= 2 * n; i++) {
		all_cards.push_back(i);
	}
	std::set_difference(all_cards.begin(), all_cards.end(), elise_cards.begin(),
	                    elise_cards.end(), std::inserter(bessie_cards, bessie_cards.end()));
	int current_points = 0;
	for (std::set<int>::iterator elise = elise_cards.begin();
	     elise != elise_cards.end(); elise++) {
		std::set<int>::iterator bessie = bessie_cards.upper_bound(*elise);
		if (bessie == bessie_cards.end()) {
			bessie = bessie_cards.begin();
		}
		if (*bessie > *elise) {
			current_points++;
		}
		bessie_cards.erase(bessie);
	}
	output << current_points << std::endl;
	input.close();
	output.close();
	return 0;
}
