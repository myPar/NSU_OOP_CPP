#include "SmartPlayer.h"

SmartPlayer::SmartPlayer(PlayerId id) : Player(id) {
	place_ship(Point(0, 0), Point(0, 3), 0);
	place_ship(Point(2, 0), Point(4, 0), 1);
	place_ship(Point(2, 2), Point(2, 4), 2);
	place_ship(Point(0, 5), Point(0, 6), 3);
	place_ship(Point(6, 0), Point(7, 0), 4);
	place_ship(Point(4, 2), Point(5, 2), 5);
	place_ship(Point(0, 9), Point(0, 9), 6);
	place_ship(Point(4, 9), Point(4, 9), 7);
	place_ship(Point(9, 4), Point(9, 4), 8);
	place_ship(Point(8, 7), Point(8, 7), 9);
}

bool SmartPlayer::has_point(Point point) {
	for (list<Point>::iterator it = p_list.begin(); it != p_list.end(); ++it) {
		if (it->x == point.x && it->y == point.y) {
			return true;
		}
	}
	return false;
}

PlayerMove SmartPlayer::do_move() {
	int result_x = -1;
	int result_y = -1;

	// check new hitted cell
	for (int x = 0; x < map_size; x++) {

		for (int y = 0; y < map_size; y++) {

			if (enemy_map[x][y].type == HITTED) {
				if (!has_point(Point(x,y)) && !p_list.empty()) {
					// save previous data
					int last_x = p_list.back().x;
					int last_y = p_list.back().y;
					// update last hitted point
					p_list.push_back(Point(x, y));
					// get dx and dy
					int dx = (x - last_x) / abs(x - last_x);
					int dy = (y - last_y) / abs(y - last_y);

					result_x = x + dx;
					result_y = y + dy;

					if (result_x < 0 || result_x > 9 || result_y < 0 || result_y > 9) {
						return PlayerMove(rand() % 10, rand() % 10, player_id);
					}
					else {
						return PlayerMove(result_x, result_y, player_id);
					}
				}
			}
		}
	}
	return PlayerMove(rand() % 10, rand() % 10, player_id);
}
