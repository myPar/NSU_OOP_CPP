#pragma once
#include <vector>
#include "Data.h"

using namespace std;

class Statistics {
private:
	vector<MoveDescriptor> statistic;

	// number of rounds
	int rounds_number;
	// numbers of moves in each round
	int* round_moves_count;
	// winners array in each round
	GameStatus* winners;
public:
	Statistics(int rounds_count);
	~Statistics();

	void print_statistics();
	
	// statistics writing methods
	void add_move(MoveDescriptor move);
	void add_vinner(GameStatus winner, int round);
	void add_move_count(int count, int round);
};
