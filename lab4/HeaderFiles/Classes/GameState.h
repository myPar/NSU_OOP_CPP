#pragma once
#include "Data.h"
#include "Player.h"
#include "Statistics.h"

class GameState {
public:
	GameStatus update(PlayerMove move, Player *player1, Player *player2, Statistics *statistic, int round, int move_count);
};
