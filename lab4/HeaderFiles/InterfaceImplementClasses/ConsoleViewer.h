#pragma once
#include "GameView.h"
#include "Data.h"

class ConsoleViewer : public GameViewer {
protected:
	void GameViewer::display_map(Cell map[map_size][map_size]) override;
public:
	void GameViewer::display(Player& player) override;

	friend GameViewer* GameViewer::factory_method(ViewerType type);
};
