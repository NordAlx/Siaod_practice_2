#pragma once

#ifndef HASH_TABLE
#define HASH_TABLE
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct Element {
	bool open = true, deleted = false;
	string disciplineCode = "", directionCode = "", semesterNumber = "", disciplineName = "";
    int n;
};

struct HashTable {
    int numberOfElements = 0, capacity = 12;
    Element* elements = new Element[this->capacity];

    void insertData(string disciplineCode, string directionCode, string disciplineName, string semesterNumber, int n);
    void realloc();
    int get(string key);
    void print(string key);
    void dlt(string key);
    int getHash(string key);
    int getMove(string key);
    void interface();
};

#endif // !HASH_TABLE
