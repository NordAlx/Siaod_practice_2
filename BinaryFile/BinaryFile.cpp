#include <iostream>
#include <fstream>
#include "BinaryFile.h"
using namespace std;

void BinaryUse::readFile(string name) {

	ifstream file(name, ios_base::binary);
	file.read(link, sizeof(link));
	cout << link;
}


int main() {
	BinaryUse bin;
	bin.readFile("BinaryFile.bin");
}