#include <iostream>
#include "TritSet.h"

TritSet::Reference::Reference() {};
TritSet::Reference::Reference(TritSet *set_, unsigned int byte_shift_, unsigned int bit_shift_)
        : set(set_), ptr(set->get_set() + byte_shift_), bit_shift(bit_shift_) {}
TritSet::Reference::~Reference() {};
TritSet::Reference& TritSet::Reference::operator=(Trit t) {
    int shift = uint_bit_size - bit_shift - 1;
    unsigned int mask = ~(0b11 << shift);
    *ptr = *ptr & mask;
    switch (t) {
        case FALSE:
            mask = 0b1 << shift;
            break;
        case UNKNOWN:
            mask = 0;
            break;
        case TRUE:
            mask = 0b10 << shift;
            break;
    }
    *ptr = *ptr | mask;
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
    int bits = 0b11 & (*ptr >> uint_bit_size - bit_shift - 1);
    if (bits == 0b10) return TRUE;
    if (bits == 0b1) return FALSE;
    return UNKNOWN;
}

TritSet::TritSet() {
    this->capacity = 0;
    this->data = 0;
    this->ptr_last = 0;
}
TritSet::TritSet(unsigned int capacity_) {
    this->capacity = capacity_ / uint_capacity;
    unsigned int tail_in_trits = capacity_ % uint_capacity;
    if (tail_in_trits > 0) this->capacity++;
    this->data = new unsigned int[this->capacity];
    this->ptr_last = tail_in_trits == 0 ? uint_capacity * 2 - 1 : tail_in_trits * 2 - 1;
}
TritSet::~TritSet() {
    delete[] data;
    data = 0;
}

TritSet::Reference TritSet::operator[](unsigned int x) {
    //check
    x++;
    unsigned int index = x % uint_capacity;
    if (index == 0) index = uint_capacity;
    return Reference(this, x / uint_capacity, index * 2 - 1);
}

unsigned int * TritSet::get_set() const {
    return data;
}

unsigned int TritSet::get_capacity() const {
    return (capacity - 1) * uint_capacity + ptr_last / 2 + 1;
}

unsigned int TritSet::get_byte_capacity() const {
    return capacity;
}