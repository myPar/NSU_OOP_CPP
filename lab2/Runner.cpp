#include "Runner.h"

void Runner::run(string workflow_file_name) {
	Parser* parser = Parser::factory_method();
	const Data *data = parser->parse_workflow(workflow_file_name);

	Validator* validator = Validator::factory_method();
	const Data *checked_data = validator->check_workflow(data);

	Executor* executor = Executor::factory_method();
	executor->execute(checked_data);

	parser->Delete();
	validator->Delete();
	executor->Delete();
}
