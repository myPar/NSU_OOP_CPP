#pragma once
#include <optional>
#include <string>
#include <vector>
#include <fstream>
#include "Data.h"

using namespace std;

namespace WorkflowBlockException {
	enum { type_number = 6 };
	static const string Types[type_number] = { "ReadFile", "WriteFile", "Grep", "Sort", "Replace", "Dump" };
}

class BlockException {
private:
	string type;
	string message;
public:
	void print_exception();
	BlockException(string t, string m);
};

class Block {

public:
	// virtual destructor
	virtual ~Block() {}
	// main workflow block method
	virtual optional<vector<string>> *execute(optional<vector<string>> *input) = 0;
	// factory method for creating workflow blocks
	static Block* factory_method(const Node node);
};
