#include <iostream>
#include "TritSet.h"

void TritSet::Reference::set_trit(int bit1, int bit2) {
    set_bit(bit1, index);
    set_bit(bit2, index + 1);
}

void TritSet::Reference::set_bit(int bit, int numb) {
    int mask = 1 << (uint_bit_size - numb);
    if (bit == 0) {
        mask = ~mask;
        *ptr = *ptr & mask;
    }
    else *ptr = *ptr | mask;
}
TritSet::Reference::Reference() = default;
TritSet::Reference::Reference(unsigned int *ptr_, unsigned int index_) : ptr(ptr_), index(index_) {}
TritSet::Reference::~Reference() = default;
TritSet::Reference& TritSet::Reference::operator=(Trit t) {
    switch (t) {
        case FALSE:
            set_trit(false, true);
            break;
        case UNKNOWN:
            set_trit(false, false);
            break;
        case TRUE:
            set_trit(true, false);
            break;
    }
    return *this;
}

TritSet::Reference& TritSet::Reference::operator=(const TritSet::Reference& rvalue) {
    *this = (Trit)rvalue;
    return *this;
}

Trit TritSet::Reference::operator~() const {
    if ((Trit)(*this) == TRUE) return FALSE;
    if ((Trit)(*this) == FALSE) return TRUE;
    return UNKNOWN;
}
TritSet::Reference::operator Trit() const {
    int bit1 = 1 & ((*ptr) >> uint_bit_size - index);
    int bit2 = 1 & ((*ptr) >> uint_bit_size - index + 1);
    if (bit1 == 1) return TRUE;
    if (bit2 == 1) return FALSE;
    return UNKNOWN;
}

TritSet::TritSet() {
    this->capacity = 0;
    this->data = nullptr;
    this->ptr_last = 0;
}
TritSet::TritSet(unsigned int capacity_) {
    this->capacity = capacity_ / uint_capacity;
    unsigned int tail_in_trits = capacity_ % uint_capacity;
    if (tail_in_trits > 0) this->capacity++;
    this->data = new unsigned int[this->capacity];
    this->ptr_last = tail_in_trits == 0 ? uint_capacity * 2 - 1 : tail_in_trits * 2 - 1;
    std::cout << "Created set." << std::endl;
}
TritSet::~TritSet() {
    //???
    //delete data;
    data = nullptr;
}

TritSet::Reference TritSet::operator[](unsigned int x) {
    //проверка на выход за пределы
    //!!!
    x++;
    unsigned int index = x % uint_capacity;
    if (index == 0) index = uint_capacity;
    return Reference(this->data + (x / uint_capacity - 1), index * 2 - 1);
}

unsigned int TritSet::get_capacity() const {
    return (capacity - 1) * uint_capacity + ptr_last / 2 + 1;
}

unsigned int TritSet::get_byte_capacity() const {
    return capacity;
}