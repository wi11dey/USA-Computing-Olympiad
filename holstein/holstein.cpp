/*
 ID: arka.ma1
 PROG: holstein
 LANG: C++11
 */

#ifdef DEBUG
#include <iostream>
#endif
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using vitamin_amount = int;
using feed_type = unsigned int;

class feed: public std::vector<vitamin_amount> {
	using super = std::vector<int>;
	
public:
	feed(size_type v) :
		super(v) {
	}
	
	friend std::istream& operator>>(std::istream& in, feed& into) {
		for (auto& elem : into) {
			in >> elem;
		}
		return in;
	}
	
	feed& operator+=(const feed& other) {
		auto it1 = begin();
		auto it2 = other.begin();
		for (; it1 != end() && it2 != other.end(); it1++, it2++) {
			*it1 += *it2;
		}
		return *this;
	}
	
	friend feed operator+(feed a, const feed& b) {
		a += b;
		return a;
	}
	
	friend bool operator<(const feed& a, const feed& b) {
		auto it1 = a.begin();
		auto it2 = b.begin();
		for (; it1 != a.end() && it2 != b.end(); it1++, it2++) {
			if (*it1 < *it2) {
				return true;
			}
		}
		return false;
	}
	
	friend bool operator>=(const feed& a, const feed& b) {
		return !(a < b);
	}
};

int main() {
	std::ifstream input("holstein.in");
	std::ofstream output("holstein.out");
	feed::size_type v;
	input >> v;
	feed target(v);
	input >> target;
	feed_type g;
	input >> g;
	std::vector<feed> feeds;
	for (feed_type i = 0; i < g; i++) {
		feed new_feed(v);
		input >> new_feed;
		feeds.push_back(std::move(new_feed));
	}
	for (feed_type r = 1; r <= g; r++) {
		std::vector<bool> combinations(g);
		std::fill(combinations.begin(), combinations.begin() + r, true);
		std::vector<feed_type> types_fed;
		types_fed.reserve(r);
		do {
			feed total(v);
			for (feed_type i = 0; i < g; i++) {
				if (combinations[i]) {
					total += feeds[i];
					types_fed.push_back(i + 1);
				}
			}
			if (total >= target) {
				output << r;
				for (feed_type type : types_fed) {
					output << " " << type;
				}
				output << std::endl;
				goto exit;
			}
			types_fed.clear();
		} while (std::prev_permutation(combinations.begin(), combinations.end()));
	}
exit:
	return 0;
}
