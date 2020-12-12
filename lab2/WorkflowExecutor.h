#pragma once
#include "Executor.h";

class WorkflowExecutor : public Executor {
private:
	// closed constructor
	WorkflowExecutor();
public:
	// main method
	virtual void Executor::execute(const Data& data) override;
	// virtual destructor
	virtual Executor::~Executor() override;

	// make factory method a friend
	friend Executor *Executor::factory_method();
};
