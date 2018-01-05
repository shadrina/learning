#ifndef LAB_3_WORKFLOW_PARSER_H
#define LAB_3_WORKFLOW_PARSER_H


#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Keys.h"
#include "exceptions/Exception.h"


class Parser {
private:
    std::queue<std::string> args;
    bool end_of_desc_detected;
    inline bool is_integer(const std::string &);
public:
    explicit Parser(std::ifstream *);
    std::string get_next_essential_arg();
    unsigned int get_next_essential_int_arg();
    std::string get_command_args();
    bool end_of_desc();
    bool empty();
};


#endif //LAB_3_WORKFLOW_PARSER_H
