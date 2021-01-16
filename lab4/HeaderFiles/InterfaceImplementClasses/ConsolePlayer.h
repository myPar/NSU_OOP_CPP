#pragma once
#include "Player.h"

class ConsolePlayer : public Player{
private:
	// private constructor
	ConsolePlayer(PlayerId p_id);
public:
	PlayerMove Player::do_move() override;

	// frind factory method
	friend Player* Player::factory_method(PlayerType type, PlayerId id);
};
