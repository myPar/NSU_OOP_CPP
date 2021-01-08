#include "Grep.h"

// Grep class implementation:
	// Delete method
void Grep::Delete() { delete this; }

// constructor
Grep::Grep(Node n) : node(n) {}

// main block method
optional<vector<string>> *Grep::execute(optional<vector<string>> *input_data) {
	// check input data exists
	if (!input_data->has_value()) {
		throw BlockException(WorkflowBlockException::Types[2], "input data doesn't exist");
	}
	string pattern = node.get_args()[0];
	vector<string> result_data;

	// matching 'pattern' in data
	for (vector<string>::iterator it = (*input_data)->begin(); it != (*input_data)->end(); ++it) {
		string cur_str = *it;
		
		// remove string without match from vector 
		if (cur_str.find(pattern) != string::npos) {
			result_data.push_back(cur_str);
		}
	}
	// update data
	input_data->emplace(result_data);
	// return data
	return input_data;
}
