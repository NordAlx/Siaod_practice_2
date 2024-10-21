#include "Unity.h"
using namespace Unity;

int main() {
    int k = 0;
    cout << "Choose the task: ";
    cin >> k;
    if (k == 2) {
        HashTable* table = new HashTable;
        ifstream file("Text.txt");
        string line, disciplineCode, directionCode, disciplineName, semesterNumber, ln = "";
        int n = 0, count = 1;

        while (getline(file, line)) {
            for (char x: line) {
                if (x == ' ') {
                    switch (count) {
                    case 1:
                        disciplineCode = ln;
                        cout << ln << " ";
                        break;
                    case 2:
                        directionCode = ln;
                        cout << ln << " ";
                        break;
                    case 3:
                        disciplineName = ln;
                        cout << ln << " ";
                        break;
                    }
                    count++;
                    ln = "";
                }
                else {
                    ln += x;
                }
            }
            semesterNumber = ln;
            cout << ln << endl;
            table->insertData(disciplineCode, directionCode, disciplineName, semesterNumber, n);
            n++;
            ln = "";
            count = 1;
        }
        table->interface();
    }
    else
        startWork();

    
}