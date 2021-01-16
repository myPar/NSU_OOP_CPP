#pragma once
#include "Data.h"

class GameLauncher {
private:
	PlayerType get_player_type(string type_arg);
public:
	GameSettings parse_settings(int argc, char* argv[]);
};
