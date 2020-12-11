#pragma once
#include <unordered_map>
#include <list>
#include "Node.h"

using namespace std;
// class presents workflow data: 
// *hash_map of pairs - idx--workflow block definition
// *executing pipeline

class Data {
private:
	// map of indices and workflow block definition
	unordered_map<int, Node> *const node_map;
	// idx1->idx4->idx0->...->idxn (workflow pipeline)
	list<int> *const execute_pipe;
public:
	// field get'ers:
	unordered_map<int, Node>* const get_map();
	list<int>* const get_pipe();
	// Constructor & Destructor:
	Data();
	~Data();
};

