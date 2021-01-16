#include "WorkflowParser.h"

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
	// add last token to data
	data[idx++] = str;
	// words number
	size_t data_size = idx;
	// parse block idx:
	int block_idx = 0;
	try {
		block_idx = stoi(data[0], nullptr, 10);
	}
	catch (invalid_argument e) {
		throw ParserException(WorkflowParserException::Types[1], "invalide block index");
	}
	// check '=' character
	if (data[1] != "=") {
		throw ParserException(WorkflowParserException::Types[1], "invalide delimeter");
	}
	string name_str = data[2];
	
	// check block name:
	if (!WorkflowSpec::is_correct_name(name_str)) {
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
		if (str != "desc") {
			delete workflow_block_map;
			throw ParserException(WorkflowParserException::Types[1], "incorrect keyword: should be 'desk'");
		}
		bool is_end = false;
		// read workflow blocks
		while (!input->eof()) {
			getline(*input, str);
			// check keyword 'csed'
			if (str == "csed") {
				is_end = true;
				break;
			}
			// parse next line
			pair<int, Node> block = parse_block_line(str);
			int idx = block.first;
			// check index uniqueness
			if (workflow_block_map->find(idx) != workflow_block_map->end()) {
				delete workflow_block_map;
				throw ParserException(WorkflowParserException::Types[1], "block index collision: all blocks should have unique index");
			}
			// add parsed pair<idx, Node> to the map
			workflow_block_map->insert(block);
		}
		if (!is_end) {
			delete workflow_block_map;
			throw ParserException(WorkflowParserException::Types[1], "no keyword 'csed'");
		}
	}
	catch(ifstream::failure e) {
		delete workflow_block_map;
		throw ParserException(WorkflowParserException::Types[0], "read line error");
	}
	// return built map
	return workflow_block_map;
}
// parse workflow pipeline mehod implementation
list<int>* const WorkflowParser::parse_pipe(ifstream* input) {
	list<int>* pipe = new list<int>();
	string pipe_line;
	// set exception mask (use failbit only)
	input->exceptions(ifstream::failbit);

	try {
		getline(*input, pipe_line);
		if (!input->eof()) {
			delete pipe;
			throw ParserException(WorkflowParserException::Types[0], "workflow file has garbage at the end");
		}
		size_t pos;

		// allocate memory for pipe and
		// set unique_ptr to pipe data
		list<string> *pipe_tokents = new list<string>();
		unique_ptr<list<string>> data_ptr(pipe_tokents);

		// split string data by ' '
		while ((pos = pipe_line.find(" ")) != string::npos) {
			string token = pipe_line.substr(0, pos);
			pipe_tokents->push_back(token);
			pipe_line.erase(0, pos + 1);
		}
		// add last token to the data
		pipe_tokents->push_back(pipe_line);

		int state = -1;
		// check pipe on syntax correctness
		for (std::list<string>::iterator it = pipe_tokents->begin(); it != pipe_tokents->end(); ++it) {
			// get token
			string token = *it;
			//change state
			state = (state + 1) % 2;
			int idx = 0;
			// check index
			if (state == 0) {
				try {
					idx = stoi(token, nullptr, 10);
				}
				catch (invalid_argument e) {
					delete pipe;
					throw ParserException(WorkflowParserException::Types[2], "invalide block index in pipe");
				}
				// add index to the list
				pipe->push_back(idx);
			}
			// check '->' delimeter
			else {
				if (token != "->") {
					delete pipe;
					throw ParserException(WorkflowParserException::Types[2], "invalide delimeter in pipe");
				}
			}
		}
		// check that the last token is an index
		if (state != 0) {
			delete pipe;
			throw ParserException(WorkflowParserException::Types[2], "the last token should be an index");
		}
	}
	catch (ifstream::failure e) {
		delete pipe;
		throw ParserException(WorkflowParserException::Types[0], "read line error");
	}
	// return block indices pipe
	return pipe;
}
// main WorkflowParser method
const Data *WorkflowParser::parse_workflow(string input_file_name) {
	unordered_map<int, Node>* workflow_block_map = nullptr;
	list<int>* pipe = nullptr;
	//unique_ptr<unordered_map<int, Node>> map_ptr(workflow_block_map);
	//unique_ptr
	try {
		ifstream input;
		input.open(input_file_name);

		if (input.fail()) {
			throw ParserException(WorkflowParserException::Types[0], "can't open workflow file");
		}
		// init block map
		workflow_block_map = parse_nodes(&input);
		// init block pipe 
		pipe = parse_pipe(&input);
	}
	catch (ParserException exception) {
		// in case of exception both pointers are either nullptr or points on data
		// so delete method will not throw an error
		delete workflow_block_map;
		delete pipe;
		exception.print_exception();
		// throw exit code
		throw -1;
	}
	// return workflow Data
	return new Data(workflow_block_map, pipe);
}

// other methods:
	// ParserException constructor
WorkflowParser::ParserException::ParserException(string t, string m): type(t), message(m) {}
	// print exception method
void WorkflowParser::ParserException::print_exception() {
	cerr << "WorkflowParser exception of type: " << type << "; " << message << endl;
}
