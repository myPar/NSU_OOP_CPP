// lab0a.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "module1.h"
#include "module2.h"
#include <iostream>

/*answer:
	1. for each source *.cpp  file builds one object file (for main.cpp; Module1.cpp; Module2.cpp)
	2. NO, after rebuilding all object files become modified
	3. A - output - "John", because we use directive "using" to namespace Module1
	   D - output - "James", because we use directive "using" to namespace Module2
	   (prefious using of the namespace Module1 stoped)
	4. item getMyName() inside two namespaces - Module1 and Module2
	   we can tell compiler from actualy which namespace we should take item getMyName():
	   change line "B" to 'using Module2::getMyName; // (B)'
	5. see below
	6. write above code where you use std namespace items - 'using namespace std';
*/
//

namespace MyNameSpace {
	std::string getMyName() {
		std::string str = "Peter";
		return str;
	}
}
using namespace std;

int main(int argc, char** argv)
{
	std::cout << "Hello world!" << "\n";
	std::cout << Module1::getMyName() << "\n";
	std::cout << Module2::getMyName() << "\n";
	using namespace Module1;
	std::cout << getMyName() << "\n"; // (A)
	std::cout << Module2::getMyName() << "\n";
	using Module2::getMyName; // (B)
	std::cout << getMyName() << "\n"; // COMPILATION ERROR (C)
	//using Module2::getMyName;
	cout << getMyName() << "\n"; // (D)
	cout << MyNameSpace::getMyName() << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
