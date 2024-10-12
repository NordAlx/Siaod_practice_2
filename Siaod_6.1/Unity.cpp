#include "Unity.h"
using namespace Unity;

void Unity::startWork() {
    HashTable table;
    string name, line = "", ln, disciplineCode, directionCode, disciplineName, semesterNumber;
    int n = 1, count = 1;
    char x;
    cout << "Input the file name: ";
    cin >> name;
    ifstream file(name, ios_base::binary);
    if (file.is_open()) {
        while (file.read(&x, sizeof(char))) {
            if (x == ' ' || x == '\n') {
                if (x != '\n') {
                    cout << line << endl;
                    switch (count) {
                    case 1:
                        disciplineCode = line;
                        line = "";
                        break;
                    case 2:
                        directionCode = line;
                        line = "";
                        break;
                    case 3:
                        disciplineName = line;
                        line = "";
                        break;
                    }
                    count++;
                }
                else {
                    cout << line << endl;
                    semesterNumber = line;
                    line = "";
                    count++;
                    count = 1;
                    table.insertData(disciplineCode, directionCode, disciplineName, semesterNumber, n);
                    n++;
                }
            }
            else {
                line += x;
            }
        }
        cout << line << endl;
        semesterNumber = line;
        table.insertData(disciplineCode, directionCode, disciplineName, semesterNumber, n);
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
            Unity::dlt(key, table, name);
        }
        else if (command == "2") {
            cout << "Input the key: ";
            cin >> key;
            Unity::findInFile(key, table, name);
        }
        else
            cout << "Unknown command" << endl;
        cout << endl;
        cout << "Input the command: ";
        cin >> command;
    }
}


void Unity::dlt(string key, HashTable& table, string name) {
    int k = table.get(key);
    if (k != -1) {
        deletePart(name, table.elements[k].n);
        table.dlt(key);
    }
}


void Unity::findInFile(string key, HashTable& table, string name) {
    int k = table.get(key);
    if (k != -1) {
        cout << BinaryFuncs::findInFile(name, table.elements[k].n);
    }
}