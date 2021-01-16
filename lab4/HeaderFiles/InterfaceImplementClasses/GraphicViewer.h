#pragma once
#include "GameView.h"
#include <SFML/Graphics.hpp>

using namespace sf;
enum {rects_number = 5};
enum { WIDTH = 1000, HEIGHT = 720};

class GraphicViewer : GameViewer {
protected:
	void GameViewer::display_map(Cell map[map_size][map_size]) override;
	Texture texture;
	size_t rect_size;

	size_t window_height;
	size_t window_width;

	RenderWindow *window;

	// sprites
	Sprite empty;
	Sprite unseen;
	Sprite ship;
	Sprite hitship;
	Sprite hitempty;
	// map x axis offset
	size_t x_offset = 0;
public:
	GraphicViewer();
	~GraphicViewer();
	void GameViewer::display(Player& player) override;

	friend GameViewer* GameViewer::factory_method(ViewerType type);

};