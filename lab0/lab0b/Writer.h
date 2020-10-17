#pragma once
#include <fstream>
#include <map>
#include <list>
#include "Statistics.h"

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
		void write_data(ofstream *output, const DataState* state);
	};
public:
	void write_output_data(char** argv, const DataState *state);

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
