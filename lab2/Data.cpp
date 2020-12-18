#include "Data.h"

// Data class implementation:
	// Data constructor
Data::Data(unordered_map<int, Node>* map, list<int>* pipe):node_map(map), execute_pipe(pipe) {}
	// Data destructor
Data::~Data() {
	delete node_map;
	delete execute_pipe;
}
	// field getters:
const unordered_map<int, Node>* const Data::get_map() { return node_map; }

const list<int>* const Data::get_pipe() { return execute_pipe; }

// WorkflowSpec methods implementation:
bool WorkflowSpec::check_arg_number(string name) {
	return true;
}

bool WorkflowSpec::check_name(string name) {
	return true;
}

// Node class implementation:
	// constructor
Node::Node(string name, int arg_n, string* ptr):block_name(name), arg_number(arg_n), args(ptr) {}
	// destructor
Node::~Node() {
	delete[] args;
}
	// copy-costructor
Node::Node(const Node& src): block_name(src.block_name), arg_number(src.arg_number) {
	string* copy = new string[arg_number];
	// copy data:
	for (size_t i = 0; i < (size_t)arg_number; i++) {
		copy[i] = src.args[i];
	}
	// update args:
	args = copy;
}
	// field getters:
const string Node::get_name() { return block_name; }
const int Node::get_arg_number() { return arg_number; }
const string* const Node::get_args() { return args; }
