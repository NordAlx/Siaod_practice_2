﻿#include <iostream> 
#include <bitset> 
#include <fstream> 
#include <string> 
#include <set> 
#include <random> 
#include <ctime> 
#include <vector> 
#include <chrono>


using namespace std;

int main()
{
    ///Номер 1, задание 1 
    /*
    int n = 0x4256;
    cout << "Variable in 2-digit number system" << endl;
    cout << bitset <16>(n) << endl;
    int mask = 0b0101010101010101;
    cout << "Mask in 2-digit number system" << endl;
    cout << bitset<16>(mask) << endl;
    cout << "Result" << endl;
    cout << bitset<16>(n | mask);
    */

    //Номер 2, задание 1 
    /*
    int n;
    cout << "Enter variable value" << endl;
    cin >> n;
    cout << "Variable in 2-digit number system" << endl;
    cout << bitset <16>(n) << endl;
    int mask = 0b1000011111111111;
    cout << "Mask in 2-digit number system" << endl;
    cout << bitset<16>(mask) << endl;
    cout << "Result" << endl;
    cout << bitset<16>(n & mask);
    */

    //Номер 3, задание 1 
    /*
    int n;
    cout << "Enter variable value" << endl;
    cin >> n;
    cout << "Result" << endl;
    cout << bitset <16>(n) << " * " << 16 << " = " << bitset<16>(n << 4);
    cout << " (" << n * 16 << ")";
    */

    //Номер 4, задание 1 
    /*
    int n;
    cout << "Enter variable value" << endl;
    cin >> n;
    cout << "Result" << endl;
    cout << bitset <16>(n) << " / " << 32 << " = " << bitset<16>(n >> 5);
    cout << " (" << n / 32 << ")";
    */

    //Номер 5, задание 1 
    /*
    int x, n;
    cout << "Enter variable value" << endl;
    cin >> x;
    int mask = 0b1000000000000000;
    cout << "Enter the number of digit to turn 1" << endl;
    cin >> n;
    mask = mask >> (15 - n);
    cout << bitset <16>(x) << endl;
    cout << bitset<16>(mask) << endl;
    cout << bitset<16>(x | mask);
    */




    //Задание 2 
    /*
    unsigned char baits = 0;
    int number, n;
    cout << "Enter the number of values" << endl;
    cin >> n;
    cout << "Enter the values" << endl;
    for (int i = 0; i < n; i++) {
        cin >> number;
        baits = baits | (0b10000000 >> number);
    }
    cout << "Result" << endl;
    for (int i = 0; i < 8; i++) {
        if (baits & (0b10000000 >> i))
            cout << i << " ";
    }
    */


    /*
    unsigned char baits[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int number, n;
    cout << "Enter the number of values" << endl;
    cin >> n;
    cout << "Enter the values" << endl;
    for (int i = 0; i < n; i++) {
        cin >> number;
        baits[number / 8] = baits[number / 8] | (0b10000000 >> (number % 8));
    }
    cout << "Result" << endl;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (baits[i] & (0b10000000 >> j))
                cout << i * 8 + j << " ";
        }
    }
    */




    //Задание 3 
    
    unsigned int start_time = clock();

    ifstream f1;
    ofstream f2;
    const int MAX_NUM = 10000000;
    int number;
    vector <unsigned char> baits(MAX_NUM / 8);

    f1.open("Fuf.txt");
    f2.open("Shish.txt");
    if (!(f1.is_open() && f2.is_open())) {
        return 1;
    }

    while (f1 >> number) {
        baits[number / 8] |= (0b10000000 >> (number % 8));
    }

    for (int i = 0; i < (MAX_NUM / 8); i++) {
        for (int j = 0; j < 8; j++) {
            if (baits[i] & (0b10000000 >> j))
                f2 << i * 8 + j << endl;
        }
    }

    f1.close();
    f2.close();

    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    cout << "Time programm requaired " << search_time/1000 << " seconds" << endl;
    


    return 0;
}