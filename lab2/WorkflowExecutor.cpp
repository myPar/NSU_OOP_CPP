#include "WorkflowExecutor.h"

void WorkflowExecutor::Delete() {delete this;}

// factory-method implementation
Executor* Executor::factory_method() {
	return static_cast<Executor*>(new WorkflowExecutor());
}

// main method
void WorkflowExecutor::execute(const Data *data) {

}
