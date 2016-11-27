/*
 ID: arkamajumdar
 PROG: badmilk
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

struct milk_drink {
	int milk_type, time;
	
	inline friend bool operator<(const milk_drink& a, const milk_drink& b) {
		return a.time < b.time;
	}
};

struct person {
	std::vector<milk_drink> drinks;
	int sick_time;
	bool sorted;
	
	person() :
		drinks(), sick_time(-1), sorted(false) {
	}
	
	int first_drink_time(int milk_type) {
		if (!sorted) {
			std::sort(drinks.begin(), drinks.end());
			sorted = true;
		}
		for (std::vector<milk_drink>::iterator it = drinks.begin();
		     it != drinks.end(); it++) {
			if (it->milk_type == milk_type) {
				return it->time;
			}
		}
		return -1;
	}
	
	bool got_sick() {
		return sick_time != -1;
	}
};

int main() {
	std::ifstream input("badmilk.in");
	std::ofstream output("badmilk.out");
	assert(input.is_open() && output.is_open());
	int n, m, d, s;
	input >> n >> m >> d >> s;
	std::vector<person> friends(n + 1);
	for (int i = 0; i < d; i++) {
		milk_drink drink;
		int p;
		input >> p >> drink.milk_type >> drink.time;
		friends[p].drinks.push_back(drink);
	}
	for (int i = 0; i < s; i++) {
		int p, t;
		input >> p >> t;
		friends[p].sick_time = t;
	}
	int max = 0;
	for (int i = 1; i <= m; i++) {
		bool is_bad = true;
		int medicine = 0;
		for (int j = 1; j <= n; j++) {
			int first_drink_time = friends[j].first_drink_time(i);
			if (first_drink_time != -1) { // drank the milk sometime
				medicine++; // is, obviously, a drinker of the milk then, might need medicine
				if (friends[j].got_sick()
				    && friends[j].sick_time <=
				    first_drink_time) { // friend got sick, but only drank the milk after getting sick
					is_bad = false;
					break;
				}
			} else if (
			    friends[j].got_sick()) { // did not drink the milk, but still got sick
				is_bad = false;
				break;
			}
		}
		if (is_bad) {
			max = std::max(max, medicine);
		}
	}
	output << max << std::endl;
	input.close();
	output.close();
	return 0;
}
