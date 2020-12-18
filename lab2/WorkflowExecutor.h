#pragma once
#include "Executor.h";

class WorkflowExecutor : public Executor {
public:
	// main method
	void Executor::execute(const Data *data) override;
	void Delete() override;

	// make factory method a friend
	friend Executor *Executor::factory_method();
};

