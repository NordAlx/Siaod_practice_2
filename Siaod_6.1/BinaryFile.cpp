#include "BinaryFile.h"
using namespace BinaryFuncs;


void BinaryFuncs::deletePart(string name, int n){
    vector <string> vec;
    string line = "";
    char x;
    ifstream file(name, ios_base::binary);
    if (file.is_open()) {
        while (file.read(&x, sizeof(char))) {
            if (x != '\n')
                line += x;
            else {
                vec.push_back(line);
                line = "";
            }
        }
    }
    file.close();

    ofstream file1(name, ios_base::binary);
    size_t len;
    for (int i = 0; i < vec.size(); i++) {
        if (i != n) {
            len = vec[i].size() + 1;
            file1.write((char*)vec[i].c_str(), len);
        }
    }
    file1.close();
}

string BinaryFuncs::findInFile(string name, int n) {
    char x;
    string line = "";
    ifstream file(name, ios_base::binary);
    file.seekg(n);
    while (file.read(&x, sizeof(char)) && x != '\n')
        line += x;
    return line;
}