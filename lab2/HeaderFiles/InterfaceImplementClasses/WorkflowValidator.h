#pragma once
#include "Validator.h"
#include <string>
#include <iostream>
#include <memory>

using namespace std;

namespace WorkflowValidatorException {
	static enum { type_number = 2 };
	static const string Types[type_number] = { "BlockSemantics", "PipeSemantics" };
}

class WorkflowValidator: public Validator{
	class ValidatorException {
	private:
		string type;
		string message;
	public:
		void print_exception();
		ValidatorException(string t, string m);
	};

private:
	void Validator::check_workflow_blocks(const unordered_map<int, Node> *block_map) override;
	void Validator::check_workflow_pipe(const Data *data) override;
public:
	const Data *Validator::check_workflow(const Data *data) override;
	void Delete() override;

	// make factory-method a friend
	friend Validator *Validator::factory_method();
};
