#pragma once
#include "Trit.h"

#include <memory>
#include <map>
#include <string>
#include <iostream>

class Debugger {
// debugger subclasses
	// class implements user input command
	class Command {
	private:
		// command name
		string name;
		// option
		string option;
		// args
		std::unique_ptr<string[]> args;
	public:
		// get methods
		string get_name();
		string get_option();
		string *get_args();
		// constructor
		Command(string name, string option, string* args);
		// destructor
		~Command();
	};
	// parse input user string and recognizes the command
	class CommandParser {
	public:
		Command parse_command(string input_string);
	};
	// executes input command
	class CommandExecutor {
	public:
		void execute_command(Command command);
	};

	enum Option{ObjectMode, UpOnObjectsMode, DebuggerMode};
private:
	// map of TritSet pointers: key - tritSet unicue name, value - TritSet pointer
	map<const string, std::unique_ptr<TritSet>> *set_map;
	// count of TritSets in the map
	size_t set_count;
	// current option (by default - debugger mode)
	Option option;
public:
	// constructor
	Debugger(map<const string, std::unique_ptr<TritSet>> *s_map, size_t s_count);
	// destructor
	~Debugger();
// Debugger methods
	// clear Debugger data
	void clear();

//	Debugger Exception handling
	// Exception type enum
	enum ExceptionType {
		CommandParserException,
		CommandExecutor
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
};
