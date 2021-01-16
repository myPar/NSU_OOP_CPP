#include "GraphicViewer.h"

GraphicViewer::GraphicViewer() : 
window_width(WIDTH), window_height(HEIGHT)
{
	window = new RenderWindow(VideoMode(window_width, window_height), "Battleships");
	texture.loadFromFile("C:\\User_files\\sprite.png");
	rect_size = texture.getSize().x / rects_number;

	// init sprites
	empty = Sprite(texture);
	unseen = Sprite(texture);
	ship = Sprite(texture);
	hitship = Sprite(texture);
	hitempty = Sprite(texture);

	size_t offset = 0;
	empty.setTextureRect(IntRect(offset, 0, offset + rect_size, rect_size));
	offset += rect_size;

	unseen.setTextureRect(IntRect(offset, 0, offset + rect_size, rect_size));
	offset += rect_size;

	ship.setTextureRect(IntRect(offset, 0, offset + rect_size, rect_size));
	offset += rect_size;

	hitship.setTextureRect(IntRect(offset, 0, offset + rect_size, rect_size));
	offset += rect_size;

	hitempty.setTextureRect(IntRect(offset, 0, offset + rect_size, rect_size));
	offset += rect_size;
}

GraphicViewer::~GraphicViewer() {
	delete window;
}

void GraphicViewer::display_map(Cell map[map_size][map_size]) {

	for (int y = 0; y < map_size; y++) {
		// print x axis first
		for (int x = 0; x < map_size; x++) {
			Cell cell = map[x][y];
			CellType type = cell.get_type();

			if (type == UNSEEN) {
				unseen.setPosition(x * rect_size + x_offset, y * rect_size);
				window->draw(unseen);
			}
			else if (type == HITTED) {
				hitship.setPosition(x * rect_size + x_offset, y * rect_size);
				window->draw(hitship);
			}
			else if (type == UNHITTED) {
				ship.setPosition(x * rect_size + x_offset, y * rect_size);
				window->draw(ship);
			}
			else if (type == EMPTY) {
				empty.setPosition(x * rect_size + x_offset, y * rect_size);
				window->draw(empty);
			}
			else if (type == EMPTY_HITTED) {
				hitempty.setPosition(x * rect_size + x_offset, y * rect_size);
				window->draw(hitempty);
			}
		}
	}

}

void GraphicViewer::display(Player& player) {
	string title = "";

	if (player.get_id() == FIRST) {
		title = "FIRST";
	}
	else {
		title = "SECOND";
	}
	// clear window before displaying
	window->clear(Color::White);
	window->setTitle(title);

	display_map(player.own_map);
	x_offset = map_size * (rect_size + 2);
	display_map(player.enemy_map);
	x_offset = 0;
	window->display();
}
