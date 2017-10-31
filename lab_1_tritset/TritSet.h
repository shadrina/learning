#ifndef LAB_1_TRITSET_H
#define LAB_1_TRITSET_H


/*!
	@file
	\brief Contains declarations of all properties, fields, and methods of the class TritSet and nested
	class Reference.

	The class implements storing a sequence of trits that grows as needed. Each element of the TritSet occupies 2 bits 
	and has three possible values: FALSE, UNKNOWN or TRUE.
	Individual indexed trits can be examined, set, or cleared. 
	One TritSet may be used to modify an another TritSet through logical AND and logical OR.
*/

#pragma once
#include <iostream>
#include <unordered_map>

enum Trit { FALSE, UNKNOWN, TRUE };

const unsigned int uint_capacity = sizeof(unsigned int) * 8 / 2;
const unsigned int uint_bit_size = sizeof(unsigned int) * 8;

// Bit representation of trits
const unsigned int TRUE_bits = 0b10;
const unsigned int FALSE_bits = 0b01;

const double GOLDEN_RATIO = 1.61803;

class TritSet {
private:
	unsigned int init_capacity;       // In uints
	unsigned int capacity;            // In uints
	unsigned int *data;
	unsigned int ptr_last;            // Last bit in the last byte
	unsigned int last_modified_trit;  // In trits
public:
	class Reference {
	private:
		TritSet *set;
		unsigned int byte_shift;
		unsigned int bit_shift;
	public:
		Reference(TritSet *, unsigned int, unsigned int);
		Reference& operator=(Trit);
		Reference& operator=(const Reference&);
		Trit operator~() const;
		Trit operator&(Trit) const;
		Trit operator|(Trit) const;
		operator Trit() const;
		friend std::ostream& operator<<(std::ostream &, const TritSet::Reference&);
	};
	TritSet();
	TritSet(const TritSet &);
	explicit TritSet(unsigned int capacity_);
	~TritSet();
	Reference operator[](unsigned int);
	TritSet & operator=(const TritSet &);
	TritSet operator~() const;
	TritSet operator&(TritSet &) const;
	TritSet operator|(TritSet &) const;
	bool operator==(TritSet &) const;
	bool operator!=(TritSet &) const;
	friend std::ostream& operator<<(std::ostream &, const TritSet &);
	void reallocate(unsigned int);
	void shrink();
	void trim(size_t);
	size_t cardinality(Trit);
	std::unordered_map<Trit, int, std::hash<int>> cardinality();
	size_t length();
	unsigned int * get_set() const;
	unsigned int get_capacity() const;
	unsigned int get_uint_capacity() const;
};


#endif