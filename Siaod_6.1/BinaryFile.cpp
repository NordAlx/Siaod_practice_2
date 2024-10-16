#include "BinaryFile.h"


void Elements::add(string line) {
    Node* node = new Node();
    node->line = line;
    if (this->elements.size() == 0) {
        node->offset = 0;
    }
    else {
        node->offset = this->elements.back()->offset + this->elements.back()->line.length()/1.0 + 1;
    }
    this->elements.push_back(node);
}

void Elements::deleteNode(string name, int n){
    ofstream file(name, ios_base::binary);
    if (!file.is_open())
        return;

    int offset = this->elements[n]->line.size() + 1;
    file.seekp(0, ios_base::beg);
    for (int i = 0; i < this->elements.size(); i++) {
        if (this->elements[i] == NULL)
            continue;
        if (i < n)
            file.write((char*)elements[i]->line.c_str(), elements[i]->line.size() + 1);
        else if (i == n) {
            this->elements[i] = NULL;
        }
        else {
            file.write((char*)elements[i]->line.c_str(), elements[i]->line.size() + 1);
            this->elements[i]->offset -= offset;
        }
    }
    file.flush();
    file.close();
}

string Elements::findInFile(string name, int n) {
    ifstream file(name, ios_base::binary);
    file.seekg(0, ios_base::beg);
    if (!file.is_open())
        return "Open file fail";
    char x;
    string line = "";
    file.seekg(this->elements[n]->offset, ios_base::beg);
    while (file.read(&x, sizeof(char)) && x != '\n')
        line += x;
    file.close();
    return line;
}