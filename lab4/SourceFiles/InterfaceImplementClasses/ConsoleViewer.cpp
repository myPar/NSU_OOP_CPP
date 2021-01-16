#include <iostream>
#include <cassert>
#include "ConsoleViewer.h"
#include "Data.h"

void ConsoleViewer::display(Player& player) {
	PlayerId id = player.get_id();
	
	if (id == FIRST) {
		cout << "FIRST player:\n";
		cout << "-------------------------\n";
	}
	else if (id == SECOND) {
		cout << "SECOND player:\n";
		cout << "-------------------------\n";
	}
	else {
		assert(0 && "invalid player id");
	}
	// display own map
	cout << "own map:\n\n";
	display_map(player.own_map);
	cout << "\n";

	// display enemy map
	cout << "enemy map:\n\n";
	display_map(player.enemy_map);
	cout << "-------------------------\n\n";
}

void ConsoleViewer::display_map(Cell map[10][10]) {
	for (int y = 0; y < map_size; y++) {
		// print x axis first
		for (int x = 0; x < map_size; x++) {
			Cell cell = map[x][y];
			CellType type = cell.get_type();

			if (type == UNSEEN) {
				cout << "* ";
			}
			else if (type == HITTED) {
				cout << "X ";
			}
			else if (type == UNHITTED) {
				cout << "H ";
			}
			else if (type == EMPTY) {
				cout << "0 ";
			}
			else if (type == EMPTY_HITTED) {
				cout << "+ ";
			}
		}
		cout << "\n";
	}
}
