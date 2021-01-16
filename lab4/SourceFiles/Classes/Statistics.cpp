#include <iostream>
#include "Statistics.h"
#include <cassert>

void Statistics::print_statistics() {
	size_t vector_idx = 0;

	for (int round = 0; round < rounds_number; round++) {
		cout << "Round " << round + 1 << ":\n\n";
		
		for (int i = 0; i < round_moves_count[round]; i++) {
			MoveDescriptor descriptor = statistic[vector_idx++];
			
			if (descriptor.player_id == FIRST) {
				cout << "FIRST player: ";
			}
			else {
				cout << "SECOND player: ";
			}
			cout << "move: x = " << descriptor.ox << " y = " << descriptor.oy << "; ";
			
			if (descriptor.has_hit) {
				if (descriptor.killed) {
					cout << "KILLED ";
				}
				else {
					cout << "HITTED ";
				}
				cout << descriptor.ship_type << endl;
			}
			else {
				cout << "FALL\n";
			}
		}
		string winner = "";

		if (winners[round] == P1_WON) {
			winner = "FIRST PLAYER";
		}
		else if (winners[round] == P2_WON) {
			winner = "SECOND PLAYER";
		}
		else {
			assert(0 && "invalid vinner");
		}
		cout << "WINNER in round " << round + 1 << " is " << winner << endl << endl;
	}
}
// add new MoveDescriptor to vector
void Statistics::add_move(MoveDescriptor move) {
	statistic.push_back(move);
}
void Statistics::add_vinner(GameStatus winner, int round) {
	winners[round] = winner;
}
void Statistics::add_move_count(int count, int round) {
	round_moves_count[round] = count;
}

// Statistics constructor
Statistics::Statistics(int rounds_count) {
	winners = new GameStatus[rounds_count];
	round_moves_count = new int[rounds_count];
	rounds_number = rounds_count;
}
// Statistics destructor
Statistics::~Statistics() {
	delete[] winners;
	delete[] round_moves_count;
}


