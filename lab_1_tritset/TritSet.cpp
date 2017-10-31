#include "TritSet.h"

TritSet::TritSet() : init_capacity(0), capacity(0), data(nullptr), ptr_last(0), last_modified_trit(0) {}

// Copy constructor
TritSet::TritSet(TritSet const & set) {
	this->init_capacity = set.init_capacity;
	this->capacity = set.capacity;
	this->data = new unsigned int[this->capacity];
	for (int i = 0; i < this->capacity; i++)
		this->data[i] = set.data[i];
	this->ptr_last = set.ptr_last;
	this->last_modified_trit = set.last_modified_trit;
}

TritSet::TritSet(unsigned int capacity_) {
	this->init_capacity = capacity_ / uint_capacity;
	this->capacity = capacity_ / uint_capacity;
	auto tail_in_trits = capacity_ % uint_capacity;
	if (tail_in_trits > 0) {
		this->capacity++;
		this->init_capacity++;
	}
	this->data = new unsigned int[this->capacity];
	this->ptr_last = tail_in_trits == 0 ? uint_capacity * 2 - 1 : tail_in_trits * 2 - 1;
	this->last_modified_trit = 0;
}

TritSet::~TritSet() {
	delete[] data;
	data = nullptr;
}

TritSet::Reference TritSet::operator[](unsigned int x) {
	x++;
	auto index = x % uint_capacity;
	if (index == 0) index = uint_capacity;
	return Reference(this, x / uint_capacity, index * 2 - 1);
}

// Differences between copy constructor and operator=?
// (except deleting previous data)
TritSet & TritSet::operator=(const TritSet & set) {
	this->capacity = set.capacity;
	delete[] this->data;
	this->data = new unsigned int[set.capacity];
	for (int i = 0; i < this->capacity; i++)
		this->data[i] = set.data[i];
	this->ptr_last = set.ptr_last;
	this->last_modified_trit = set.last_modified_trit;
	return *this;
}

TritSet TritSet::operator~() const {
	// Method operator[] allows the object to be modified,
	// so we need to create copy
	TritSet set_copy = *this;
	TritSet set = *this;
	for (int i = 0; i < this->get_capacity(); i++)
		set[i] = ~set_copy[i];
	return set;
}

TritSet TritSet::operator&(TritSet &set_) const {
	// Method operator[] allows the object to be modified,
	// so we need to create copy
	TritSet set_copy = *this;
	auto capct1 = this->get_capacity();
	auto capct2 = set_.get_capacity();
	TritSet set(capct1 > capct2 ? capct1 : capct2);
	int i = 1;
	while (capct1 != i - 1 && capct2 != i - 1) {
		set[set.get_capacity() - i] = set_copy[capct1 - i] & set_[capct2 - i];
		i++;
	}
	i--; // now i is the capacity of the smaller operand
	int j = 0;
	// until we reach already filled part
	while (j < set.get_capacity() - i) {
		Reference r = capct1 > capct2 ? set_copy[j] : set_[j];
		set[j] = r & UNKNOWN;
		j++;
	}
	return set;
}

TritSet TritSet::operator|(TritSet &set_) const {
	// Method operator[] allows the object to be modified,
	// so we need to create copy
	TritSet set_copy = *this;
	auto capct1 = this->get_capacity();
	auto capct2 = set_.get_capacity();
	TritSet set(capct1 > capct2 ? capct1 : capct2);
	int i = 1;
	while (capct1 != i - 1 && capct2 != i - 1) {
		set[set.get_capacity() - i] = set_copy[capct1 - i] | set_[capct2 - i];
		i++;
	}
	i--; // now i is the capacity of the smaller operand
	int j = 0;
	// until we reach already filled part
	while (j < set.get_capacity() - i) {
		Reference r = capct1 > capct2 ? set_copy[j] : set_[j];
		set[j] = r | UNKNOWN;
		j++;
	}
	return set;
}

bool TritSet::operator==(TritSet &set_) const {
	// Method operator[] allows the object to be modified,
	// so we need to create copy
	TritSet set_copy = *this;
	if (this->get_capacity() != set_.get_capacity()) return false;
	for (int i = 0; i < this->get_capacity(); i++) 
		if (set_copy[i] != set_[i]) return false;
	return true;
}

bool TritSet::operator!=(TritSet &set_) const {
	return !(this->operator==(set_));
}

std::ostream& operator<<(std::ostream &o, const TritSet &set) {
	// Method operator[] allows the object to be modified,
	// so we need to create copy
	TritSet set_copy = set;
	auto capacity = set.get_capacity();
	for (int i = 0; i < capacity; i++)
		o << i << " ";
	o << std::endl;
	for (int i = 0; i < capacity; i++)
		o << set_copy[i] << " ";
	return o;
}

void TritSet::reallocate(unsigned int new_capacity) {
	this->capacity = new_capacity / uint_capacity;
	auto tail_in_trits = new_capacity % uint_capacity;
	if (tail_in_trits > 0) this->capacity++;
	this->ptr_last = tail_in_trits == 0 ? uint_capacity * 2 - 1 : tail_in_trits * 2 - 1;
	auto *new_data = new unsigned int[this->capacity];
	for (int i = 0; i < this->capacity; i++)
		new_data[i] = this->data[i];
	delete[] this->data;
	this->data = new_data;
}

void TritSet::shrink() {
	if (last_modified_trit != 0) reallocate(last_modified_trit);
	else reallocate(init_capacity);
}

void TritSet::trim(size_t last_index) {
	reallocate(last_index);
}

size_t TritSet::cardinality(Trit t) {
	size_t res = 0;
	for (int i = 1; i <= last_modified_trit; i++)
		if ((*this)[i] == t) res++;
	return res;
}

std::unordered_map<Trit, int, std::hash<int>> TritSet::cardinality() {
	std::unordered_map<Trit, int, std::hash<int>> m;
	m[FALSE] = cardinality(FALSE);
	m[UNKNOWN] = cardinality(UNKNOWN);
	m[TRUE] = cardinality(TRUE);
	return m;
}

size_t TritSet::length() {
	for (size_t i = last_modified_trit; i > 0; i--)
		if ((*this)[i] != UNKNOWN) return i - 1;
	return 0;
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