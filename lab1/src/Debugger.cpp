#include <iostream>
#include <list>
#include <string>

#include "Debugger.h"

// DebuggerException methods implementation
	//constructor
Debugger::DebuggerException::DebuggerException(ExceptionType type, string message) {
	exception_type = type;
	exception_message = message;
}

// print exception method
void Debugger::DebuggerException::print_exception() {
	cout << "exception of type: " << exception_type << " " << exception_message << endl;
}

// Command methods implementation
	//constructor
Command::Command(string name, string option, size_t arg_number, string* args) {
	Command::name = name;
	Command::option = option;
	Command::args = args;
	Command::arg_number = arg_number;
}
// default constructor
Command::Command() {
	Command::name = "";
	Command::option = "";
	Command::args = nullptr;
	Command::arg_number = 0;
}
//destructor
Command::~Command() {
	delete[] args;
	cout << "Command destructor executed" << endl;
}

// print data method
void Command::print_command() {
	cout << "name: " << name << endl;
	cout << "option: ";

	if (option == "") {
		cout << "no option" << endl;
	}
	else {
		cout << option << endl;
	}
	cout << arg_number << " args: ";

	for (size_t i = 0; i < arg_number; i++) {
		cout << args[i] << " ";
	}
	cout << endl;
}
// Debugger methods implementation
	// constructor
Debugger::Debugger() : command_set({ "mkset", "initset", "prtset" }), option_set({ "-b" }) {
	set_map = new map<const string, std::unique_ptr<TritSet>>();
}

// destructor
Debugger::~Debugger() {
	delete set_map;
}
// split string by ' ' method
string* Debugger::split(string* input_str, size_t* size) {
	size_t str_len = input_str->length();

	bool parsing = false;
	size_t st_idx = 0;
	size_t length = 0;

	string* word_arr = new string[max_size];
	size_t arr_idx = 0;

	for (size_t i = 0; i < str_len; i++) {
		char ch = (*input_str)[i];

		if (!parsing && ch != ' ') {
			st_idx = i;
			length = 1;
			parsing = true;
			continue;
		}
		if (parsing && ch != ' ') {
			length++;
		}
		if (parsing && (ch == ' ' || i == str_len - 1)) {
			// take a substring (word)
			if (arr_idx >= max_size) {
				throw DebuggerException(CommandParserException, "too large input string");
			}

			parsing = false;
			string word = input_str->substr(st_idx, length);
			word_arr[arr_idx++] = word;
		}
	}
	*size = arr_idx;

	return word_arr;
}

// Parse Command method implementation
Command Debugger::parse_command(string* input_str) {
	// split input string by ' '
	size_t arr_lengt = 0;
	string* word_arr = split(input_str, &arr_lengt);

	// check word list before construct Command obj
		// Command fields values
	string name = "";
	string opt = "";
	size_t arg_number = 0;
	string* args = new string[max_arg_number];
	size_t cur_args_idx = 0;

	for (size_t i = 0; i < arr_lengt; i++) {
		string word = word_arr[i];

		if (i == 0) {
			if (command_set.find(word) == command_set.end()) {
				delete[] args;
				delete[] word_arr;
				throw DebuggerException(CommandParserException, "Incorrect command name");
			}
			name = word;
		}
		else if (i == 1 && word[0] == '-') {
			// check option
			if (option_set.find(word) == option_set.end()) {
				delete[] args;
				delete[] word_arr;
				throw DebuggerException(CommandParserException, "Incorrect command option");
			}
			opt = word;
		}
		else {
			args[cur_args_idx++] = word;
			arg_number++;
		}
	}
	delete[] word_arr;

	return Command(name, opt, arg_number, args);
}

void Debugger::parse_user_input() {
	while (true) {
		string* input_string = new string();
		getline(cin, *input_string);

		Command command;

		try {
			command = parse_command(input_string);
			delete input_string;
		}
		catch (DebuggerException exception) {
			delete input_string;
			exception.print_exception();
			continue;
		}
		cout << "interpreted command:\n";
		command.print_command();
		try {
			// command executor calling
		}
		catch (DebuggerException exception) {
			exception.print_exception();
			continue;
		}
	}
}