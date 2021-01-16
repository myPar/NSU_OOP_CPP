#include "Data.h"
#include <cassert>

// GameSettings class implementation:
GameSettings::GameSettings(PlayerType p1_type, PlayerType p2_type, int r_number) : 
	player1_type(p1_type), player2_type(p2_type), rounds_number(r_number){};

// field geter's:
PlayerType GameSettings::get_player1_type() const { return player1_type; }
PlayerType GameSettings::get_player2_type() const { return player2_type; }
int GameSettings::get_rounds_number() const { return rounds_number; }

// PlayerMove class implementation:
PlayerMove::PlayerMove(int o_x, int o_y, PlayerId p_id) : x(o_x), y(o_y), id(p_id) {};

// geter's
int PlayerMove::get_x() const { return x; }
int PlayerMove::get_y() const { return y; }
PlayerId PlayerMove::get_id() const { return id; }

// Ship class implementation:

// constructor
Ship::Ship(int sh_id) : ship_id(sh_id), alive(true) {
	hp = 0;
	
	// "Battleship" case
	if (ship_id == 0) {
		hp = 4;
		ship_type = ship_types[0];
	}
	// "Destroyer" case (id = 1 & id = 2)
	else if (ship_id == 1 || ship_id == 2) {
		hp = 3;
		ship_type = ship_types[1];
	}
	// "Cruiser" case (id = 3 & id = 4 & id = 5)
	else if (ship_id == 3 || ship_id == 4 || ship_id == 5) {
		hp = 2;
		ship_type = ship_types[2];
	}
	// "Boat" case (id = 6 & id = 7 & id = 8 & id = 9)
	else if (ship_id == 6 || ship_id == 7 || ship_id == 8 || ship_id == 9) {
		hp = 1;
		ship_type = ship_types[3];
	}
	else {
		assert(0 && "invalid ship type");
	}
}
// default constructor
Ship::Ship() : ship_id(0), ship_type(""), alive(false), hp(0) {}

// returns 'alive' field
bool Ship::is_alive() const { return alive; }

// get ship type
string Ship::get_type() const { return ship_type; }

// get ship hp
int Ship::get_hp() const { return hp; }

// decrease hp on 1 point and update 'alive' state
void Ship::hit() { 
	hp--;
	
	if (hp <= 0) {
		alive = false;
	}
}

// Cell class implementation:
Cell::Cell(CellType c_type, int sh_id, bool is_t) : type(c_type), ship_id(sh_id), is_taken(is_t) {};
// default constructor
Cell::Cell() : type(UNSEEN), ship_id(-1), is_taken(false) {};

// geter's
int Cell::get_ship_id() const { return ship_id; }
CellType Cell::get_type() const { return type; }

//MoveDescriptor class implementation
MoveDescriptor::MoveDescriptor(int x, int y, PlayerId p_id, bool hit, bool kill, string sh_type) :
	ox(x), oy(y), player_id(p_id), has_hit(hit), killed(kill), ship_type(sh_type){};


// Point class implementation
Point::Point(int x_, int y_) : x(x_), y(y_) {}
Point::Point() : x(-1), y(-1) {}