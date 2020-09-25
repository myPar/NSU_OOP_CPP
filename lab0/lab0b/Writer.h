#pragma once
#include <fstream>
#include <map>
#include <list>

using namespace std;
//
class Writer
{
	//
	class OutputSetter {
	public:
		ofstream *set_output(char **argv);
	};
	//
	class DataWriter {
	public:
		void write_data(ofstream *output, map<int, list<string>>* data_map);
	};
public:
	void write_output_data(char** argv, map<int, list<string>>* data_map);

	enum ExceptionType
	{
		OutputSetterException,
		DataWriterException,
	};
	// Reader exception class
	class WriterException {
	private:
		ExceptionType exception_type;
		string exception_message;
	public:
		// Reader exception constructor
		WriterException(ExceptionType type, string message);
		// formating exception printing function
		void print_exception();
	};

};
