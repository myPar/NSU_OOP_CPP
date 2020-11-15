#include <list>

#include "Debugger.h"

// Command methods implementation
	//constructor
Command::Command(string name, string option, size_t arg_number, string *args) {
	Command::name = name;
	Command::option = option;
	Command::args = args;
	Command::arg_number = arg_number;
}
	//destructor
Command::~Command() {
	delete[] args;
}

// Debugger methods implementation
	// constructor
Debugger::Debugger(map<const string, std::unique_ptr<TritSet>>* s_map) : command_set({ "mkset", "initset", "prtset" }), option_set({"-b"}) {
	s_map = new map<const string, std::unique_ptr<TritSet>>();
}

	// destructor
Debugger::~Debugger() {
	delete set_map;
}

// Parse Command method implementation
Command Debugger::parse_command(string input_str) {
	size_t str_len = input_str.length();
	
	bool parsing = false;
	size_t st_idx = 0;
	size_t length = 0;
	
	string word_arr[max_size];
	size_t arr_idx = 0;

	// spliting string to substrings by ' '
	for (size_t i = 0; i < str_len; i++) {
		char ch = input_str[i];

		if (!parsing && ch != ' ') {
			st_idx = i;
			length = 1;
			parsing = true;
		}
		else if (parsing && ch != ' ') {
			length++;
		}
		else if (parsing && ch == ' ') {
			// take a substring (word)
			parsing = false;
			string word = input_str.substr(st_idx, length);
			word_arr[arr_idx] = word;
		}
	}
// check word list before construct Command obj
	// Command fields values
	string name = "";
	string opt = "";
	size_t arg_number = 0;
	string* args = new string[max_arg_number];
	size_t cur_args_idx = 0;

	for (size_t i = 0; i <= arr_idx; i++) {
		string word = word_arr[i];

		if (i == 0) {
			if (command_set.find(word) == command_set.end()) {
				throw DebuggerException(CommandParserException, "Incorrect command name \n");
			}
			name = word;
		}
		else if (i == 1 && word[0] == '-') {
			// check option
			if (option_set.find(word) == option_set.end()) {
				throw DebuggerException(CommandParserException, "Incorrect command option \n");
			}
			opt = word;
		}
		else {
			args[cur_args_idx++] = word;
			arg_number++;
		}
	}
	return Command(name, opt, arg_number, args);
}
