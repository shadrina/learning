enum Trit {FALSE, UNKNOWN, TRUE};

const unsigned int uint_capacity = sizeof(unsigned int) * 8 / 2;
const unsigned int uint_bit_size = sizeof(unsigned int) * 8;

//Bit representation of trits
const unsigned int TRUE_bits = 0b10;
const unsigned int FALSE_bits = 0b01;

class TritSet {
private:
    unsigned int capacity; //in uints
    unsigned int *data;
    unsigned int ptr_last;
public:
    class Reference {
    private:
        TritSet const *set;
        unsigned int *ptr;
        unsigned int bit_shift;
    public:
        Reference();
        Reference(TritSet const *, unsigned int, unsigned int);
        ~Reference();
        Reference& operator=(Trit);
        Reference& operator=(const Reference&);
        Trit operator~() const;
        Trit operator&(Trit) const;
        Trit operator|(Trit) const;
        operator Trit() const;
        friend std::ostream& operator<<(std::ostream &o, const TritSet::Reference& t);
    };
    TritSet();
    TritSet(const TritSet &);
    explicit TritSet(unsigned int capacity_);
    ~TritSet();
    Reference operator[](unsigned int) const;
    TritSet & operator=(const TritSet &);
    TritSet operator~() const;
    TritSet operator&(TritSet) const;
    TritSet operator|(TritSet) const;
    friend std::ostream& operator<<(std::ostream &o, const TritSet &set);
    void reallocate(unsigned int);
    unsigned int * get_set() const;
    unsigned int get_capacity() const;
    unsigned int get_uint_capacity() const;
};