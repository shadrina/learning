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
	void shrink();           // Gets the memory free to the initial value or up to the value storing the last trit
	void trim(size_t);       // Forgets trits from last_index and on
	size_t cardinality(Trit);// Returns the number of trits set to this value
	std::unordered_map<Trit, int, std::hash<int>> cardinality();
	size_t length();         // Logical length
	unsigned int * get_set() const;
	unsigned int get_capacity() const;
	unsigned int get_uint_capacity() const;
};