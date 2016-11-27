/*
 ID: arka.ma1
 PROG: ariprog
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

struct solution {
	int a, b;
	
	solution(int a, int b) :
		a(a), b(b) {
	}
	
	inline friend bool operator<(const solution& a, const solution& b) {
		return a.b < b.b;
	}
};

class bisquare_checker {
	bool* array;
	const int max_bisquare;
	
public:
	bisquare_checker(int m) :
		max_bisquare(2 * m* m) {
		array = new bool[max_bisquare + 1];
		for (int i = 0; i <= max_bisquare; i++) {
			array[i] = false;
		}
		for (int p = 0; p <= m; p++) {
			for (int q = 0; q <= m; q++) {
				array[p * p + q * q] = true;
			}
		}
	}
	
	~bisquare_checker() {
		delete[] array;
	}
	
	bool operator[](int i) const {
		if (i > max_bisquare) {
			return false;
		}
		return array[i];
	}
	
	int max() const {
		return max_bisquare;
	}
};

int main() {
	std::ifstream input("ariprog.in");
	std::ofstream output("ariprog.out");
	assert(input.is_open() && output.is_open());
	int n, m;
	input >> n >> m;
	std::vector<solution> solutions;
	bisquare_checker bisquare(m);
	for (int a = 0; a <= bisquare.max(); a++) {
		if (bisquare[a]) {
			for (int b = 1; a + (n - 1) * b <= bisquare.max(); b++) {
				int count = 1;
				int k = a + b;
				while (bisquare[k]) {
					count++;
					k += b;
					if (count > n) {
						break;
					}
				}
				if (count >= n) {
					solutions.push_back(solution(a, b));
				}
			}
		}
	}
	std::sort(solutions.begin(), solutions.end());
	if (solutions.size() == 0) {
		output << "NONE" << std::endl;
	} else {
		for (std::vector<solution>::iterator it = solutions.begin();
		     it != solutions.end(); it++) {
			output << it->a << " " << it->b << std::endl;
		}
	}
	input.close();
	output.close();
	return 0;
}
