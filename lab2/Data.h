#pragma once
#include <unordered_map>
#include <list>
#include <string>

using namespace std;

// declaration of workflow specification
// used in Parser and Validator classes for workflow correctness checking
namespace WorkflowSpec {
	enum { block_number = 6 };
	// workflow block names
	static const string BlockNames[block_number] = { "readfile", "writefile", "grep", "sort", "replace", "dump" };

	// check block name correctness
	bool check_name(string name);
	// check correctness of args number in such block
	bool check_arg_number(string block_name);
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
	const string get_name();
	const int get_arg_number();
	const string* const get_args();
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
	const unordered_map<int, Node>* const get_map();
	const list<int>* const get_pipe();
	// Constructor & Destructor:
	Data(unordered_map<int, Node>* map, list<int>* pipe);
	~Data();
};
