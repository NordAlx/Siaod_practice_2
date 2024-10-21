#include "BinaryFile.h"


void Elements::add(char* line, int offset, int size) {
    Node* node = new Node();
    node->line = line;
    node->offset = offset;
    node->size = size;
    this->elements.push_back(node);
}

void Elements::deleteNode(string name, int n){
    ofstream file(name, ios_base::binary);
    if (!file.is_open())
        return;

    int size = elements[n]->size;

    for (int i = 0; i < this->elements.size(); i++) {
        if (this->elements[i] == NULL)
            continue;
        if (i < n)
            file.write(elements[i]->line, elements[i]->size);
        else if (i == n) {
            delete this->elements[i];
            this->elements[i] = NULL;
        }
        else {
            file.write(elements[i]->line, elements[i]->size);
            this->elements[i]->offset -= size;
        }
    }
    file.close();
}

string Elements::findInFile(string name, int n) {
    ifstream file(name, ios_base::binary);
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