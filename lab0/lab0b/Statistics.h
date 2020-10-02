#pragma once
#include <map>
#include <list>
#include <string>

using namespace std;
class DataState {
private:
	int word_count;
	map<int, list<string>>* word_map;
public:
	map<int, list<string>>* get_map();
	int get_count();
	DataState(int count, map<int, list<string>>* data_map);
	~DataState();
};
