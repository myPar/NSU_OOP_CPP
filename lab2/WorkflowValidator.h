#pragma once
#include "Validator.h"

class WorkflowValidator: public Validator{
private:
	virtual void Validator::check_workflow_blocks(const unordered_map<int, Node>& block_map) override;
	virtual void Validator::check_workflow_pipe(const list<int>& pipe) override;
	// closed constructor
	WorkflowValidator();
public:
	virtual const Data& Validator::check_workflow(const Data& data) override;
	virtual Validator::~Validator() override;

	// make factory-method a friend
	friend Validator *Validator::factory_method();
};
