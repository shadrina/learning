#include <iostream>
#include "TritSet.h"

using namespace std;

void print_set(TritSet& set) {
    for (int i = 0; i < set.get_capacity(); i++)
        cout << i << ":  " << set[i] << ", ";
    cout << endl;
}

int main() {
    unsigned int N;
    cout << "Enter capacity:" << endl;
    cin >> N;
    TritSet set(N);

    cout << "Capacity in trits: " << set.get_capacity() << endl;
    cout << "Capacity in bytes: " << set.get_byte_capacity() << endl;
    print_set(set);

    for (int i = 0; i < set.get_capacity(); i++)
        set[i] = TRUE;
    print_set(set);

    set[0] = FALSE;
    for (int i = 1; i < set.get_capacity(); i++)
        set[i] = set[i - 1];
    print_set(set);


    Trit test = set[5];
    cout << endl;
    cout << "set[5]: " << test;
    return 0;
}