/*
 ID: arkamajumdar
 PROG: paint
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>

void paint_fence(bool fence[], int a, int b) {
	for (int i = a; i < b; i++) {
		fence[i] = true;
	}
}

int main() {
	std::ifstream input("paint.in");
	std::ofstream output("paint.out");
	assert(input.is_open() && output.is_open());
	int a, b;
	int c, d;
	input >> a >> b;
	input >> c >> d;
	bool fence[101];
	for (int i = 0; i <= 100; i++) {
		fence[i] = false;
	}
	paint_fence(fence, a, b);
	paint_fence(fence, c, d);
	int count = 0;
	for (int i = 0; i <= 100; i++) {
		if (fence[i]) {
			count++;
		}
	}
	output << count << std::endl;
	input.close();
	output.close();
	return 0;
}
