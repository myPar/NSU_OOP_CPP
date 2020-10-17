#pragma once
#include <map>
#include <list>
#include <string>

using namespace std;
class DataState {
private:
	const int word_count;
	const map<int, list<string>> *word_map;
public:
	const map<int, list<string>>* get_map() const;
	int get_count() const;
	DataState(int count, map<int, list<string>>* data_map);
	~DataState();
};
