#pragma once
#include <cassert>
#include <iostream>
#include <memory>
#include "Executor.h";
#include "Block.h"

class WorkflowExecutor : public Executor {

public:
	// main method
	void Executor::execute(const Data *data) override;

	// make factory method a friend
	friend Executor *Executor::factory_method();
};

