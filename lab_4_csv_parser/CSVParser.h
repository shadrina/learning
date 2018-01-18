#ifndef LAB_4_CSV_PARSER_CSVPARSER_H
#define LAB_4_CSV_PARSER_CSVPARSER_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include "Keywords.h"
#include "subtask_1_print_tuple/print_tuple.h"
#include "Exception.h"


template<typename ...TList>
class CSVParser {
private:
    std::tuple<TList...> *strings;
    size_t current_size;
    size_t filled_size;

    void reallocate();
    void parse_line(const std::string &);
    int convert_to_int(const std::string &);
    double convert_to_double(const std::string &);
    char convert_to_char(const std::string &);
    template <typename... T>
    friend std::ostream& operator<<(std::ostream &, const std::tuple<T...> &);
public:
    class Iterator {
    private:
        const std::tuple<TList...> *tuple_ptr;
    public:
        explicit Iterator(const std::tuple<TList...> *);
        const std::tuple<TList...> & operator*();
        Iterator & operator++();
        Iterator operator++(int);
        bool operator==(const Iterator &);
        bool operator!=(const Iterator &);
    };
    CSVParser();
    explicit CSVParser(std::ifstream *);
    ~CSVParser();
    Iterator begin();
    Iterator end();

};

template<typename T>
bool check_type(const std::string &s) {
    T n;
    return ((std::istringstream(s) >> n >> std::ws).eof());
}

template <size_t n, typename ElementT, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
set_element_by_index(std::tuple<T...> &, int, ElementT) {}

template <size_t n, typename ElementT, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
set_element_by_index(std::tuple<T...> &tup, int index, ElementT element) {
    if (n > sizeof...(T)) throw Exception();
    if (n == index) std::get<n>(tup) = element;
    set_element_by_index<n + 1, ElementT>(tup, index, element);
}

template<typename... TList>
void CSVParser<TList...>::reallocate() {
    size_t new_size = static_cast<size_t>(current_size * GOLDEN_RATIO);
    auto new_strings = new std::tuple<TList...>[new_size];
    for (int i = 0; i < current_size; i++) new_strings[i] = strings[i];
    delete strings;
    strings = new_strings;
    current_size = new_size;
}

template <typename... TList>
void CSVParser<TList...>::parse_line(const std::string &s) {
    std::tuple<TList...> tuple;
    std::istringstream iss(s);
    std::string sub;
    iss >> sub;
    int i = 0;
    while (iss) {
        if (check_type<int>(sub)) {
            auto element = convert_to_int(sub);
            set_element_by_index<0, int>(tuple, i, element);
        }
        if (check_type<double>(sub)) {
            auto element = convert_to_double(sub);
            set_element_by_index<0, double>(tuple, i, element);
        }
        if (check_type<char>(sub)) {
            auto element = convert_to_char(sub);
            set_element_by_index<0, char>(tuple, i, element);
        }
        if (check_type<std::string>(sub)) {
            // set_element_by_index<0, std::string>(tuple, i, sub);
        }
        iss >> sub;
        i++;
    }

    strings[filled_size] = tuple;
    if (filled_size == current_size - 1) reallocate();
    filled_size++;
}

template<typename... TList>
int CSVParser<TList...>::convert_to_int(const std::string &s) {
    return std::stoi(s);
}

template<typename... TList>
double CSVParser<TList...>::convert_to_double(const std::string &s) {
    return std::stod(s);
}

template<typename... TList>
char CSVParser<TList...>::convert_to_char(const std::string &s) {
    return s.c_str()[0];
}

template<typename... TList>
CSVParser<TList...>::CSVParser() {
    strings = new std::tuple<TList...>[INIT_SIZE];
    current_size = INIT_SIZE;
    filled_size = 0;
}

template<typename... TList>
CSVParser<TList...>::CSVParser(std::ifstream *file) : CSVParser() {
    std::string str;
    while (std::getline(*file, str, NEW_LINE)) parse_line(str);
}

template<typename... TList>
CSVParser<TList...>::~CSVParser() {
    delete strings;
}

template<typename... TList>
typename CSVParser<TList...>::Iterator CSVParser<TList...>::begin() {
    return Iterator(strings);
}

template<typename... TList>
typename CSVParser<TList...>::Iterator CSVParser<TList...>::end() {
    return Iterator(strings + filled_size);
}

template<typename... TList>
CSVParser<TList...>::Iterator::Iterator(const std::tuple<TList...> *tuple_) : tuple_ptr(tuple_) {}

template<typename... TList>
const std::tuple<TList...> & CSVParser<TList...>::Iterator::operator*() {
    return *tuple_ptr;
}

template<typename... TList>
typename CSVParser<TList...>::Iterator & CSVParser<TList...>::Iterator::operator++() {
    tuple_ptr++;
    return *this;
}

template<typename... TList>
typename CSVParser<TList...>::Iterator CSVParser<TList...>::Iterator::operator++(int) {
    Iterator temp(tuple_ptr);
    tuple_ptr++;
    return temp;
}

template<typename... TList>
bool CSVParser<TList...>::Iterator::operator==(const CSVParser::Iterator &i) {
    return this->tuple_ptr == i.tuple_ptr;
}

template<typename... TList>
bool CSVParser<TList...>::Iterator::operator!=(const CSVParser::Iterator &i) {
    return this->tuple_ptr != i.tuple_ptr;
}

#endif //LAB_4_CSV_PARSER_CSVPARSER_H
