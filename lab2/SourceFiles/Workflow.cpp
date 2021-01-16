#include <iostream>
#include "Runner.h"

int main(int argc, char** argv)
{
    string workflow_file_name = "";
    string input_file_name = "";
    string output_file_name = "";

    bool is_correct = false;
    // consisting of key "-i"
    bool is_key1 = false;   
    // consisting of key "-o"
    bool is_key2 = false;

    // parse args:
    if (argc >= 2) {
        workflow_file_name = string(argv[1]);

        if (argc == 2) {
            // only workflow file name case
            is_correct = true;
        }
        else if (argc == 4 || argc == 6) {

            // additional write/read block (file names)
            for (int i = 2; i < argc; i += 2) {
                is_correct = false;
                // get key
                string key = string(argv[i]);
                // get file name
                string arg = string(argv[i + 1]);

                if (key == "-i" && !is_key1) {
                    is_correct = true;
                    is_key1 = true;
                    input_file_name = arg;
                }
                else if (key == "-o" && !is_key2) {
                    is_correct = true;
                    is_key2 = true;
                    output_file_name = arg;
                }
                else {
                    break;
                }
            }
        }
    }
    // check args syntax correctness
    if (!is_correct) {
        cerr << "WorkflowRunner exception:" << endl;
        cerr << "Incorrect args" << endl;
        return 1;
    }
    Runner runner;
    int exit_code = runner.run(workflow_file_name, input_file_name, output_file_name);

    return exit_code;
}
