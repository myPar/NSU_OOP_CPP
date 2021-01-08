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
const unordered_map<int, Node>* Data::get_map() const { return node_map; }

const list<int>* Data::get_pipe() const { return execute_pipe; }

// WorkflowSpec methods implementation:
int WorkflowSpec::get_arg_number(string name) {	//"readfile", "writefile", "grep", "sort", "replace", "dump"
	// 'name' should be a block name
	assert(arg_number_map.find(name) != arg_number_map.end() && "'name' should be a block name");
	
	return arg_number_map.find(name)->second;
}

bool WorkflowSpec::is_correct_name(string name) {
	return block_name_set.find(name) != block_name_set.end();
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
string Node::get_name() const { return block_name; }
int Node::get_arg_number() const { return arg_number; }
const string* Node::get_args() const { return args; }
