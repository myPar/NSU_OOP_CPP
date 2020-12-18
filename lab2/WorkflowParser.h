#pragma once
#include "Parser.h"

class WorkflowParser : public Parser{
private:
	unordered_map<int, Node>* const Parser::parse_nodes(ifstream* input) override;
	list<int>* const Parser::parse_pipe(ifstream* input) override;
public:
	// main method
	const Data *Parser::parse_workflow(string input_file_name) override;
	// Interface virtual destructor
	void Delete() override;
	
	// make factory method a friend
	friend Parser* Parser::factory_method();
};
