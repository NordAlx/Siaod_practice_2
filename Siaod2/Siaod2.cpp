#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <set>
#include <vector>
using namespace std;

struct Table {
    int key;
    string name;
};

void dlt(vector <Table*> vec) {
    while (vec.size() > 0) {
        delete vec[0];
        vec.erase(vec.begin());
    }
}

void make_file(int n) {
    ofstream file1("Text.bin");
    if (!file1.is_open())
        return;

    int count = 0, number;
    string names[9] = { "МИРЭА", "ВШЭ", "МГУ", "МИФИ", "МГТУ", "ПУП", "ПИП", "МИССИС", "ПИС" };
    set<int> st;

    while (count < n) {
        number = abs(rand()) % 1000000;
        if (!st.count(number)) {
            st.insert(number);
            count++;
        }
    }

    for (int x : st)
        file1 << x << " " << names[x % 5] << endl;

    file1.close();
}

int get_part(string line) {
    string num = "";

    for (char x : line) {
        if (x == ' ')
            return stoi(num);

        num += x;
    }
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

string find_in_file(int key) {
    int mid, l = 0, r;
    ifstream file("Text.bin");
    vector<string> vec;
    string line;

    if (!file.is_open())
        return "NF";
    
    while (getline(file, line))
        vec.push_back(line);
    file.close();

    r = vec.size() - 1;

    while (l <= r) {
        mid = (l + r) / 2;

        if (get_part(vec[mid]) == key) 
            return get_another_part(vec[mid]);
        else if (get_part(vec[mid]) > key)
            r = mid - 1;
        else
            l = mid + 1;
    }
    cout << "Not found" << endl;


    return "NF";
}

Table* func1(int key, vector<Table*> unis, int n) {
    int mid, l = 0, r = n - 1;

    while (l <= r) {
        mid = (l + r) / 2;
        if (unis[mid] -> key == key) 
            return unis[mid];
        else if (unis[mid] -> key > key)
            r = mid - 1;
        else
            l = mid + 1;
    }

    return NULL;
}

string func2(Table* unis) {
    if (unis)
        return unis -> name;
    return "Not found";
}

void third_try(int n, int key) {
    vector<Table*> unis;
    string line;

    ifstream file("Text.bin");
    if (!file.is_open())
        return;
    
    while (getline(file, line)) {
        Table *table = new Table();
        table -> key = get_part(line);
        table -> name = get_another_part(line);
        unis.push_back(table);
    }
    file.close();

    cout << func2(func1(key, unis, n)) << endl;

    dlt(unis);
}

int main()
{
    setlocale(LC_ALL, "RUS");

    int n, key;
    string name = "NF";

    
    cout << "Введите размер файла" << endl;
    cin >> n;

    cout << "Введите искомое значение" << endl;
    cin >> key;

    make_file(n);
    
    
    double start_time = clock();
    third_try(n, key);
    double end_time = clock();
    double search_time = end_time - start_time;
    cout << "Программа работала " << search_time/1000 << " секунд" << endl;

    
    if (name != "NF")
        cout << name;
}