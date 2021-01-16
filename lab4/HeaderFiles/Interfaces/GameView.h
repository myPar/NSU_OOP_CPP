#pragma once
#include "Player.h"
enum ViewerType {CONSOLE, GRAPHIC};

class GameViewer {
protected:
	virtual void display_map(Cell map[map_size][map_size]) = 0;
public:
	virtual void display(Player& player) = 0;

	static GameViewer* factory_method(ViewerType type);
};
