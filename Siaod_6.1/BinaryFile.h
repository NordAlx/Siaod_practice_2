#pragma once

#ifndef BINARY_FILE
#define BINARY_FILE
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Node {
	string line;
	double offset = 0;
};

struct Elements {
	vector <Node*> elements;

	void add(string line);
	void deleteNode(string name, int n);
	string findInFile(string name, int n);
};


#endif // BINARY_FILE