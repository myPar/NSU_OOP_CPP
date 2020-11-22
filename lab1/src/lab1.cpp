// lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Trit.h"
using namespace std;

int main(int argc, char** argv)
{
	TritSet trit_set = TritSet(10);

	trit_set[2] = True;
	trit_set[2] = False;
	trit_set[5] = False;
	trit_set[0] = False;
	trit_set[20] = True;
	trit_set[24] = False;
	trit_set[10] = True;
	trit_set[15] = True;
	trit_set[17] = False;
	trit_set[17] = True;
	trit_set[16] = False;
	trit_set[13] = False;
	trit_set[11] = False;
	trit_set.print_data();
	trit_set.trim(0);
	trit_set.print_data();
	
	TritSet trit_set1(10);
	trit_set1[2] = True;
	trit_set1[6] = Unknown;
	cout << "Unknown: " << trit_set.cardinality(Unknown) << endl;
	cout << "True: " << trit_set.cardinality(True) << endl;
	cout << "False: " << trit_set.cardinality(False) << endl;
	unordered_map<Trit, size_t> count_map = trit_set.cardinality();
	
	for (unordered_map<Trit, size_t>::iterator it = count_map.begin(); it != count_map.end(); ++it) {
		cout << it->first << ": " << it->second << endl;
	}
	//trit_set1.print_binary_data();

	//TritSet result = trit_set1 | trit_set;
	TritSet result = !trit_set;
	result.print_data();

	cout << "Unknown: " << result.cardinality(Unknown) << endl;
	cout << "True: " << result.cardinality(True) << endl;
	cout << "False: " << result.cardinality(False) << endl;


	return 0;
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
