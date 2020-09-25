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
		throw WriterException(type, "can't open the output file");
	}
	return output_file;
}

void Writer::DataWriter::write_data(ofstream* output, map<int, list<string>>* data_map) {
	if (data_map->empty()) {
		return;
	}
	int words_count = 0;
	*output << "word,count,frequency" << endl;

	for (map<int, list<string>>::iterator it = data_map->begin(); it != data_map->end(); ++it) {
		// calculate summary word count
		int list_size = (it->second).size();
		int word_count = it->first;
		words_count += list_size * word_count;
	}
	for (map<int, list<string>>::iterator it = --data_map->end(); it != --data_map->begin(); --it) {
		int count = it->first;
		double frequency = count / (double)words_count * 100;
		list<string> word_list = it->second;

		for (string word : word_list) {
			*output << word << "," << count << "," << frequency << endl;
		}
	}
}

void Writer::write_output_data(char** argv, map<int, list<string>>* data_map) {
	OutputSetter output_setter;
	ofstream* output = output_setter.set_output(argv);
	DataWriter writer;
	writer.write_data(output, data_map);
}

Writer::WriterException::WriterException(ExceptionType type, string message) {
	exception_type = type;
	exception_message = message;
}
