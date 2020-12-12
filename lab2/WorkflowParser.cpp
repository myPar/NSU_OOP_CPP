#include "WorkflowParser.h"
// constructor implementation
WorkflowParser::WorkflowParser() {}

// virtual destructor implementation
Parser::~Parser() {}

// factory method
Parser* Parser::factory_method() {
	return static_cast<Parser*>(new WorkflowParser());
}
// parse_nodes method implementatin
unordered_map<int, Node>* const WorkflowParser::parse_nodes(ifstream* input) {

}
// parse workflow pipeline mehod implementation
list<int>* const WorkflowParser::parse_pipe(ifstream* input) {

}
// main WorkflowParser method
const Data& WorkflowParser::parse_workflow(string input_file_name) {

}
