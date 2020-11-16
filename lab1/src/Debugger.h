#pragma once
#include "Trit.h"

#include <memory>
#include <map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <list>
// consts:
enum {max_size = 10, max_arg_number = 8};

// class implements user input command
class Command {
private:
	// command name
	string name;
	// option
	string option;
	// args
	string *args;
	// arg number
	size_t arg_number;
public:
	// get methods
	string get_name();
	string get_option();
	string* get_args();
	// constructor
	Command(string name, string option, size_t arg_number, string *args);
	// default constructor
	Command();
	// destructor
	~Command();
};

class Debugger {
	// Exception type enum
	enum ExceptionType {
		CommandParserException,
		CommandExecutorException
	};

	// Exception class
	class DebuggerException {
	private:
		ExceptionType exception_type;
		string exception_message;
	public:
		DebuggerException(ExceptionType type, string message);
		void print_exception();
	};

private:
	// map of TritSet pointers: key - tritSet unicue name, value - TritSet pointer
	map<const string, std::unique_ptr<TritSet>> *set_map;
	// string set of command names
	const unordered_set<string> command_set;
	const unordered_set<string> option_set;

	string* split(string *input_str, size_t* size);
public:
	// constructor
	Debugger();
	// destructor
	~Debugger();
// Debugger methods
	// main Debugger function, which do parsing of user input data and proccese trew exceptions
	void parse_user_input();

	// parse input user string and returns Command object
	Command parse_command(string *input_string);

	// execute parsed command
	void execute_command(Command command);
};
