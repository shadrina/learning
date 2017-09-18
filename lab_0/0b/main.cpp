#include <iostream>
#include <fstream>
#include <list>
#include "module1.h"

using namespace std;

int main(int argc, char** argv) {

    if (argc < 2) {
        cout << "no parameters";
        return 0;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    if (!fin.is_open() || !fout.is_open()) {
        cout << "can't open files";
        return 0;
    }

    list<string> stringsList;
    string s;
    while (!fin.eof()) {
        getline(fin, s);
        stringsList.push_back(s);
    }

    Module1::sort_strings(stringsList);

    while (!stringsList.empty()) {
        fout << stringsList.front() << "\n";
        stringsList.pop_front();
    }

    fin.close();
    fout.close();
    return 0;
}