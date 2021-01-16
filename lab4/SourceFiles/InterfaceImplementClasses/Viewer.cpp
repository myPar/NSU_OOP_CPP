#include <cassert>
#include "GameView.h"
#include "ConsoleViewer.h"
#include "GraphicViewer.h"

GameViewer* GameViewer::factory_method(ViewerType type) {
	if (type == CONSOLE) {
		return static_cast<GameViewer*>(new ConsoleViewer());
	}
	else if (type == GRAPHIC) {
		return static_cast<GameViewer*>(new GraphicViewer());
	}
	else {
		assert(0 && "invalid viewer type");
	}
}
