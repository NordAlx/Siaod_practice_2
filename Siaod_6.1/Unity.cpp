#include "Unity.h"
using namespace Unity;

void Unity::startWork() {
    HashTable *table = new HashTable;
    Elements *fileElements = new Elements;
    string name, disciplineCode, directionCode, disciplineName, semesterNumber, line = "";
    char x, *ln;
    int count = 1, n = 0, point = 0, offset = 0;
    cout << "Input the file name: ";
    cin >> name;
    ifstream file(name, ios_base::binary);
    if (!file.is_open()) {
        cout << "Couldn't open the file" << endl;
        return;
    }
    
    while (file.read((char*)&x, sizeof(char))) {
        if (x == '\n') {
            semesterNumber = line;
            table->insertData(disciplineCode, directionCode, disciplineName, semesterNumber, n);
            n++;
            line = "";
            count = 1;
        }
        else if (x == ' ') {
            switch (count) {
            case 1:
                disciplineCode = line;
                break;
            case 2:
                directionCode = line;
                break;
            case 3:
                disciplineName = line;
                break;
            }
            count++;
            line = "";
        }
        else {
            line += x;
        }

        cout << x;
        if (x == '\n') {
            point = file.tellg();
            file.seekg(offset);
            ln = new char[point - offset];
            file.read(ln, point - offset);
            fileElements->add(ln, offset, point - offset);
            offset = point;
        }
    }

    file.close();
    
    string command;
    string key;

    cout << endl;
    cout << "Choose the command" << endl;
    cout << "1)delete element" << endl;
    cout << "2)Find in file" << endl;
    cout << "3)end" << endl;
    cout << "Input the command: ";
    cin >> command;
    while (command != "3") {
        if (command == "1") {
            cout << "Input the key: ";
            cin >> key;
            Unity::dlt(key, table, fileElements, name);
        }
        else if (command == "2") {
            cout << "Input the key: ";
            cin >> key;
            Unity::findInFile(key, table, fileElements, name);
        }
        else
            cout << "Unknown command" << endl;
        cout << endl;
        cout << "Input the command: ";
        cin >> command;
    }
    
}


void Unity::dlt(string key, HashTable* table, Elements* fileElements, string name) {
    int k = table->get(key);
    if (k != -1) {
        fileElements->deleteNode(name, table->elements[k].n);
        table->dlt(key);
    }
}


void Unity::findInFile(string key, HashTable* table, Elements* fileElements, string name) {
    int k = table->get(key);
    if (k != -1) {
        cout << fileElements->findInFile(name, table->elements[k].n);
    }
}