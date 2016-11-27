/*
 ID: arka.ma1
 PROG: castle
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <sstream>

struct module;
typedef std::vector<std::vector<module> > castle;

struct module {
	struct {
		bool west, north, east, south;
	} walls;
	int room;
};

int assign_to_room(int i, int j, int new_room, castle& modules) {
	int num_assigned = 0;
	module& module = modules[i][j];
	if (module.room == -1) {
		module.room = new_room;
		num_assigned++;
		if (!module.walls.west) {
			num_assigned += assign_to_room(i, j - 1, new_room, modules);
		}
		if (!module.walls.north) {
			num_assigned += assign_to_room(i - 1, j, new_room, modules);
		}
		if (!module.walls.east) {
			num_assigned += assign_to_room(i, j + 1, new_room, modules);
		}
		if (!module.walls.south) {
			num_assigned += assign_to_room(i + 1, j, new_room, modules);
		}
	}
	return num_assigned;
}

int assign_all_rooms(castle& modules, int& max_size) {
	max_size = 0;
	int num_rooms = 0;
	for (int i = 0; i < (int) modules.size(); i++) {
		for (int j = 0; j < (int) modules[i].size(); j++) {
			modules[i][j].room = -1;
		}
	}
	for (int i = 0; i < (int) modules.size(); i++) {
		for (int j = 0; j < (int) modules[i].size(); j++) {
			if (modules[i][j].room == -1) {
				num_rooms++;
				max_size = std::max(max_size,
				                    assign_to_room(i, j, num_rooms, modules));
			}
		}
	}
	return num_rooms;
}

class wall {
	castle* parent;
	
	template<typename T> class readonly_field {
		T value;
		
	public:
		readonly_field(T value) :
			value(value) {
		}
		
		operator T() const {
			return value;
		}
	};
	
	readonly_field<int> i, j;
	
public:
	readonly_field<int> row, column;
	bool north_wall;
	
	wall(castle& parent, int row, int column, bool north_wall) :
		parent(&parent), i(row - 1), j(column - 1), row(row), column(
		    column), north_wall(north_wall) {
	}
	
	bool is_on_edge() const {
		int rows = (int) parent->size(), columns = (int) parent->at(0).size();
		return row > rows || column > columns || north_wall ?
		       row == 1 : column == columns;
	}
	
	operator bool() const {
		return north_wall ?
		       parent->at(i)[j].walls.north : parent->at(i)[j].walls.east;
	}
	
	wall& operator=(const bool& enabled) {
		if (north_wall) {
			parent->at(i)[j].walls.north = enabled;
			if (!is_on_edge()) {
				parent->at(i - 1)[j].walls.south = enabled;
			}
		} else {
			parent->at(i)[j].walls.east = enabled;
			if (!is_on_edge()) {
				parent->at(i)[j + 1].walls.west = enabled;
			}
		}
		return *this;
	}
	
	inline friend bool operator<(const wall& a, const wall& b) {
		if (a.column == b.column) {
			if (a.row == b.row) {
				if (a.north_wall) {
					return true;
				}
			}
			return a.row > b.row;
		}
		return a.column < b.column;
	}
	
	std::string str() const {
		std::ostringstream oss;
		oss << row << " " << column << " " << (north_wall ? 'N' : 'E');
		return oss.str();
	}
};

inline void check_remove_wall(wall to_remove, castle& modules,
                              int& current_max_size, wall& optimal_wall) {
	if (to_remove.is_on_edge()) {
		return;
	}
	if (to_remove) {
		to_remove = false;
		int max_size = 0;
		assign_all_rooms(modules, max_size);
		if (max_size > current_max_size
		    || (max_size == current_max_size && to_remove < optimal_wall)) {
			optimal_wall = to_remove;
			current_max_size = max_size;
		}
		to_remove = true;
	}
}

int main() {
	std::ifstream input("castle.in");
	std::ofstream output("castle.out");
	assert(input.is_open() && output.is_open());
	int m, n;
	input >> m >> n;
	castle modules(n, std::vector<module>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int walls;
			input >> walls;
			module& module = modules[i][j];
			module.walls.west = walls & 1;
			module.walls.north = (walls >> 1) & 1;
			module.walls.east = (walls >> 2) & 1;
			module.walls.south = (walls >> 3) & 1;
		}
	}
	int max_size = 0;
	output << assign_all_rooms(modules, max_size) << std::endl;
	output << max_size << std::endl;
	wall optimal_wall(modules, 1, 1, true);
	int current_max_size = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			wall to_remove(modules, i + 1, j + 1, true);
			check_remove_wall(to_remove, modules, current_max_size,
			                  optimal_wall);
			to_remove.north_wall = false;
			check_remove_wall(to_remove, modules, current_max_size,
			                  optimal_wall);
		}
	}
	output << current_max_size << std::endl;
	output << optimal_wall.str() << std::endl;
	input.close();
	output.close();
	return 0;
}
