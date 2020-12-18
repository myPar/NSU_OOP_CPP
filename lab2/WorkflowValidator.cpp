#include "WorkflowValidator.h"
// Delete-method implementation
void WorkflowValidator::Delete() { delete this; }

// factory method implementatation
Validator* Validator::factory_method() {
	return static_cast<Validator*>(new WorkflowValidator());
}

// check workflow blocks on simantic correctness
void WorkflowValidator::check_workflow_blocks(const unordered_map<int, Node> *block_map) {

}
// check workflow pipeline on simantic correctness
void WorkflowValidator::check_workflow_pipe(const list<int> *pipe) {

}
// main method implementation
const Data *WorkflowValidator::check_workflow(const Data *data) {
	return data;
}
