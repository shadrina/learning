#include <iostream>
#include "TritSet.h"

TritSet::TritSet() {
    this->capacity = 0;
    this->data = nullptr;
    this->ptr_last = 0;
}
TritSet::TritSet(TritSet const & set) {
    this->capacity = set.capacity;
    this->data = new unsigned int[this->capacity];
    for (int i = 0; i < this->capacity; i++)
        this->data[i] = set.data[i];
    this->ptr_last = set.ptr_last;
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
    data = nullptr;
}

TritSet::Reference TritSet::operator[](unsigned int x) const {
    x++;
    auto index = x % uint_capacity;
    if (index == 0) index = uint_capacity;
    return Reference(this, x / uint_capacity, index * 2 - 1);
}
//differences between copy constructor and operator=?
//(except deleting previous data)
TritSet & TritSet::operator=(const TritSet & set) {
    //reallocate
    this->capacity = set.capacity;
    delete[] this->data;
    this->data = new unsigned int[set.capacity];
    for (int i = 0; i < this->get_capacity(); i++)
        (*this)[i] = set[i];
    this->ptr_last = set.ptr_last;
    return *this;
}
TritSet TritSet::operator~() const {
    TritSet set = *this;
    for (int i = 0; i < this->get_capacity(); i++)
        set[i] = ~(*this)[i];
    return set;
}
TritSet TritSet::operator&(TritSet set_) const {
    unsigned int capct1 = this->get_capacity();
    unsigned int capct2 = set_.get_capacity();
    TritSet set(capct1 > capct2 ? capct1 : capct2);
    int i = 1;
    while (capct1 != i - 1 && capct2 != i - 1) {
        set[set.get_capacity() - i] = (*this)[capct1 - i] & set_[capct2 - i];
        i++;
    }
    int j = 0;
    while (j < set.get_capacity() - i) {
        Reference r = capct1 > capct2 ? (*this)[j] : set_[j];
        set[i] = r & UNKNOWN;
        i--;
    }
    return set;
}
TritSet TritSet::operator|(TritSet set_) const {
    unsigned int capct1 = this->get_capacity();
    unsigned int capct2 = set_.get_capacity();
    TritSet set(capct1 > capct2 ? capct1 : capct2);
    int i = 1;
    while (capct1 != i - 1 && capct2 != i - 1) {
        set[set.get_capacity() - i] = (*this)[capct1 - i] | set_[capct2 - i];
        i++;
    }
    int j = 0;
    while (j < set.get_capacity() - i) {
        Reference r = capct1 > capct2 ? (*this)[j] : set_[j];
        set[i] = r | UNKNOWN;
        i--;
    }
    return set;
}
std::ostream& operator<<(std::ostream &o, const TritSet &set) {
    unsigned int capacity = set.get_capacity();
    for (int i = 0; i < capacity; i++)
        o << i << " ";
    o << std::endl;
    for (int i = 0; i < capacity; i++)
        o << set[i] << " ";
    return o;
}

void TritSet::reallocate(unsigned int new_capacity) {
    auto *new_data = new unsigned int[new_capacity];
    for (int i = 0; i < this->get_uint_capacity(); i++)
        new_data[i] = this->data[i];
    delete[] this->data;

    this->capacity = new_capacity;
    this->data = new_data;
    unsigned int tail_in_trits = new_capacity % uint_capacity;
    this->ptr_last = tail_in_trits == 0 ? uint_capacity * 2 - 1 : tail_in_trits * 2 - 1;
}

unsigned int * TritSet::get_set() const {
    return data;
}
unsigned int TritSet::get_capacity() const {
    return (capacity - 1) * uint_capacity + ptr_last / 2 + 1;
}
unsigned int TritSet::get_uint_capacity() const {
    return capacity;
}