/*
 ID: your_id_here
 PROG: namenum
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

std::vector<std::string> _list_combinations(const std::vector<int>& digits,
                                            const std::vector<std::string>& dictionary, unsigned int starting_digit,
                                            std::string& current_string,
                                            std::vector<std::string>& current_combinations) {
	static const char letters[] = "   ABCDEFGHIJKLMNOPRSTUVWXY";
	if (starting_digit >= digits.size()) {
		if (std::binary_search(dictionary.begin(), dictionary.end(),
		                       current_string)) {
			current_combinations.push_back(current_string);
		}
		return current_combinations;
	}
	for (int i = 0; i < 3; i++) {
		current_string[starting_digit] = letters[(3
		                                          * (digits[starting_digit] - 1)) + i];
		_list_combinations(digits, dictionary, starting_digit + 1,
		                   current_string, current_combinations);
	}
	return current_combinations;
}

std::vector<std::string> list_combinations(const std::vector<int>& digits,
                                           const std::vector<std::string>& dictionary) {
	std::string current_string(digits.size(), ' ');
	std::vector<std::string> current_combinations;
	return _list_combinations(digits, dictionary, 0, current_string,
	                          current_combinations);
}

int main() {
	std::ifstream input("namenum.in");
	std::ifstream dict("dict.txt");
	std::ofstream output("namenum.out");
	assert(input.is_open() && output.is_open());
	std::vector<std::string> dictionary;
	std::string name;
	while (dict >> name) {
		dictionary.push_back(name);
	}
	char c;
	std::vector<int> serial;
	while (input >> c) {
		serial.push_back(c - '0');
	}
	std::vector<std::string> valid_names = list_combinations(serial,
	                                                         dictionary);
	if (valid_names.empty()) {
		output << "NONE" << std::endl;
	} else {
		std::vector<std::string>::iterator iterator = valid_names.begin();
		while (iterator != valid_names.end()) {
			output << *iterator << std::endl;
			iterator++;
		}
	}
	input.close();
	output.close();
	return 0;
}
