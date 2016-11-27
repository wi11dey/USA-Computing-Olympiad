/*
 ID: your_id_here
 PROG: piggyback
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>

int main() {
	std::ifstream input("piggyback.in");
	std::ofstream output("piggyback.out");
	assert(input.is_open() && output.is_open());
	output << "..." << std::endl;
	/* ... other cleaning up ... */
	input.close();
	output.close();
	return 0;
}
