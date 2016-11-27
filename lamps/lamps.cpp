/*
 ID: arka.ma1
 PROG: lamps
 LANG: C++11
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

enum lamp_state {
	ON, OFF, UNKNOWN
};

using lamp_states = std::vector<lamp_state>;

bool agree(const lamp_states& a, const lamp_states& b) {
	for (lamp_states::size_type i = 0; i < a.size() && i < b.size(); i++) {
		if ((a[i] == OFF && b[i] == ON) || (a[i] == ON && b[i] == OFF)) {
			return false;
		}
	}
	return true;
}

void toggle(lamp_state& state) {
	if (state == ON) {
		state = OFF;
	} else if (state == OFF) {
		state = ON;
	}
}

void button1(lamp_states& lamps) {
	for (lamp_state& state : lamps) {
		toggle(state);
	}
}

void button2(lamp_states& lamps) {
	for (lamp_states::size_type i = 0; i < lamps.size(); i += 2) {
		toggle(lamps[i]);
	}
}

void button3(lamp_states& lamps) {
	for (lamp_states::size_type i = 1; i < lamps.size(); i += 2) {
		toggle(lamps[i]);
	}
}

void button4(lamp_states& lamps) {
	for (lamp_states::size_type i = 0; i < lamps.size(); i += 3) {
		toggle(lamps[i]);
	}
}

using lamp_button = void (*)(lamp_states&);

bool compare_as_binary_numbers(const lamp_states& a, const lamp_states& b) {
	if (a.size() < b.size()) {
		return true;
	} else if (a.size() > b.size()) {
		return false;
	}
	lamp_states::size_type a_sum = 0, b_sum = 0;
	for (lamp_states::size_type i = 0; i < a.size() && i < b.size(); i++) {
		if (a[i] == ON && b[i] == OFF) {
			return false;
		} else if (b[i] == ON && a[i] == OFF) {
			return true;
		}
	}
	return false;
}

int main() {
	std::ifstream input("lamps.in");
	std::ofstream output("lamps.out");
	lamp_states::size_type n;
	input >> n;
	lamp_states final_lamps(n, UNKNOWN);
	unsigned int c;
	input >> c;
	int lamp_number;
	while (true) {
		input >> lamp_number;
		if (lamp_number == -1) {
			break;
		}
		final_lamps[lamp_number - 1] = ON;
	}
	while (true) {
		input >> lamp_number;
		if (lamp_number == -1) {
			break;
		}
		final_lamps[lamp_number - 1] = OFF;
	}
	lamp_button press_button[] = { button1, button2, button3, button4 };
	std::vector<lamp_states> possible;
	for (std::vector<bool>::size_type r = 0; r <= 4; r++) {
		if (((r % 2 == 0) != (c % 2 == 0)) || r > c) {
			continue;
		}
		std::vector<bool> combinations(4, false);
		std::fill(combinations.begin(), combinations.begin() + r, true);
		do {
			lamp_states lamps(n, ON);
			for (std::vector<bool>::size_type i = 0; i < 4; i++) {
				if (combinations[i]) {
					press_button[i](lamps);
				}
			}
			if (agree(lamps, final_lamps)) {
				possible.push_back(lamps);
			}
		} while (std::prev_permutation(combinations.begin(), combinations.end()));
	}
	if (possible.empty()) {
		output << "IMPOSSIBLE" << std::endl;
	} else {
		std::sort(possible.begin(), possible.end(), compare_as_binary_numbers);
		for (lamp_states lamps : possible) {
			for (lamp_state state : lamps) {
				if (state == ON) {
					output << 1;
				} else if (state == OFF) {
					output << 0;
				}
			}
			output << std::endl;
		}
	}
	return 0;
}
