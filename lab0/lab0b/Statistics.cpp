#include "Statistics.h"
const map<int, list<string>> *DataState::get_map() const {return word_map;}

int DataState::get_count() const {return word_count;}

DataState::DataState(int count, map<int, list<string>> *data_map) : word_count(count), word_map(data_map) {}

DataState::~DataState() {
	delete word_map;
}