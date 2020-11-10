#include "Debugger.h"
// Debugger methods implementation
	// constructor
Debugger::Debugger(map<const string, std::unique_ptr<TritSet>> *s_map, unordered_set<string> *c_set): set_map(s_map), command_set(c_set){}

	// destructor
Debugger::~Debugger() {
	delete set_map;
	delete command_set;
}

// CommandParser methods implementation
Command Debugger::parse_command(string input_str) {
}
