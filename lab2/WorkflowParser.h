#pragma once
#include "Parser.h"
#include <string>
#include <iostream>

enum {max_arg_number = 10};

namespace WorkflowParserException {
	static enum {type_number = 3};
	static const string Types[type_number] = {"FileOpen", "BlockSyntax", "PipeSyntax"};
}

class WorkflowParser : public Parser{
	class ParserException {
	private:
		string type;
		string message;
	public:
		void print_exception();
		ParserException(string t, string m);
	};

private:
	pair<int, Node> parse_block_line(string str);
	// parse nodes method
	unordered_map<int, Node>* const Parser::parse_nodes(ifstream* input) override;
	// parse workflow pipeline method
	list<int>* const Parser::parse_pipe(ifstream* input) override;
public:
	// main method
	const Data *Parser::parse_workflow(string input_file_name) override;
	// Interface virtual destructor
	void Delete() override;
	
	// make factory method a friend
	friend Parser* Parser::factory_method();
};
