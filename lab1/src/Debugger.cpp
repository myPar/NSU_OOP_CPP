#include "Debugger.h"

// constructor
Debugger::Debugger(map<const string, std::unique_ptr<TritSet>> *s_map, size_t s_count): 
	set_map(s_map), set_count(s_count), option(DebuggerMode){}

// destructor
Debugger::~Debugger() {
	// all Trit sets'll be deleted automatically by using unique_ptr
	delete(set_map);
}
