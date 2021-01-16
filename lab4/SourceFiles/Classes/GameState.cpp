#include "GameState.h"
#include <cassert>

GameStatus GameState::update(PlayerMove move, Player* player1, Player* player2, Statistics *statistic, int round, int move_count) {
	Player* mover = nullptr;
	Player* waiter = nullptr;
	PlayerId id = move.get_id();

	// get mover and waiter
	if (id == FIRST) {
		mover = player1;
		waiter = player2;
	}
	else if (id == SECOND) {
		mover = player2;
		waiter = player1;
	}
	else {
		assert(0 && "invalid player id");
	}
	int hit_x = move.get_x();
	int hit_y = move.get_y();

	// update players:
	GameStatus move_status = waiter->check_hit(hit_x, hit_y);
	
	// already bitted cell, need to move again
	if (move_status == BITTED) {
		return move_status;
	}
	mover->update_enemy_map(hit_x, hit_y, move_status);
	
	// update Statistics:
	if (move_status == FALL) {
		statistic->add_move(MoveDescriptor(hit_x, hit_y, id, false, false, "noship"));
	}
	else if (move_status == HIT) {
		string ship_type = waiter->get_ship_type(hit_x, hit_y);
		assert(ship_type != "noship" && "invalid hit coordinates");

		statistic->add_move(MoveDescriptor(hit_x, hit_y, id, true, false, ship_type));
	}
	else if (move_status == KILL) {
		string ship_type = waiter->get_ship_type(hit_x, hit_y);
		assert(ship_type != "noship" && "invalid hit coordinates");
		
		// is all ships are dead mover WON
		if (!waiter->has_alive_ships()) {
			if (id == FIRST) {
				move_status = P1_WON;
			}
			else {
				move_status = P2_WON;
			}
			// add winner in this round
			statistic->add_vinner(move_status, round);
			// add move count in this round
			statistic->add_move_count(move_count, round);
		}
		statistic->add_move(MoveDescriptor(hit_x, hit_y, id, true, true, ship_type));
	}
	else {
		assert(0 && "invalid move status");
	}
	// return move status
	return move_status;
}
