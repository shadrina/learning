#include <iostream>
#include "TritSet.h"

TritSet::Reference::Reference(TritSet const *set_, unsigned int byte_shift_, unsigned int bit_shift_)
        : set(set_), ptr(set->get_set() + byte_shift_), bit_shift(bit_shift_) {}

TritSet::Reference & TritSet::Reference::operator=(Trit t) {
    // By the shift of the pointer, we determine the index
    // by which we are trying to address.
    if (set->get_capacity() <= (ptr - set->data) * uint_capacity + bit_shift / 2 + 1) return *this;
    int shift = uint_bit_size - bit_shift - 1;
    int mask = ~(0b11 << shift);
    *ptr = *ptr & mask;
    switch (t) {
        case FALSE:
            mask = FALSE_bits << shift;
            break;
        case UNKNOWN:
            mask = 0;
            break;
        case TRUE:
            mask = TRUE_bits << shift;
            break;
    }
    *ptr = *ptr | mask;
    return *this;
}

TritSet::Reference & TritSet::Reference::operator=(TritSet::Reference const & rvalue) {
    *this = (Trit)rvalue;
    return *this;
}

Trit TritSet::Reference::operator~() const {
    Trit t = *this;
    if (t == TRUE) return FALSE;
    if (t == FALSE) return TRUE;
    return UNKNOWN;
}

Trit TritSet::Reference::operator&(Trit t1) const {
    Trit t2 = *this;
    if ((t1 == TRUE && (t2 == TRUE || t2 == UNKNOWN)) || (t2 == TRUE && t1 == UNKNOWN)) return TRUE;
    if (t1 == FALSE || t2 == FALSE) return FALSE;
    return UNKNOWN;
}

Trit TritSet::Reference::operator|(Trit t1) const {
    Trit t2 = *this;
    if (t1 == TRUE || t2 == TRUE) return TRUE;
    if (t1 == UNKNOWN || t2 == UNKNOWN) return UNKNOWN;
    return FALSE;
}

TritSet::Reference::operator Trit() const {
    // By the shift of the pointer, we determine the index
    // by which we are trying to address.
    if (set->get_capacity() <= (ptr - set->data) * uint_capacity + bit_shift / 2 + 1) return UNKNOWN;
    int bits = 0b11 & (*ptr >> uint_bit_size - bit_shift - 1);
    if (bits == TRUE_bits) return TRUE;
    if (bits == FALSE_bits) return FALSE;
    return UNKNOWN;
}

std::ostream& operator<<(std::ostream &o, const TritSet::Reference& t) {
    if (t == TRUE)    o << "T";
    if (t == FALSE)   o << "F";
    if (t == UNKNOWN) o << "U";
    return o;
}