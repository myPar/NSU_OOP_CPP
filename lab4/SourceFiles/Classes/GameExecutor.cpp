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
		Player* player2 = Player::factory_method(settings.get_player2_type(), SECOND);
		viewer->display(*player1);
		viewer->display(*player2);
		GameState state;

		GameStatus status = HIT;
		int moves_count = 0;

		while (true) {
			status = HIT;
			// while hit do move
			while (status == HIT || status == KILL) {
				// do move
				PlayerMove move1 = player1->do_move();
				// increment number of moves
				moves_count++;

				// update players and Statistics
				status = state.update(move1, player1, player2, &statistic, round, moves_count);
				
				// already bitted cell need to move again
				if (status == BITTED) {
					moves_count--;
					status = HIT;
				}
				else {
					viewer->display(*player1);
				}
			}
			if (status == P1_WON) {
				break;
			}
			status = HIT;

			// while hit do move
			while (status == HIT || status == KILL) {
				// do move
				PlayerMove move2 = player2->do_move();
				// increment number of moves
				moves_count++;

				// update players and Statistics
				status = state.update(move2, player1, player2, &statistic, round, moves_count);

				// already bitted cell need to move again
				if (status == BITTED) {
					moves_count--;
					status = HIT;
				}
				else {
					viewer->display(*player2);
				}
			}
			if (status == P2_WON) {
				break;
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
