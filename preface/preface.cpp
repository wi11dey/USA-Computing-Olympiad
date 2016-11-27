/*
 ID: arka.ma1
 PROG: preface
 LANG: C++11
 */

#ifdef DEBUG
#include <iostream>
#endif
#include <fstream>
#include <string>
#include <algorithm>

using arabic_numeral = int;
using page_number = arabic_numeral;

std::string to_roman_numeral(arabic_numeral n) {
	constexpr static std::pair<arabic_numeral, const char*> roman_numerals[] = {
		{ 1000, "M" }, { 900, "CM" }, { 500, "D" }, { 400, "CD" }, {
			100,
			"C"
		}, { 90, "XC" }, { 50, "L" }, { 40, "XL" }, { 10, "X" },
		{ 9, "IX" }, { 5, "V" }, { 4, "IV" }, { 1, "I" }
	};
	std::string result;
	for (std::pair<arabic_numeral, const char*> pair : roman_numerals) {
		while (n >= pair.first) {
			result += pair.second;
			n -= pair.first;
		}
	}
	return result;
}

int main() {
	std::ifstream input("preface.in");
	std::ofstream output("preface.out");
	page_number n;
	input >> n;
	std::string roman_numerals = "IVXLCDM";
	std::string::difference_type counts[7] = {};
	for (page_number i = 1; i <= n; i++) {
		std::string roman_numeral = to_roman_numeral(i);
		for (std::string::size_type j = 0; j < 7; j++) {
			counts[j] += std::count(roman_numeral.begin(), roman_numeral.end(),
			                        roman_numerals[j]);
		}
	}
	for (std::string::size_type i = 0; i < 7; i++) {
		if (counts[i] > 0) {
			output << roman_numerals[i] << " " << counts[i] << std::endl;
		}
	}
	return 0;
}
