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
	string* args;
public:
	// vield geter's mthods
	string name();
	int arg_number();
	string* args();
	// Constructor
	Node();
	// copy-Constructor
	Node(const Node &node);
	//Destructor
	~Node();
};

