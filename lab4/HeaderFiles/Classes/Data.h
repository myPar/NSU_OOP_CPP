#pragma once
#include <string>

// Data collectors classes definition
using namespace std;

static enum PlayerType {CONSOLE_PLAYER, RANDOM_PLAYER, SMART_PLAYER, UNKNOWN_PLAYER};
static enum PlayerId { FIRST, SECOND };

static const int map_size = 10;

static enum GameStatus {HIT, FALL, KILL, BITTED, P1_WON, P2_WON};	// current game status (the result of the last player's move)

static enum { ship_type_count = 4, max_ship_size = 4, max_ship_count = 10};
static const string ship_types[ship_type_count] = {"Battleship", "Destroyer", "Cruiser", "Boat"};

// Cell type enum for displaying
static enum CellType {UNSEEN, HITTED, UNHITTED, EMPTY, EMPTY_HITTED};

class GameSettings {
private:
	const PlayerType player1_type;
	const PlayerType player2_type;
	const int rounds_number;
public:
	// constructor
	GameSettings(PlayerType p1_type, PlayerType p2_type, int r_number);

	// field geter's:
	PlayerType get_player1_type() const;
	PlayerType get_player2_type() const;
	int get_rounds_number() const;
};

// move Data (Player & cordinates)
class PlayerMove {
private:
	const int x;
	const int y;
	const PlayerId id;
public:
	// constructor
	PlayerMove(int o_x, int o_y, PlayerId p_id);
	
	// geter's
	int get_x() const;
	int get_y() const;
	PlayerId get_id() const;
};

// Ship class
class Ship {
private:
	// hit points
	int hp;
	// unique ship id
	int ship_id;
	// ship type
	string ship_type;
	// alive state
	bool alive;
public:
	// constructors
	Ship(int id);
	Ship();
	// returns 'alive' field
	bool is_alive() const;
	// decrease hp on 1 point and update 'alive' state
	void hit();
	// get ship type
	string get_type() const;
	// get ship hp
	int get_hp() const;
};

// Game field Cell class
class Cell {
public:
	int ship_id;
	CellType type;
	bool is_taken;

	// constructor
	Cell(CellType c_type, int sh_id, bool is_t);
	// default constructor
	Cell();
	// geter's
	int get_ship_id() const;
	CellType get_type() const;
};

// Move description class player, move results (fall, hit, kill and s.o.)
// using by Statistics class for statistic collecting

class MoveDescriptor {
public:
	// cell cordinated
	int ox;
	int oy;
	// id of player which move was done
	PlayerId player_id;
	// was hit or fall
	bool has_hit;
	// was ship killed (only if was hit)
	bool killed;
	// type of hitted or killed ship
	string ship_type;

	MoveDescriptor(int x, int y, PlayerId p_id, bool hit, bool kill, string sh_type);
};

// help class of cordinate pair (use in map generation)
class Point {
public:
	int x;
	int y;

	Point(int x_, int y_);
	Point();
};
