#include "Writer.h"
#include <fstream>
#include <iostream>
#include <list>

using namespace std;
void Writer::WriterException::print_exception() {
	cout << "exception of type: " << exception_type << " " << exception_message << endl;
}

ofstream* Writer::OutputSetter::set_output(char** argv) {
	Writer::ExceptionType type = Writer::ExceptionType::OutputSetterException;

	string file_name = string(argv[2]);
	ofstream* output_file = new ofstream(file_name);

	if (!(*output_file)) {
		delete output_file;
		throw WriterException(type, "can't open the output file");
	}
	return output_file;
}

void Writer::DataWriter::write_data(ofstream* output, const DataState *state) {
	const map<int, list<string>>* data_map = state->get_map();
	
	if (data_map->empty()) {
		delete output;
		Writer::ExceptionType type = Writer::ExceptionType::DataWriterException;
		throw WriterException(type, "no data to write");
	}
	int words_count = state->get_count();
	*output << "word,count,frequency" << endl;

	for (map<int, list<string>>::const_iterator it = --data_map->end(); it != --data_map->begin(); --it) {
		int count = it->first;
		double frequency = count / (double)words_count * 100;
		list<string> word_list = it->second;

		for (string word : word_list) {
			*output << word << "," << count << "," << frequency << endl;
		}
	}
}

void Writer::write_output_data(char** argv, const DataState *state) {
	OutputSetter output_setter;
	ofstream* output = output_setter.set_output(argv);
	DataWriter writer;
	writer.write_data(output, state);
	delete output;
}

Writer::WriterException::WriterException(ExceptionType type, string message) {
	exception_type = type;
	exception_message = message;
}
