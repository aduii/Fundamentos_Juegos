#include "Error.h"
#include <iostream>
using namespace std;

void fatalError(std::string errorMsg)
{
	cout << errorMsg << endl;
	cout << "Enter any key to quit " << endl;
	int temp;
	cin >> temp;
	exit(-1);
}
