#include "WorkflowExecutor.h"

// constructor implementation
WorkflowExecutor::WorkflowExecutor() {}

// destructor implementation
Executor::~Executor() {}

// factory-method implementation
Executor* Executor::factory_method() {
	return static_cast<Executor*>(new WorkflowExecutor());
}

// main method
void WorkflowExecutor::execute(const Data& data) {

}
