#include <iostream>
#include "TritSet.h"

using namespace std;

int main() {
    TritSet set(2);
    TritSet set_(2);
    set_[0] = FALSE;
    set_[1] = ~set_[0];
    cout << "init :" << endl << set_ << endl;
    set = ~set_;
    cout << "~set_ :" << endl << set << endl;
    set = set & set_;
    cout << "set & set_ :" << endl << set << endl;

    return 0;
}