#pragma once
#include "Data.h"
// Workflow executor Interface

class Executor {
public:
	// virtual destructor
	virtual ~Executor() {}
	// workflow pipeline executing method
	virtual void execute(const Data *data) = 0;
	// function-factory for implement class object creating
	static Executor *factory_method();
};

