/*
 ID: arka.ma1
 PROG: frac1
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <set>

struct fraction {
	const int numerator, denominator;
	const float value;
	
	fraction(int numerator, int denominator) :
		numerator(numerator), denominator(denominator), value(
		    ((float) numerator) / ((float) denominator)) {
	}
	
	inline friend bool operator<(const fraction& a, const fraction& b) {
		return a.value < b.value;
	}
};

int main() {
	std::ifstream input("frac1.in");
	std::ofstream output("frac1.out");
	assert(input.is_open() && output.is_open());
	int n;
	input >> n;
	std::set<fraction> fractions;
	for (int denominator = 1; denominator <= n; denominator++) {
		for (int numerator = 0; numerator <= denominator; numerator++) {
			fraction temp(numerator, denominator);
			fractions.insert(temp);
		}
	}
	for (std::set<fraction>::iterator it = fractions.begin();
	     it != fractions.end(); it++) {
		output << it->numerator << "/" << it->denominator << std::endl;
	}
	input.close();
	output.close();
	return 0;
}
