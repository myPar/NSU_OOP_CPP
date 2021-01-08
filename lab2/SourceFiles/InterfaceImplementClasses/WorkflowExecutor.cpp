#include "WorkflowExecutor.h"

void WorkflowExecutor::Delete() {delete this;}

// factory-method implementation
Executor* Executor::factory_method() {
	return static_cast<Executor*>(new WorkflowExecutor());
}

// main method
void WorkflowExecutor::execute(const Data *data) {
	// empty text data
	optional<vector<string>> text_data;
	optional<vector<string>> *text_data_ptr = &text_data;
	// get index pipeline
	const list<int> *pipe = data->get_pipe();
	// get Node map
	const unordered_map<int, Node>* map = data->get_map();

	// iterate over each index
	for (list<int>::const_iterator it = pipe->begin(); it != pipe->end(); ++it) {
		unordered_map<int, Node>::const_iterator node_it = map->find(*it);
		// no such index in block map assertion
		assert(node_it != map->end() && "invalide index");
		Node node = node_it->second;

		// create block
		Block* cur_block = Block::factory_method(node);
		// try to execute block
		try {
			text_data_ptr = cur_block->execute(text_data_ptr);
		}
		catch (BlockException e) {
			cerr << "WorkflowExecutor exception:" << endl;
			e.print_exception();
			cur_block->Delete();
			delete data;
			exit(1);
		}
		// delete block
		cur_block->Delete();
	}
	// check that text data is empty after workflow execution 
	// (last workflow block shoult be 'writefile')
	if (text_data.has_value()) {
		cerr << "WorkflowExecutor exception:" << endl;
		cerr << "last executed workflow block should be a 'writefile' block" << endl;
		delete data;
		exit(1);
	}
}

// other methods
	// WorkflowExecutor exception constructor
BlockException::BlockException(string t, string m) : type(t), message(m) {}

	// print exception method
void BlockException::print_exception() {
	cerr << "Execution of block \"" << type << "\" failed; " << message << endl;
}
