#include "WorkflowParser.h"
// Delete-method implementation
void WorkflowParser::Delete() { delete this; }

// factory method
Parser* Parser::factory_method() {
	return static_cast<Parser*>(new WorkflowParser());
}
// parse_nodes method implementatin
unordered_map<int, Node>* const WorkflowParser::parse_nodes(ifstream* input) {
	return new unordered_map<int, Node>();
}
// parse workflow pipeline mehod implementation
list<int>* const WorkflowParser::parse_pipe(ifstream* input) {
	return new list<int>();
}
// main WorkflowParser method
const Data *WorkflowParser::parse_workflow(string input_file_name) {
	return new Data(new unordered_map<int, Node>(), new list<int>());
}
