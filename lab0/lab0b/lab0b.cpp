// lab0b.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Reader.h"
#include "Writer.h"

int main(int argc, char** argv)
{
    Reader reader;
    map<int, list<string>>* output_map;
    try {
        output_map = reader.parse_input_data(argc, argv);
    }
    catch (Reader::ReaderException exception) {
        exception.print_exception();
        return 1;
    }

    Writer writer;
    try {
        writer.write_output_data(argv, output_map);
    }
    catch (Writer::WriterException exception) {
        exception.print_exception();
        return 1;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
