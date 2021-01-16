#pragma once

#include "Player.h"
#include <list>

class SmartPlayer : public Player {
private:
	list<Point> p_list;
	bool has_point(Point point);
	// private constructor
	SmartPlayer(PlayerId p_id);
public:
	PlayerMove Player::do_move() override;
	
	// friend factory method
	friend Player* Player::factory_method(PlayerType type, PlayerId id);
};

