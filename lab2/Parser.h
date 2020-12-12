#pragma once
#include <unordered_map>
#include <fstream>
#include "Node.h"
#include "Data.h"

// Workflow Parser Interface
using namespace std;

class Parser {
protected:
	// parse workflow blocks declaration and check it on syntax correction
	virtual unordered_map<int, Node>* const parse_nodes(ifstream *input) = 0;
	// parse workflow pipeline and check it on syntax correctness and on difference
	virtual list<int>* const parse_pipe(ifstream* input) = 0;
public:
	// main parse function
	virtual const Data &parse_workflow(string input_file_name) = 0;
	// function-factory for implement class object creating
	static Parser *factory_method();
	// virtual destructor
	virtual ~Parser() = 0;
};