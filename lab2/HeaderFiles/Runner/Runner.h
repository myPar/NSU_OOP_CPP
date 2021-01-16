#pragma once
#include "Parser.h"
#include "Validator.h"
#include "Executor.h"

class Runner {
private:
	Data* check_io_blocks(const Data *data, string i_name, string o_name);
public:
	int run(string workflow_file_name, string input_file_name, string output_file_name);
};

