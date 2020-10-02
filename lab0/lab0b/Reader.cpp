#include "Reader.h" 
#include "Statistics.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;
// formating exception printing function implementation
void Reader::ReaderException::print_exception() {
	cout << "exception of type: " << exception_type << " " << exception_message << endl;
}

ifstream *Reader::InputSetter::set_input(int argc, char** argv) {
	ExceptionType type = InputSetterException;
	
	if (argc != 3) {
		throw ReaderException(type, "incorrect argument number");
	}
	string file_name = string(argv[1]);
	ifstream *input_file = new ifstream(file_name);
	
	if (!(*input_file)) {
		delete input_file;
		throw ReaderException(type, "can't open the input file");
	}
	return input_file;
}

list<string>* Reader::StringParser::parse_string(string str) {
	list<string>* word_list = new list<string>();
	regex rx("[1-9a-zA-Z]");

	int st_word_idx;
	int end_word_idx;

	bool parse_word = false;

	for (string::iterator it = str.begin(); it != str.end(); ++it) {
		if (regex_match(it, it + 1, rx)) {
			// new word case
			if (!parse_word) {
				// mark cur_word by assigning literal " "
				parse_word = true;
				// set start word index value
				st_word_idx = it - str.begin();
				end_word_idx = it - str.begin();
			}
			// old word case
			else {
				// increment word index
				end_word_idx++;
			}
		}
		else if (parse_word) {
			// no matching any more, so cut the word from input string
			parse_word = false;

			string cur_word = str.substr(st_word_idx, end_word_idx - st_word_idx + 1);
			word_list->push_back(cur_word);
		}
	}
	// check word consistence in the end of the string
	if (parse_word) {
		string cur_word = str.substr(st_word_idx, end_word_idx - st_word_idx + 1);
		word_list->push_back(cur_word);
	}
	return word_list;
}

DataState* Reader::DataCollector::parse_input_data(ifstream *input_file, StringParser str_parser) {	
	map<string, int> count_map;
	map<int, list<string>> *output_map = new map<int, list<string>>();
	int word_count = 0;

	while (!input_file->eof()) {
		string str;
		getline(*input_file, str);
		list<string> *word_list = str_parser.parse_string(str);

		for (string item : *word_list) {
			++count_map[item];
		}
		word_count += word_list->size();
		delete word_list;
	}
	for (map<string, int>::iterator it = count_map.begin(); it != count_map.end(); ++it) {
		int word_count = it->second;
		string word = it->first;
		(*output_map)[word_count].push_back(word);
	}
	DataState* state = new DataState(word_count, output_map);
	return state;
}

void Reader::DataCollector::print_map(map<int, list<string>>* output_map) {
	cout << "1'st - count; 2'nd - word list" << endl;
	cout << endl;

	for (map<int, list<string>>::iterator map_it = (*output_map).begin(); map_it != (*output_map).end(); ++map_it) {
		int count = map_it->first;
		cout << count << ": ";

		for (string str : map_it->second) {
			cout << str << "; ";
		}
		cout << endl << endl;
	}
}

DataState *Reader::parse_input_data(int argc, char** argv) {
	// set input
	InputSetter in_setter;
	ifstream* in_file = in_setter.set_input(argc, argv);
	// parsing input data
	StringParser str_parser;
	DataCollector data_collector;
	DataState *state = data_collector.parse_input_data(in_file, str_parser);

	delete in_file;
	// print output map data (for debugging only)
	//data_collector.print_map(output_map);

	return state;
}

// Reader exception constructor implementation
Reader::ReaderException::ReaderException(ExceptionType type, string message) {
	exception_type = type;
	exception_message = message;
}
