#include <iostream>
#include <string>
#include <vector>
using namespace std;

void task1() {
    string sentence, word;
    vector <string> words;
    cout << "Enter the sentence" << endl;
    getline(cin, sentence);
    
    for (char x : sentence) {
        if (x == ' ' || x == ',') {
            if (!word.empty())
                words.push_back(word);

            if (x == ',')
                words.push_back(",");

            word = "";
        }
        else
            word += x;
    }
    if (!word.empty()) {
        word.pop_back();
        words.push_back(word);
    }

    for (int i = 0; i < words.size(); i++) {
        if (i == 0 && words[i + 1] == ",")
            cout << words[i] << ", ";
        else if (i == words.size() - 1 && words[i - 1] == ",")
            cout << words[i] << ", ";

        if (i > 0 && i < words.size() - 1) 
            if (words[i - 1] == "," && words[i + 1] == ",") 
                cout << words[i] << ", ";
            
        
    }
}

vector<int> prefFunc(string line) {
    vector<int> p;

    for (int i = 0; i < line.length(); i++)
        p.push_back(0);

    int j = 0, i = 1;
    while (i != line.length()) {
        if (line[j] == line[i]) {
            p[i] = j + 1;
            i++;
            j++;
        }
        else if (j == 0) {
            p[i] = 0;
            i++;
        }
        else
            j = p[j - 1];
    }
    return p;
}

int find(string line, string obraz, vector<int> p) {
    int k = 0, l = 0;
    while (k != line.length()) {
        if (line[k] == obraz[l]) {
            k++;
            l++;
            if (l == obraz.size())
                return l;
        }
        else if (l != 0) {
            l = p[l - 1];
        }
        else {
            k++;
        }
    }
    return 0;
}

void task2() {
    string line1, line2;
    cout << "Enter the lines" << endl;
    getline(cin, line1);
    getline(cin, line2);
    line2.pop_back();
    cout << "Maximum pref: " << find(line1, line2, prefFunc(line2));
}


int main()
{
    setlocale(LC_ALL, "Russian");
    

    //task1();

    task2();
}