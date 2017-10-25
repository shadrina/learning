#include <iostream>
#include "TritSet.h"

using namespace std;

void print_set(TritSet& set) {
    for (int i = 0; i < set.get_capacity(); i++)
        cout << set[i] << ", ";
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
        set[i] = FALSE;
    print_set(set);
    set[0] = TRUE;
    set[1] = set[0];
    print_set(set);
    if (set[1] == set[0]) cout << "Ok.";
    return 0;
}