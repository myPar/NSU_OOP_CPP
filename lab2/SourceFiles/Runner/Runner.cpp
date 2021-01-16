#include "Runner.h"

Data* Runner::check_io_blocks(const Data* data, string i_name, string o_name) {
	// get first and last executing blocks	
	int first_idx = data->get_pipe()->front();
	int last_idx = data->get_pipe()->back();

	// init result node map
	unordered_map<int, Node>* result_map = new unordered_map<int, Node>();
	// init result pipe
	list<int>* result_pipe = new list<int>();

	// copy data
	*result_map = *data->get_map();
	*result_pipe = *data->get_pipe();

	// get unique indices:
	int idx1 = 0;
	int idx2 = 0;
	
	// get max key from map
	for (unordered_map<int, Node>::iterator it = result_map->begin(); it != result_map->end(); ++it) {
		int cur_idx = it->first;
		// update indices
		if (idx1 <= cur_idx) {
			idx1 = cur_idx + 1;
			idx2 = idx1 + 1;
		}
	}
	// get block names
	string rf_name = WorkflowSpec::names[0];
	string wf_name = WorkflowSpec::names[1];
	
	// first executed block should be 'readfile' block
	if (result_map->find(first_idx)->second.get_name() != rf_name) {
		if (i_name != "") {
			// make new 'readfile' node:
			string* args = new string[1];	// memory will be clear in Node destructor
			args[0] = i_name;

			Node node(rf_name, 1, args);
			// add node to map
			result_map->insert(pair<int, Node>(idx1, node));
			// add idx to pipe's start
			result_pipe->push_front(idx1);
		}
	}
	// last executed block should be 'writefile' block
	if (result_map->find(last_idx)->second.get_name() != wf_name) {
		if (o_name != "") {
			// make new 'writefile' node:
			string* args = new string[1];	// memory will be clear in Node destructor
			args[0] = o_name;

			Node node(wf_name, 1, args);
			// add node to map
			result_map->insert(pair<int, Node>(idx2, node));
			// add idx to pipe's end
			result_pipe->push_back(idx2);
		}
	}
	return new Data(result_map, result_pipe);
}

int Runner::run(string workflow_file_name, string input_file_name, string output_file_name) {
	try {
		Parser* parser = Parser::factory_method();
		unique_ptr<Parser> parser_ptr(parser);

		const Data* data = parser->parse_workflow(workflow_file_name);
		unique_ptr<const Data> data_ptr(data);

		Validator* validator = Validator::factory_method();
		unique_ptr<Validator> validator_ptr(validator);

		// the same as data
		const Data* checked_data = validator->check_workflow(data);

		Executor* executor = Executor::factory_method();
		unique_ptr<Executor> executor_ptr(executor);

		// refactoring data add readfile or writefile block (if there are -i or -o optinons in cmd line args)
		const Data* refactored_data = check_io_blocks(checked_data, input_file_name, output_file_name);
		unique_ptr<const Data> refactored_data_ptr(refactored_data);

		executor->execute(refactored_data);
	}
	catch (int exit_code) {
		return exit_code;
	}
	return 0;
}
