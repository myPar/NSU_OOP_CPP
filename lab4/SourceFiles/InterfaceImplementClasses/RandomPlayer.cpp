#include <cstdlib>
#include <cassert>
#include "RandomPlayer.h"

RandomPlayer::RandomPlayer(PlayerId p_id) : Player(p_id){
	for (int ship_id = 0; ship_id < max_ship_count; ship_id++) {
		// place ship:
		pair<Point, Point> points = get_random_points(ships[ship_id].get_hp());	// get points
		place_ship(points.first, points.second, ship_id);
	}
}

pair<Point, Point> RandomPlayer::get_random_points(int ship_hp) {
	bool collision = true;
	Point point1(0,0);
	Point point2(0,0);

	while (collision) {
		int rand_x = rand() % 10;
		assert(rand_x >= 0 && rand_x < 10 && "invalid point range");
		int rand_y = rand() % 10;
		assert(rand_y >= 0 && rand_y < 10 && "invalid point range");
		// create first point
		point1.x = rand_x;
		point1.y = rand_y;

		// set orientation
		int orientation = rand() % 2;
		assert(orientation >= 0 && orientation < 2 && "invalid orientation");

		// horisontal case
		if (orientation == 0) {
			point2.y = point1.y;
			point2.x = point1.x + ship_hp - 1;
		}
		// vertical case
		else {
			point2.y = point1.y + ship_hp - 1;
			point2.x = point1.x;
		}
		collision = check_collision(point1, point2);
	}
	// return points
	return pair<Point, Point>(point1, point2);
}

PlayerMove RandomPlayer::do_move() {
	int rand_x = rand() % 10;
	assert(rand_x >= 0 && rand_x < 10 && "invalid point range");
	int rand_y = rand() % 10;
	assert(rand_y >= 0 && rand_y < 10 && "invalid point range");

	return PlayerMove(rand_x, rand_y, get_id());
}
