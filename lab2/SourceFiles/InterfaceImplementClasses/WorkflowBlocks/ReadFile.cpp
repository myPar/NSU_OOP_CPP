#include "ReadFile.h"

// ReadFile class implementation:
	// constructor
ReadFile::ReadFile(Node n) : node(n){}
	// main block method
optional<vector<string>> *ReadFile::execute(optional<vector<string>> *input_data) {
	// check input data existing
	if (input_data->has_value()) {
		throw BlockException(WorkflowBlockException::Types[0], "input data exists");
	}
	string file_name = node.get_args()[0];
	ifstream input;
	input.open(file_name);
	
	// failed to open the file
	if (input.fail()) {
		throw BlockException(WorkflowBlockException::Types[0], "can't open te file for reading");
	}
	// set exception mask (use failbit only)
	input.exceptions(ifstream::failbit);
	
	try {
		// add empty vector container
		(*input_data).emplace();
		
		// read all file data
		while (!input.eof())
		{
			string str = "";
			// read next line from the file
			getline(input, str);
			// add line to the data
			(*input_data)->push_back(str);
		}
	}
	catch (ifstream::failure e) {
		throw BlockException(WorkflowBlockException::Types[0], "can't read the data from file");
	}
	// return readed data
	return input_data;
}
