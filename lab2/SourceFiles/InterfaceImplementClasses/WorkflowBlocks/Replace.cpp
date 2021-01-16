#include "Replace.h"

// ReadFile class implementation:
// constructor
Replace::Replace(Node n) : node(n) {}
// main block method
optional<vector<string>> *Replace::execute(optional<vector<string>> *input_data) {
	// check input data exists
	if (!input_data->has_value()) {
		throw BlockException(WorkflowBlockException::Types[4], "input data doesn't exist");
	}
	// gets patern and replacement
	string pattern = node.get_args()[0];
	string replacement = node.get_args()[1];

	for (vector<string>::iterator it = (*input_data)->begin(); it != (*input_data)->end(); ++it) {		
		size_t st_pos = 0;
		size_t len = pattern.length();

		// while pattern matches
		while ((st_pos = it->find(pattern)) != string::npos) {
			it->replace(st_pos, len, replacement);
		}
	}
	// return data
	return input_data;
}
