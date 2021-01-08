#include "WorkflowValidator.h"
// Delete-method implementation
void WorkflowValidator::Delete() { delete this; }

// factory method implementatation
Validator* Validator::factory_method() {
	return static_cast<Validator*>(new WorkflowValidator());
}

// check workflow blocks on simantic correctness
void WorkflowValidator::check_workflow_blocks(const unordered_map<int, Node> *block_map) {
	//for all blocks check the number of arguments
	for (unordered_map<int, Node>::const_iterator it = block_map->begin(); it != block_map->end(); ++it) {
		Node node = it->second;

		if (WorkflowSpec::get_arg_number(node.get_name()) != node.get_arg_number()) {
			throw ValidatorException(WorkflowValidatorException::Types[0], "incorrect number of arguments");
		}
	}
}
// check workflow pipeline on simantic correctness
void WorkflowValidator::check_workflow_pipe(const Data *data) {
	// get map and pipe pointers
	const list<int> *pipe = data->get_pipe();
	const unordered_map<int, Node>* block_map = data->get_map();
	
	// check each index on existence in block_map
	for (list<int>::const_iterator it = pipe->begin(); it != pipe->end(); ++it) {
		if (block_map->find(*it) == block_map->end()) {
			throw ValidatorException(WorkflowValidatorException::Types[1], "no block with such index");
		}
	}
}
// main method implementation
const Data *WorkflowValidator::check_workflow(const Data *data) {
	try {
		check_workflow_blocks(data->get_map());
		check_workflow_pipe(data);
	}
	catch (ValidatorException e) {
		e.print_exception();
		delete data;
		exit(1);
	}
	return data;
}

// other methods:
	// ValidatorException constructor
WorkflowValidator::ValidatorException::ValidatorException(string t, string m) : type(t), message(m) {}

// print exception method
void WorkflowValidator::ValidatorException::print_exception() {
	cerr << "WorkflowValidator exception of type: " << type << "; " << message << endl;
}
