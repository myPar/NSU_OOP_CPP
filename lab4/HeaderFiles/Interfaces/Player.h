#pragma once
#include "Data.h"

// Player Abstract class
class Player {
protected:
	friend class ConsoleViewer;
	friend class GraphicViewer;
	// ship idx is equal its id
	Ship ships[max_ship_count];
	// maps:
	Cell own_map[map_size][map_size];	// for display and hittance checking
	Cell enemy_map[map_size][map_size];	// just to display (doesn't contain enemy ships data)
	// Player's id
	PlayerId player_id;
	// place new ship on map
	void place_ship(Point p1, Point p2, int ship_id);
	// check collision while placing ship
	bool check_collision(Point p1, Point p2);
public:
	// constructor
	Player(PlayerId id);
	// player move method
	virtual PlayerMove do_move() = 0;

	// factory method
	static Player* factory_method(PlayerType type, PlayerId id);

	// this function check hit in point (x,y) 
	// updates player's own_map and ships after enemy move
	GameStatus check_hit(int x, int y);
	
	// updates enemy map after move
	void update_enemy_map(int x, int y, GameStatus status);

	// check all ships are dead or not
	bool has_alive_ships();

	// returns ship type (or noship), which is on (x,y) point
	string get_ship_type(int x, int y);
	
	// gets player id
	PlayerId get_id() const;
};
