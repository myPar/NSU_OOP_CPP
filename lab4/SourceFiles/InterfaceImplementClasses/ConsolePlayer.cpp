#include "ConsolePlayer.h"
#include <iostream>

ConsolePlayer::ConsolePlayer(PlayerId id): Player(id) {
	if (id == FIRST) {
		cout << "FIRST player ship placing:\n\n";
	}
	else {
		cout << "SECOND player ship placing:\n\n";
	}

	for (int ship_id = 0; ship_id < max_ship_count; ship_id++) {
		bool colision = true;
		int ship_size = ships[ship_id].get_hp();
		Point p1(0, 0);
		Point p2(0, 0);

		while (colision) {
			int x = 0;
			int y = 0;
			char orientation = '0';

			cout << "enter start point 'x':\n";
			cin >> x;
			if (x < 0 || x > 9) {
				cout << "invalid 'x'\n";
				continue;
			}

			cout << "enter start point 'y':\n";
			cin >> y;
			if (y < 0 || y > 9) {
				cout << "invalid 'y'\n";
				continue;
			}

			cout << "enter ship orientation:\n";
			cin >> orientation;
			if (orientation != 'h' && orientation != 'v') {
				cout << "invalid ship orintation character\n";
				continue;
			}
			int dx = 0;
			int dy = 0;

			if (orientation == 'h') {
				dx += (ship_size - 1);
			}
			else {
				dy += (ship_size - 1);
			}
			
			p1.x = x;
			p1.y = y;

			p2.x = x + dx;
			p2.y = y + dy;

			colision = check_collision(p1, p2);
			
			if (colision) {
				cout << "ship collision\n";
			}
		}
		place_ship(p1, p2, ship_id);
	}
}

PlayerMove ConsolePlayer::do_move() {
	int x = -1;
	int y = -1;
	
	if (player_id == FIRST) {
		cout << "turn of FIRST player:\n";
	}
	else {
		cout << "turn of SECOND player:\n";
	}

	cout << "enter 'x'\n";
	cin >> x;

	cout << "enter 'y'\n";
	cin >> y;

	return PlayerMove(x, y, player_id);
}

