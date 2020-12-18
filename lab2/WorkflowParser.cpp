#include "WorkflowParser.h"

// Delete-method implementation
void WorkflowParser::Delete() { delete this; }

// factory method
Parser* Parser::factory_method() {
	return static_cast<Parser*>(new WorkflowParser());
}
// parse block line method
pair<int, Node> WorkflowParser::parse_block_line(string str) {
	size_t pos;
	string data[max_arg_number];
	size_t idx = 0;
	
	// split string data by ' '
	while ((pos = str.find(" ")) != string::npos) {
		string token = str.substr(0, pos);
		data[idx++] = token;
		str.erase(0, pos + 1);
	}
	// words number
	size_t data_size = idx;
	// parse block idx:
	int block_idx = 0;
	try {
		block_idx = stoi(data[0], nullptr, 10);
	}
	catch (invalid_argument e){
		throw ParserException(WorkflowParserException::Types[1], "invalide block index");
	}
	// check '=' character
	if (data[1] != "=") {
		throw ParserException(WorkflowParserException::Types[1], "invalide delimeter");
	}
	bool is_correct_name = false;
	string name_str = data[2];
	
	// check block name:
	for (string name : WorkflowSpec::BlockNames) {
		if (name_str == name) {
			is_correct_name = true;
			break;
		}
	}
	if (!is_correct_name) {
		throw ParserException(WorkflowParserException::Types[1], "invalide block name");
	}
	size_t arg_number = data_size - 3;	        // arguments number
	string* args = new string[arg_number];		// args array

	// init args:
	for (size_t i = 3; i < data_size; i++) {
		args[i - 3] = data[i];
	}
	// return constructed pair<int, Node>:
	return pair<int, Node>(block_idx, Node(name_str, arg_number, args));
}

// parse_nodes method implementation
unordered_map<int, Node>* const WorkflowParser::parse_nodes(ifstream* input) {
	unordered_map<int, Node> *workflow_block_map = new unordered_map<int, Node>();
	// set exception mask (use failbit only)
	input->exceptions(ifstream::failbit);

	try {
		string str;
		getline(*input, str);
		// check 'desk' keyword
		if (str != "desk") {
			throw ParserException(WorkflowParserException::Types[1], "incorrect keyword: should be 'desk'");
		}
		bool is_end = false;

		while (!input->eof()) {
			getline(*input, str);
			// check keyword 'csed'
			if (str == "csed") {
				is_end = true;
				break;
			}
			// add parsed pair<idx, Node> to the map
			workflow_block_map->insert(parse_block_line(str));
		}
		if (!is_end) {
			throw ParserException(WorkflowParserException::Types[1], "no keyword 'csed'");
		}
	}
	catch(ifstream::failure e) {
		delete workflow_block_map;
		throw ParserException(WorkflowParserException::Types[0], "read line error");
	}
}
// parse workflow pipeline mehod implementation
list<int>* const WorkflowParser::parse_pipe(ifstream* input) {
	return new list<int>();
}
// main WorkflowParser method
const Data *WorkflowParser::parse_workflow(string input_file_name) {
	ifstream input;
	input.open(input_file_name);
	
	if (input.fail()) {
		throw ParserException(WorkflowParserException::Types[0], "can't open workflow file");
	}

	try {
		parse_nodes(&input);
		parse_pipe(&input);
	}
	catch (ParserException exception) {
		exception.print_exception();
	}
}

// other methods:
	// ParserException constructor
WorkflowParser::ParserException::ParserException(string t, string m): type(t), message(m) {}
	// print exception method
void WorkflowParser::ParserException::print_exception() {
	cerr << "WorkflowParser exception of type: " << type << "; " << message << endl;
}