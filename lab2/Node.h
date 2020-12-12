#pragma once
#include <string>
using namespace std;
// presents workflow block declaration
class Node {
private:
	// block name
	string name;
	// number of arguments
	int arg_number;
	// argument's array
	string* const args;
public:
	// vield geter's mthods
	const string name();
	const int arg_number();
	const string* const args();
	// Constructor
	Node();
	// copy-Constructor
	Node(const Node &node);
	//Destructor
	~Node();
};

