#pragma once
#include "Parser.h"

class WorkflowParser : public Parser{
private:
	virtual unordered_map<int, Node>* const Parser::parse_nodes(ifstream* input) override;
	virtual list<int>* const Parser::parse_pipe(ifstream* input) override;
	// closed constructor
	WorkflowParser();
public:
	// main method
	virtual const Data& Parser::parse_workflow(string input_file_name) override;
	// Interface virtual destructor
	virtual Parser::~Parser() override;
	
	// make factory method a friend
	friend Parser* Parser::factory_method();
};
