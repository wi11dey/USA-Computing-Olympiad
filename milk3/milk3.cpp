/*
 ID: arka.ma1
 PROG: milk3
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <set>
#include <algorithm>
#include <stdexcept>

struct bucket {
	int milk, size;
};

struct buckets_state {
	bucket a, b, c;
	
	bucket& operator[](int i) {
		if (i == 0) {
			return a;
		} else if (i == 1) {
			return b;
		} else if (i == 2) {
			return c;
		}
		throw std::out_of_range("i != 0 && i != 1 && i != 2");
	}
	
	friend bool operator==(const buckets_state& a, const buckets_state& b) {
		return a.a.milk == b.a.milk && a.b.milk == b.b.milk
		       && a.c.milk == b.c.milk;
	}
	
	void pour(int bucket1_i, int bucket2_i) {
		bucket& bucket1 = operator[](bucket1_i);
		bucket& bucket2 = operator[](bucket2_i);
		int bucket2_space = bucket2.size - bucket2.milk;
		if (bucket2_space < bucket1.milk) {
			bucket1.milk -= bucket2_space;
			bucket2.milk = bucket2.size;
		} else {
			bucket2.milk += bucket1.milk;
			bucket1.milk = 0;
		}
	}
};

void _pour_for_a_while(buckets_state& buckets,
                       std::vector<buckets_state>& visited, std::set<int>& solutions) {
	if (std::find(visited.begin(), visited.end(), buckets) != visited.end()) {
		return;
	}
	visited.push_back(buckets);
	for (int bucket1 = 0; bucket1 <= 2; bucket1++) {
		if (buckets[bucket1].milk != 0) {
			for (int bucket2 = 0; bucket2 <= 2; bucket2++) {
				if (bucket2 != bucket1) {
					buckets_state copy = buckets;
					copy.pour(bucket1, bucket2);
					_pour_for_a_while(copy, visited, solutions);
				}
			}
		} else if (bucket1 == 0) { // (buckets[0].milk == 0) is given
			solutions.insert(buckets.c.milk);
		}
	}
}

std::set<int> pour_for_a_while(buckets_state buckets) {
	std::set<int> retval;
	std::vector<buckets_state> visited;
	_pour_for_a_while(buckets, visited, retval);
	return retval;
}

int main() {
	std::ifstream input("milk3.in");
	std::ofstream output("milk3.out");
	assert(input.is_open() && output.is_open());
	buckets_state buckets;
	input >> buckets.a.size >> buckets.b.size >> buckets.c.size;
	buckets.a.milk = 0;
	buckets.b.milk = 0;
	buckets.c.milk = buckets.c.size;
	std::set<int> solutions = pour_for_a_while(buckets);
	for (std::set<int>::iterator it = solutions.begin(); it != solutions.end();
	     it++) {
		if (it != solutions.begin()) {
			output << " ";
		}
		output << *it;
	}
	output << std::endl;
	input.close();
	output.close();
	return 0;
}
