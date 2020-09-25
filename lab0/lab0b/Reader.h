#pragma once
#include <fstream>
#include <list>
#include <map>
using namespace std;

class Reader
{
	// input stream setter class
	class InputSetter {
	public:
		// returns input file stream
		ifstream *set_input(int argc, char** argv);
	};
	// parsing red line class
	class StringParser {
	public:
		list<string> *parse_string(string str);
	};
	// data handler class
	class DataCollector {
	public:
		// returns map<> of pairs <key, value>, where 
		// key corresponds the count of words in the text and
		// value corresponds the list of words with such count
		map<int, list<string>>* parse_input_data(ifstream* input_file, StringParser str_parser);
		// auxiliary method for map data printing
		void print_map(map<int, list<string>>* map);
	};
public:
	// exception type enum
	enum ExceptionType
	{
		InputSetterException,
		StringParserException,
		DataCollectorException,
	};
	// Reader exception class
	class ReaderException {
	private:
		ExceptionType exception_type;
		string exception_message;
	public:
		// Reader exception constructor
		ReaderException(ExceptionType type, string message);
		// formating exception printing function
		void print_exception();
	};
	// main method of input file data parsing
	map<int, list<string>> *parse_input_data(int argc, char** argv);
};
