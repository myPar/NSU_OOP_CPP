#include <cassert>
#include "Player.h"
#include "ConsolePlayer.h"
#include "RandomPlayer.h"
#include "SmartPlayer.h"

Player::Player(PlayerId id) : player_id(id) {
	// ship creating
	for (int ship_id = 0; ship_id < max_ship_count; ship_id++) {
		// create ships
		ships[ship_id] = Ship(ship_id);
	}
	// initial own map initialisation
	for (int x = 0; x < map_size; x++) {
		for (int y = 0; y < map_size; y++) {
			own_map[x][y].type = EMPTY;
		}
	}
}

PlayerId Player::get_id() const { return player_id; }

// Abstract class factory method
Player* Player::factory_method(PlayerType type, PlayerId id) {
	switch (type) {
		case CONSOLE_PLAYER:
			return static_cast<Player*>(new ConsolePlayer(id));
		case RANDOM_PLAYER:
			return static_cast<Player*>(new RandomPlayer(id));
		case SMART_PLAYER:
			return static_cast<Player*>(new SmartPlayer(id));
		default:
			assert(0 && "invalid player type");
	}
}

// map creating methods implementation:
void Player::place_ship(Point p1, Point p2, int ship_id) {
	int orientation = -1;
	
	// vertical case
	if (p1.x == p2.x) {
		orientation = 0;
	}
	// horisontal case
	else if (p1.y == p2.y) {
		orientation = 1;
	}
	else {
		assert(0 && "invalid orientation");
	}
	int st_x = p1.x - 1;
	int st_y = p1.y - 1;

	int en_x = p2.x + 1;
	int en_y = p2.y + 1;
	
	// mark surrounding ship cells as taken and set ship id
	for (int x = st_x; x <= en_x; x++) {
		
		for (int y = st_y; y <= en_y; y++) {
			if (x >= 0 && x < 10 && y >= 0 && y < 10) {
				own_map[x][y].is_taken = true;

				if (orientation == 0) {
					if (x == p1.x && y >= p1.y && y <= p2.y) {
						own_map[x][y].ship_id = ship_id;
						own_map[x][y].type = UNHITTED;
					}
				}
				if (orientation == 1) {
					if (y == p1.y && x >= p1.x && x <= p2.x) {
						own_map[x][y].ship_id = ship_id;
						own_map[x][y].type = UNHITTED;
					}
				}
			}
		}
	}
}

bool Player::check_collision(Point p1, Point p2) {
	int dx = 0;
	int dy = 0;
	int ship_size = 0;

	// horisontal case
	if (p1.y == p2.y) {
		dx = 1;
		ship_size = abs(p1.x - p2.x) + 1;
	}
	// vertical case
	else if (p1.x == p2.x) {
		dy = 1;
		ship_size = abs(p1.y - p2.y) + 1;
	}
	else{
		assert(0 && "invalid ship placement");
	}

	int x = p1.x;
	int y = p1.y;

	for (int count = 0; count < ship_size; count++) {
		if (x < 0 || x > 9) {
			return true;
		}
		if (y < 0 || y > 9) {
			return true;
		}
		if (own_map[x][y].is_taken) {
			return true;
		}
		x += dx;
		y += dy;
	}
	// no collision
	return false;
}

// updates player's own_map and ships after enemy move
GameStatus Player::check_hit(int x, int y) {
	Cell cell = own_map[x][y];
	CellType type = cell.type;

	// check is cell hitted
	if (type == HITTED || type == EMPTY_HITTED) {
		return BITTED;
	}
	// empty cell case (FALL)
	else if (type == EMPTY) {
		own_map[x][y].type = EMPTY_HITTED;
		return FALL;
	}
	// cell with ship
	else if (type == UNHITTED) {
		assert(cell.ship_id >= 0 && "no ship id on cell with ship");
		// update cell
		own_map[x][y].type = HITTED;
		// update ship
		ships[cell.ship_id].hit();
		
		if (ships[cell.ship_id].is_alive()) {
			// ship is steel alive
			return HIT;
		}
		// ship was killed
		return KILL;
	}
	else {
		assert(0 && "cell can't be UNSEEN");
	}
}

// updates enemy map after move
void Player::update_enemy_map(int x, int y, GameStatus status) {
	// change cell from UNSEEN to HITTED
	if (status == HIT || status == KILL) {
		enemy_map[x][y].type = HITTED;
	}
	// change cell from UNSEEN to EMPTY_HITTED
	else if (status == FALL) {
		enemy_map[x][y].type = EMPTY_HITTED;
	}
	else {
		assert(0 && "no other possible move status here");
	}
}

// check all ships are dead or not
bool Player::has_alive_ships() {
	// traverse all ships
	for (int ship_id = 0; ship_id < max_ship_count; ship_id++) {
		if (ships[ship_id].is_alive()) {
			return true;
		}
	}
	return false;
}

// returns ship type (or noship), which is on (x,y) point
string Player::get_ship_type(int x, int y) {
	Cell cell = own_map[x][y];
	int id = cell.ship_id;

	if (id < 0) {
		return "noship";
	}
	if (id == 0) {
		return ship_types[0];
	}
	else if (id == 1 || id == 2) {
		return ship_types[1];
	}
	else if (id == 3 || id == 4 || id == 5) {
		return ship_types[2];
	}
	else if (id == 6 || id == 7 || id == 8 || id == 9) {
		return ship_types[3];
	}
	else {
		assert(0 && "invalid ship id");
	}
}

