#include "HashTable.h"

void HashTable::insertData(string disciplineCode, string directionCode, string disciplineName, string semesterNumber, int n) {
    this->realloc();
    int index;
    index = getHash(disciplineCode);
    if (!this->elements[index].open) {
        int move = getMove(disciplineCode);
        int temp = index;
        int count = 1;
        while (!this->elements[temp].open) {
            temp = (index + move * count) % this->capacity;
            count++;
        }
        this->elements[temp].disciplineCode = disciplineCode;
        this->elements[temp].disciplineName = disciplineName;
        this->elements[temp].directionCode = directionCode;
        this->elements[temp].semesterNumber = semesterNumber;
        this->elements[temp].open = false;
        this->elements[temp].deleted = false;
        this->elements[temp].n = n;
    }
    else {
        this->elements[index].disciplineCode = disciplineCode;
        this->elements[index].disciplineName = disciplineName;
        this->elements[index].directionCode = directionCode;
        this->elements[index].semesterNumber = semesterNumber;
        this->elements[index].open = false;
        this->elements[index].deleted = false;
        this->elements[index].n = n;
    }
    numberOfElements++;
}

void HashTable::realloc() {
    if (numberOfElements / capacity * 100 >= 75) {
        int count = 0;
        Element* elements1 = new Element[this->numberOfElements];

        for (int i = 0; i < this->capacity; i++) {
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
            this->insertData(elements1[i].disciplineCode, elements1[i].directionCode, elements1[i].disciplineName, elements1[i].semesterNumber, elements1[i].n);
        }
        delete[] elements1;
    }
}

int HashTable::get(string key) {
    int index = getHash(key);
    int move = getMove(key);
    int temp = index;
    int count = 0;
    while (!this->elements[temp].open || this->elements[temp].deleted) {
        if (this->elements[temp].disciplineCode == key && !this->elements[temp].deleted) {
            return temp;
        }
        else if (this->elements[temp].disciplineCode == key && this->elements[temp].deleted)
            break;
        temp = (index + move * count) % this->capacity;
        count++;
    }
    cout << "Not found" << endl;
    return -1;
}

void HashTable::print(string key) {
    int key1 = get(key);
    if (key1 != -1) {
        cout << this->elements[key1].disciplineCode << " ";
        cout << this->elements[key1].directionCode << " ";
        cout << this->elements[key1].disciplineName << " ";
        cout << this->elements[key1].semesterNumber << endl;
    }
}

void HashTable::dlt(string key) {
    int key1 = get(key);
    if (key1 == -1)
        return;
    this->elements[key1].open = true;
    this->elements[key1].deleted = true;
    cout << "Element deleted" << endl;
}

int HashTable::getHash(string key) {
    return stoi(key) % this->capacity;
}

int HashTable::getMove(string key) {
    return stoi(key) / (this->capacity - 1) + 1;
}

void HashTable::interface() {
    string command;
    string key;

    cout << endl;
    cout << "Choose the command" << endl;
    cout << "1)find the key" << endl;
    cout << "2)delete element" << endl;
    cout << "3)print element" << endl;
    cout << "4)end" << endl;

    cin >> command;
    while (command != "4") {
        if (command == "1") {
            cout << "Input the key: ";
            cin >> key;
            if (get(key) != -1)
                cout << "Key: " << get(key) << endl;
        }
        else if (command == "2") {
            cout << "Input the key: ";
            cin >> key;
            dlt(key);
        }
        else if (command == "3") {
            cout << "Input the key: ";
            cin >> key;
            print(key);
        }
        else
            cout << "Not a command" << endl;

        cout << endl;
        cout << "Enter new command: ";
        cin >> command;
    }
}