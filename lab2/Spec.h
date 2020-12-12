#pragma once
#include <string>
using namespace std;
// declaration of workflow specification
// used in Parser and Validator classes for workflow correctness checking
namespace WorkflowSpec {
	enum {block_number = 6};
	// workflow block names
	static const string BlockNames[block_number] = {"readfile", "writefile", "grep", "sort", "replace", "dump"};
	
	// check block name correctness
	bool check_name(string name);
	// check correctness of args number in such block
	bool check_arg_number(string block_name);
}
