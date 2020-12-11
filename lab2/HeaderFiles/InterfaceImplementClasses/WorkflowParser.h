#pragma once
#include "Parser.h"

class WorkflowParser : public Parser{
private:
	virtual unordered_map<int, Node>* const Parser::parse_nodes(ifstream* input);
	virtual list<int>* const Parser::parse_pipe(ifstream* input);
public:
	virtual const Data& Parser::parse_workflow(string input_file_name);
};
