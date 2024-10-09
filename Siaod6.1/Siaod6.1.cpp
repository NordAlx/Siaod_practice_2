#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>
#include <random>
#include <set>
using namespace std;

struct Element{
    bool open = true, deleted = false;
    string disciplineCode = "", directionCode = "", semesterNumber = "", disciplineName = "";
};

struct HashTable {
    int numberOfElements = 0, capacity = 1;
    Element* elements = new Element[this->capacity];

    

    void insertData(string disciplineCode, string directionCode, string disciplineName, string semesterNumber) {
        this->realloc();
        int index;
        index = getHash(disciplineCode);
        if (!this->elements[index].open) {
            int move = getMove(disciplineCode);
            int temp = index;
            for (int i = 0; i < this->capacity - 1 && !this->elements[temp].open; i++) {
                temp = (index + move + i + 1) % this->capacity;
            }

            this->elements[temp].disciplineCode = disciplineCode;
            this->elements[temp].disciplineName = disciplineName;
            this->elements[temp].directionCode = directionCode;
            this->elements[temp].semesterNumber = semesterNumber;
            this->elements[temp].open = false;
            this->elements[temp].deleted = false;
        }
        else {
            this->elements[index].disciplineCode = disciplineCode;
            this->elements[index].disciplineName = disciplineName;
            this->elements[index].directionCode = directionCode;
            this->elements[index].semesterNumber = semesterNumber;
            this->elements[index].open = false;
            this->elements[index].deleted = false;
        }
        numberOfElements++;
        cout << "Data was added" << endl;
    }

    void realloc() {
        if (numberOfElements / capacity * 100 >= 75) {
            int count = 0;
            Element* elements1 = new Element[this->numberOfElements];

            for (int i = 0; i < capacity; i++) {
                if (!this->elements[i].open) {
                    elements1[count] = this->elements[i];
                    count++;
                }
                this->elements[i].open = true;
                this->elements[i].deleted = false;
            }

            this->capacity *= 2;
            this->elements = new Element[capacity];

            this->numberOfElements = 0;

            for (int i = 0; i < count; i++) {
                this->insertData(elements1[i].disciplineCode, elements1[i].directionCode, elements1[i].disciplineName, elements1[i].semesterNumber);
            }
            delete [] elements1;
        }
    }

    string get(string key) {
        int index = getHash(key), ty = 0;
        int move = getMove(key);
        int temp = index;
        if (this->elements[temp].directionCode == key )
            return 
    }

    void dlt(string key) {
        int index = getHash(key), ty = 0;
        int move = index + getMove(key, ty);

        while (!this->elements[move].open || this->elements[move].deleted) {
            if (this->elements[move].disciplineCode == key) {
                this->elements[move].deleted = true;
                this->elements[move].open = true;
                return;
            }
            ty++;
            move = index + getMove(key, ty);
            if (move > this->capacity)
                return;
        }
    }

    int getHash(string key) {
        int sm = 0;
        for (int i = 0; i < key.length(); i++)
            sm += (key[i] - '0') * (i + 1);
        return sm % this->capacity;
    }

    int getMove(string key) {
        return 1 + stoi(key) % (this->capacity - 1);
    }
};

int main(){
    HashTable table;
    ifstream file("Text.txt");
    int count = 0;
    string disciplineCode = "", directionCode = "", semesterNumber = "", disciplineName = "", line;
    while (getline(file, line)) {
        for (char x : line) {
            if (x == ' ') {
                count++;
                continue;
            }

            switch (count) {
            case 0:
                disciplineCode += x;
                break;
            case 1:
                directionCode += x;
                break;
            case 2:
                disciplineName += x;
                break;
            case 3:
                semesterNumber += x;
                break;
            }
        }
        table.insertData(disciplineCode, directionCode, disciplineName, semesterNumber);
        count = 0;
        disciplineCode = "";
        directionCode = "";
        semesterNumber = "";
        disciplineName = "";
    }
    file.close();


}