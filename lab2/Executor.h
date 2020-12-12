#pragma once
#include "Data.h"
// Workflow executor Interface

class Executor {
public:
	// workflow pipeline executing method
	virtual void execute(const Data& data) = 0;
	// function-factory for implement class object creating
	static Executor *factory_method();
	// virtual destructor
	virtual ~Executor() = 0;
};

