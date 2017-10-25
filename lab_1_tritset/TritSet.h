enum Trit {FALSE, UNKNOWN, TRUE};

const unsigned int uint_capacity = sizeof(unsigned int) * 8 / 2;
const unsigned int uint_bit_size = sizeof(unsigned int) * 8;

class TritSet {
private:
    unsigned int capacity; // в uint'ах
    unsigned int *data;
    unsigned int ptr_last;
    class Reference {
    private:
        TritSet *set;
        unsigned int *ptr;
        unsigned int bit_shift;
        Reference();
    public:
        Reference(TritSet *, unsigned int, unsigned int);
        ~Reference();
        Reference& operator=(Trit);
        Reference& operator=(const Reference&);
        Trit operator~() const;
        operator Trit() const;
    };
public:
    TritSet();
    explicit TritSet(unsigned int capacity_);
    ~TritSet();
    Reference operator[](unsigned int);
    unsigned int * get_set() const;
    unsigned int get_capacity() const;
    unsigned int get_byte_capacity() const;
};