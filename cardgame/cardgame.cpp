/*
 ID: arka.ma1
 PROG: cardgame
 LANG: C++11
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>

using card = int;

int main() {
	std::ifstream input("cardgame.in");
	std::ofstream output("cardgame.out");
	int n;
	input >> n;
	std::vector<card> elise_cards(n);
	std::vector<card> bessie_cards;
	{
		std::vector<bool> used(2 * n + 1, false);
		for (int i = 0; i < n; i++) {
			input >> elise_cards[i];
			used[elise_cards[i]] = true;
		}
		bessie_cards.reserve(n);
		for (card i = 1; i <= 2 * n; i++) {
			if (!used[i]) {
				bessie_cards.push_back(i);
			}
		}
	}
	std::sort(elise_cards.begin(), elise_cards.begin() + n / 2);
	std::sort(elise_cards.begin() + n / 2, elise_cards.end());
	int points = 0;
	for (int i = 0, j = n / 2; i < n / 2; i++, j++) {
		while (j < n && bessie_cards[j] <= elise_cards[i]) {
			j++;
		}
		if (j >= n) {
			break;
		}
		points++;
	}
	for (int i = n - 1, j = n / 2 - 1; i >= n / 2; i--, j--) {
		while (j >= 0 && bessie_cards[j] >= elise_cards[i]) {
			j--;
		}
		if (j < 0) {
			break;
		}
		points++;
	}
	output << points << std::endl;
	return 0;
}
