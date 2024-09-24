#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

void make_file() {
    ofstream file1("Text.txt");
    if (!file1.is_open())
        return;

    int n, count = 0, number;
    string names[5] = { "МИРЭА", "ВШЭ", "МГУ", "МИФИ", "МГТУ" };
    set<int> st;

    cout << "Input number of lines" << endl;
    cin >> n;

    while (count < n) {
        number = abs(rand()) % 10000;
        if (!st.count(number)) {
            st.insert(number);
            count++;
        }
    }

    for (int x: st)
        file1 << x << " " << names[x % 5] << endl;

    file1.close();
}

int get_part(string line) {
    string num = "";

    for (char x : line)
        if (x == ' ')
            return stoi(num);
        else
            num += x;
}

string get_another_part(string line) {
    string name = "";
    int n = 0;
    while (line[n] != ' ')
        n++;
    n++;
    for (int i = n; i < line.size(); i++)
        name += line[i];
    return name;
}

void find_in_file() {
    int key, mid, l = 0, r;
    ifstream file("Text.bin");
    vector<string> vec;
    string line;
    bool flag = false;

    if (!file.is_open())
        return;

    cout << "Input the key" << endl;
    cin >> key;
    
    while (getline(file, line))
        vec.push_back(line);

    r = vec.size() - 1;

    while (l <= r && !flag) {
        mid = (l + r) / 2;

        if (get_part(vec[mid]) == key)
            flag = true;
        if (get_part(vec[mid]) > key)
            r = mid - 1;
        else
            l = mid + 1;
    }

    if (flag)
        cout << get_another_part(vec[mid]);
    else
        cout << "Not found";

    file.close();
}

int main()
{
    setlocale(LC_ALL, "RUS");
    find_in_file();
}