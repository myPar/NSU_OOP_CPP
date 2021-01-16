#include "Dump.h"

// ReadFile class implementation:
// constructor
Dump::Dump(Node n) : node(n) {}
// main block method
optional<vector<string>> *Dump::execute(optional<vector<string>> *input_data) {
	// check input data exists
	if (!input_data->has_value()) {
		throw BlockException(WorkflowBlockException::Types[5], "input data doesn't exist");
	}
	string file_name = node.get_args()[0];
	ofstream output;
	output.open(file_name);

	// failed to open the file
	if (output.fail()) {
		throw BlockException(WorkflowBlockException::Types[5], "can't open the file for writing");
	}
	// set exception mask (use failbit and badbit)
	output.exceptions(ofstream::failbit | ofstream::badbit);

	try {
		// write data to file
		for (vector<string>::iterator it = (*input_data)->begin(); it != (*input_data)->end(); ++it) {
			output << *it << endl;
		}
	}
	catch (ofstream::failure e) {
		throw BlockException(WorkflowBlockException::Types[5], "can't write data to file");
	}

	// return data
	return input_data;
}
