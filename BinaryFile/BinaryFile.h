#pragma once

#ifndef BINARY_FILE
#define BINARY_FILE
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct BinaryUse
{
	string key;
	char *link;
	
	void readFile(string fileName);

};


#endif // !1
