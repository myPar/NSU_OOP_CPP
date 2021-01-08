#pragma once
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <string>
#include <cassert>

using namespace std;

// declaration of workflow specification
// used in Parser and Validator classes for workflow correctness checking
namespace WorkflowSpec {
	enum { block_number = 6 };
	// workflow block names
	static const string names[block_number] = { "readfile", "writefile", "grep", "sort", "replace", "dump" };
	static const unordered_set<string> block_name_set = { "readfile", "writefile", "grep", "sort", "replace", "dump" };
	static const unordered_map<string, int> arg_number_map = { {"readfile", 1}, {"writefile", 1}, {"grep", 1}, {"sort", 0}, {"replace", 2}, {"dump", 1} };

	// check block name correctness
	bool is_correct_name(string name);
	// get number of arguments for such block name
	int get_arg_number(string name);
}

// represents workflow node (block with name and args)
class Node {
private:
	// block name
	string block_name;
	// number of arguments
	int arg_number;
	// argument's array
	string* args;
public:
	// vield geter's mthods
	string get_name() const;
	int get_arg_number() const;
	const string* get_args() const;
	// Constructor
	Node(string name, int arg_n, string *ptr);
	// copy-Constructor
	Node(const Node& node);
	//Destructor
	~Node();
};

// class presents workflow data: 
// *hash_map of pairs - idx--workflow block definition
// *executing pipeline

class Data {
private:
	// map of indices and workflow block definition
	unordered_map<int, Node>* const node_map;
	// idx1->idx4->idx0->...->idxn (workflow pipeline)
	list<int>* const execute_pipe;
public:
	// field get'ers:
	const unordered_map<int, Node>* get_map() const;
	const list<int>* get_pipe() const;
	// Constructor & Destructor:
	Data(unordered_map<int, Node>* map, list<int>* pipe);
	~Data();
};
