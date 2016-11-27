/*
 ID: arkamajumdar
 PROG: bcount
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

struct query_answer {
	int holsteins, guernseys, jerseys;
	
	friend query_answer operator-(const query_answer& a,
	                              const query_answer& b) {
		query_answer retval = { a.holsteins - b.holsteins, a.guernseys
		                        - b.guernseys, a.jerseys - b.jerseys
		                      };
		return retval;
	}
};

int main() {
	std::ifstream input("bcount.in");
	std::ofstream output("bcount.out");
	assert(input.is_open() && output.is_open());
	int n, q;
	input >> n >> q;
	std::vector<query_answer> answers;
	answers.reserve(n);
	query_answer current = { 0, 0, 0 };
	answers.push_back(current);
	for (int i = 0; i < n; i++) {
		int id;
		input >> id;
		if (id == 1) {
			current.holsteins++;
		} else if (id == 2) {
			current.guernseys++;
		} else if (id == 3) {
			current.jerseys++;
		}
		answers.push_back(current);
	}
	for (int i = 0; i < q; i++) {
		int a, b;
		input >> a >> b;
		query_answer answer = answers[b] - answers[a - 1];
		output << answer.holsteins << " " << answer.guernseys << " " << answer.jerseys
		       << std::endl;
	}
	input.close();
	output.close();
	return 0;
}
