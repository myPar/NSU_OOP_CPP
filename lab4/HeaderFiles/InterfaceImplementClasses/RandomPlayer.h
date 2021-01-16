#pragma once

#include "Player.h"

class RandomPlayer : public Player {
private:
	// private constructor
	RandomPlayer(PlayerId p_id);

	// gets bound ship's points
	pair<Point, Point> get_random_points(int ship_hp);
public:
	PlayerMove Player::do_move() override;

	// frind factory method
	friend Player* Player::factory_method(PlayerType type, PlayerId id);
};
