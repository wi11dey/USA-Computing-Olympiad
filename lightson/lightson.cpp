/*
 ID: arkamajumdar
 PROG: lightson
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

struct room;
typedef std::vector<std::vector<room> > grid;

struct room {
	bool lit;
	bool visited;
	std::vector<room*> connections;
	
	room() :
		lit(false), visited(false), connections() {
	}
};

struct point {
	int x, y;
	
	point(int x, int y) :
		x(x), y(y) {
	}
};

inline bool in_bounds(point pt, int n) {
	return pt.x >= 0 && pt.x < n && pt.y >= 0 && pt.y < n;
}

std::vector<point> check_adjacents(point start, grid& rooms) {
	std::vector<point> retval;
	point candidates[4] = { point(start.x - 1, start.y), point(start.x + 1,
	                                                           start.y), point(start.x, start.y - 1), point(start.x, start.y + 1)
	                      };
	for (int i = 0; i < 4; i++) {
		if (in_bounds(candidates[i], (int) rooms.size())
		    && !rooms[candidates[i].x][candidates[i].y].visited
		    && rooms[candidates[i].x][candidates[i].y].lit) {
			retval.push_back(candidates[i]);
		}
	}
	return retval;
}

void _max_illuminated_rooms(point start, grid& rooms,
                            int& current_illuminated_rooms) {
	rooms[start.x][start.y].visited = true;
	std::vector<room*> connections = rooms[start.x][start.y].connections;
	for (std::vector<room*>::iterator it = connections.begin();
	     it != connections.end(); it++) {
		room* room = *it;
		if (!room->lit) {
			room->lit = true;
			current_illuminated_rooms++;
		}
	}
	std::vector<point> adjacents;
	do {
		adjacents = check_adjacents(start, rooms);
		for (std::vector<point>::iterator it = adjacents.begin();
		     it != adjacents.end(); it++) {
			_max_illuminated_rooms(*it, rooms, current_illuminated_rooms);
		}
	} while (!adjacents.empty());
}

int max_illuminated_rooms(grid& rooms) {
	int retval = 1;
	_max_illuminated_rooms(point(0, 0), rooms, retval);
	return retval;
}

int main() {
	std::ifstream input("lightson.in");
	std::ofstream output("lightson.out");
	assert(input.is_open() && output.is_open());
	int n, m;
	input >> n >> m;
	grid rooms(n, std::vector<room>(n));
	rooms[0][0].lit = true;
	for (int i = 0; i < m; i++) {
		int x, y;
		input >> x >> y;
		int a, b;
		input >> a >> b;
		rooms[x - 1][y - 1].connections.push_back(&rooms[a - 1][b - 1]);
	}
	output << max_illuminated_rooms(rooms) << std::endl;
	input.close();
	output.close();
	return 0;
}
