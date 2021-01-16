#include "Sort.h"

// Sort class implementation:
// constructor
Sort::Sort(Node n) : node(n) {}
// main block method
optional<vector<string>> *Sort::execute(optional<vector<string>> *input_data) {
	// check input data exists
	if (!input_data->has_value()) {
		throw BlockException(WorkflowBlockException::Types[3], "input data doesn't exist");
	}
	// set of sorted strings
	map<string, int> sorted_str_map;
	
	// insert data to set
	for (vector<string>::iterator it = (*input_data)->begin(); it != (*input_data)->end(); ++it) {
		// increment string count
		sorted_str_map[*it]++;
	}
	// clear data
	input_data->emplace();

	// update data
	for (map<string, int>::iterator it = sorted_str_map.begin(); it != sorted_str_map.end(); ++it) {
		int count = it->second;
		string str = it->first;

		// insert current string 'count' times
		for (int i = 0; i < count; i++) {
			(*input_data)->push_back(str);
		}
	}
	// return data
	return input_data;
}
