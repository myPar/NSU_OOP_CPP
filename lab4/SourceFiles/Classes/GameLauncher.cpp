#include <memory>
#include <cassert>
#include <iostream>
#include "optionparser.h"
#include "GameLauncher.h"

// returns player type by option arg value
PlayerType GameLauncher::get_player_type(string type_arg) {
	if (type_arg == "random") {
		return RANDOM_PLAYER;
	}
	if (type_arg == "smart") {
		return SMART_PLAYER;
	}
	if (type_arg == "console") {
		return CONSOLE_PLAYER;
	}
	else {
		return UNKNOWN_PLAYER;
	}
}

GameSettings GameLauncher::parse_settings(int argc, char *argv[]) {
	enum OptionIndex {HELP, COUNT, FIRST, SECOND, UNKNOWN};
	enum {max_option_count = 10, max_arg_count = 10};
	//
	const option::Descriptor usage[] = 
	{ 
		{HELP, 0, "h", "help", option::Arg::None, "-h --help \tprint message with arg list description and shutting down \n"},
		{COUNT, 0, "c", "count", option::Arg::Optional, "-c --count \tset number of game rounds. Default: 1\n"},
		{FIRST, 0, "f", "first", option::Arg::Optional, "-f --first  \tset first player type. Default: RandomPlayer\n"},
		{SECOND, 0, "s", "second", option::Arg::Optional, "-s --second \tset first player type. Default: RandomPlayer\n"},
		{UNKNOWN, 0, "", "", option::Arg::None, "unknown option, run programm with --help or -h key to see options description\n"},
	};
	// skip program name argv[0] if present
	argc -= (argc > 0);
	argv += (argc > 0);
	
	option::Option *options = new option::Option[max_option_count];
	// move options array under unique_ptr
	unique_ptr<option::Option> options_ptr(options);

	option::Option* buffer = new option::Option[max_arg_count];
	// move buffer array under unique_ptr
	unique_ptr<option::Option> buffer_ptr(buffer);

	// parse arguments
	option::Parser parse(usage, argc, argv, options, buffer);

	if (parse.error()) {
		cout << "exception while option parsing\n";
		exit(1);
	}
	// game default settings
	PlayerType player1_type = RANDOM_PLAYER;
	PlayerType player2_type = RANDOM_PLAYER;
	int round_count = 1;

	// check unknown option
	if (options[UNKNOWN]) {
		cout << "unknown option: " << options[UNKNOWN].name << endl;
		exit(1);
	}
	// check 'help' option
	if (options[HELP]) {
		cout << "Program options:\n";
		cout << "-h --help \tprint message with arg list description and shutting down \n";
		cout << "-c --count \tset number of game rounds. Default: 1\n";
		cout << "-f --first  \tset first player type. Default: RandomPlayer\n";
		cout << "-s --second \tset first player type. Default: RandomPlayer\n";
		exit(0);
	}
	// check 'count' option
	option::Option count_option = options[COUNT];

	if (count_option) {
		if (count_option.arg) {
			string arg_str(count_option.arg);
			int count = -1;

			try {
				count = stoi(arg_str, nullptr, 10);
			}
			catch (invalid_argument e) {
				cout << "invalid 'count' option argument\n";
				exit(1);
			}
			// init
			round_count = count;
		}
		else {
			cout << "no arg in option 'count'\n";
			exit(1);
		}
	}
	// check 'first' option
	option::Option first_option = options[FIRST];

	if (first_option) {
		if (first_option.arg > 0) {
			string arg_str(first_option.arg);
			
			PlayerType type = get_player_type(arg_str);
			if (type == UNKNOWN_PLAYER) {
				cout << "unknown arg in option 'first'\n";
				exit(1);
			}
			player1_type = type;
		}
		else {
			cout << "no arg in option 'first'\n";
			exit(1);
		}
	}
	// check 'second' option
		// check 'first' option
	option::Option second_option = options[SECOND];

	if (second_option) {
		if (second_option.arg > 0) {
			string arg_str(second_option.arg);

			PlayerType type = get_player_type(arg_str);
			if (type == UNKNOWN_PLAYER) {
				cout << "unknown arg in option 'second'\n";
				exit(1);
			}
			player2_type = type;
		}
		else {
			cout << "no arg in option 'second'\n";
			exit(1);
		}
	}
	// return GameSettings object
	return GameSettings(player1_type, player2_type, round_count);
}
