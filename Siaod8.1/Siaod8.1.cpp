#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

using namespace std;

struct simbol {
    char x;
    double p;
    string code = "";
};

void ShannonFano(vector<simbol*>& simbols, int right, int left = 0) {
    if (left >= right - 1)
        return;
    else if (right - left == 2) {
        simbols[left]->code += "0";
        simbols[right - 1]->code += "1";
        return;
    }
    
    double sum = 0;
    double stop = 0;
    int split = left;

    for (int i = left; i < right; i++) {
        stop += simbols[i]->p;
    }

    stop /= 2;

    for (int i = left; i < right; i++) {
        sum += simbols[i]->p;

        if (sum <= stop) {
            simbols[i]->code += "0";
            split++;
        }
        else
            simbols[i]->code += "1";
    }

    ShannonFano(simbols, split, left);
    ShannonFano(simbols, right, split);
}

void compress(string text, map<char, string> codeTable) {
    ofstream file("ZippedFile.txt");
    for (char x : text) {
        file << codeTable[x];
    }
}

void decompress(string fileName, map<char, string> codeTable) {
    map<string, char> reverseCodeTable;
    for (const auto& entry : codeTable) {
        reverseCodeTable[entry.second] = entry.first;
    }

    ifstream file(fileName);
    if (!file.is_open()) {
        return;
    }

    string encodedText;
    getline(file, encodedText);
    file.close();

    string decodedText;
    string currentCode;
    for (char bit : encodedText) {
        currentCode += bit;
        if (reverseCodeTable.count(currentCode)) {
            decodedText += reverseCodeTable[currentCode]; 
            currentCode.clear();
        }
    }

    ofstream outputFile("UnzippedFile.txt");
    if (!outputFile.is_open()) {
        return;
    }
    outputFile << decodedText;
    outputFile.close();
}

void getK(string text, map <char, string> codeTable) {
    double sum = text.size()*8, newSum = 0;
    for (auto x : text) {
        newSum += codeTable[x].size();
    }
    cout << "K = " << round((1 - newSum / sum) * 100) << "%";
}

void part1() {
    ifstream file("TextForZip.txt");
    string line, whole = "";
    map <char, string> codeTable;
    vector <pair<char, double>> simbols;
    vector <simbol*> s;
    int sum = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            whole += (line + " ");
            for (char x : line) {
                auto it = find_if(simbols.begin(), simbols.end(), [&](const pair<char, double>& p) {
                    return p.first == x;
                    });

                if (it != simbols.end()) {
                    it->second++;
                }
                else {
                    simbols.push_back({ x, 1 });
                }
                sum++;
            }
        }

        for (auto& p : simbols) {
            p.second /= sum;
        }

        sort(simbols.begin(), simbols.end(), [](auto el1, auto el2) {return el1.second > el2.second;});
        
        for (auto element : simbols) {
            simbol* simb = new simbol;
            simb->x = element.first;
            simb->p = element.second;
            s.push_back(simb);
        }
     
        ShannonFano(s, s.size());

        for (const auto& simb : s) {
            codeTable[simb->x] = simb->code;
        }

        for (auto simb : s) {
            delete simb;
        }

        compress(whole, codeTable);
        decompress("ZippedFile.txt", codeTable);

        getK(whole, codeTable);
    }
    file.close();
}

int main() 
{
    setlocale(LC_ALL, "Russiаn");
    part1();
    return 0;
}