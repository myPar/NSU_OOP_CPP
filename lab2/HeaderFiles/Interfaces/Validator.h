#pragma once
#include "Data.h"
// workflow validator Interface

class Validator {
protected:
	// check workflow blocks on simantic correctness (args number and s.o.)
	virtual void check_workflow_blocks(const unordered_map<int, Node> &block_map) = 0;
	// check workflow pipeline on simantic correctness
	virtual void check_workflow_pipe(const list<int> &pipe) = 0;
public:
	// main Validator function 
	virtual const Data& check_workflow(const Data& data) = 0;
	// function-factory for implement class object creating
	static Validator& factory_method();
};
