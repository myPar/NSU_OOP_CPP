#pragma once
#include "Validator.h"

class WorkflowValidator: public Validator{
private:
	virtual void Validator::check_workflow_blocks(const unordered_map<int, Node>& block_map);
	virtual void Validator::check_workflow_pipe(const list<int>& pipe);
public:
	virtual const Data& Validator::check_workflow(const Data& data);
};
