#pragma once
#include "Validator.h"

class WorkflowValidator: public Validator{
private:
	void Validator::check_workflow_blocks(const unordered_map<int, Node> *block_map) override;
	void Validator::check_workflow_pipe(const list<int> *pipe) override;
public:
	const Data *Validator::check_workflow(const Data *data) override;
	void Delete() override;

	// make factory-method a friend
	friend Validator *Validator::factory_method();
};
