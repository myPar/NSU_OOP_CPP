#include <memory>
#include <cassert>
#include "GameExecutor.h"
#include "Player.h"
#include "GameState.h"
#include "ConsoleViewer.h"

void GameExecutor::execute(GameSettings settings) {
	int round_count = settings.get_rounds_number();
	Statistics statistic(round_count);
	GameViewer *viewer = GameViewer::factory_method(CONSOLE);
	unique_ptr<GameViewer> ptr(viewer);

	for (int round = 0; round < round_count; round++) {
		Player* player1 = Player::factory_method(settings.get_player1_type(), FIRST);
		unique_ptr<Player> player1_ptr(player1);

		Player* player2 = Player::factory_method(settings.get_player2_type(), SECOND);
		unique_ptr<Player> player2_ptr(player2);

		viewer->display(*player1);
		viewer->display(*player2);

		GameStatus status = HIT;
		int moves_count = 0;
		// at the game beginning current player is first player
		Player* current_player = player1;
			
		status = HIT;

		while (true) {
			// do move
			PlayerMove move = current_player->do_move();
			// increment number of moves
			moves_count++;

			// update players and Statistics
			status = GameState::update(move, player1, player2, &statistic, round, moves_count);

			// already bitted cell need to move again
			if (status == BITTED) {
				moves_count--;
				status = HIT;
			}
			else {
				viewer->display(*current_player);

				if (status == FALL){
					// change current player
					current_player = current_player->get_id() == FIRST ? player2 : player1;
				}
				else if (status == P1_WON || status == P2_WON) {
					break;
				}
				status = HIT;
			}
		}
		// check winner consistance
		assert(status == P1_WON || status == P2_WON);

		statistic.add_move_count(moves_count, round);
		statistic.add_vinner(status, round);
	}
	// print statistic at the end of the match
	statistic.print_statistics();
}
