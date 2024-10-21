#pragma once

#ifndef BINARY_FILE
#define BINARY_FILE
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Node {
	char* line;
	int offset = 0, size = 0;
};

struct Elements {
	vector <Node*> elements;

	void add(char* line, int offset, int size);
	void deleteNode(string name, int n);
	string findInFile(string name, int n);
};


#endif // BINARY_FILE