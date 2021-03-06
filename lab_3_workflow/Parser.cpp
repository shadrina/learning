#include "Parser.h"

// stolen from stackoverflow.com :)
bool Parser::is_integer(const std::string &s) {
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
    char *p;
    strtol(s.c_str(), &p, 10);
    return (*p == 0);
}

Parser::Parser(std::ifstream *file) {
    std::string s;
    while (getline(*file, s)) {
        std::istringstream iss(s);
        std::string sub;
        iss >> sub;
        while (iss) {
            args.push(sub);
            iss >> sub;
        }
    }
    if (args.front() != BLOCK_START) throw WrongStructureException();
    args.pop();
    end_of_desc_detected = false;
}

std::string Parser::get_next_essential_arg() {
    std::string next;
    while (true) {
        if (args.empty() && !end_of_desc_detected) throw WrongStructureException();
        next = args.front();
        if (next == BLOCK_END) throw WrongStructureException();
        if (next == BLOCK_INITIALIZER || next == NODE_BOND) {
            args.pop();
            continue;
        }
        break;
    }
    args.pop();
    return next;
}

unsigned int Parser::get_next_essential_int_arg() {
    std::string arg = get_next_essential_arg();
    if (!is_integer(arg)) throw WrongStructureException();
    return static_cast<unsigned int>(std::stoi(arg));
}

std::string Parser::get_command_args() {
    std::string command_args;
    while (!args.empty() && !is_integer(args.front()) && args.front() != BLOCK_END) {
        command_args += args.front() + " ";
        args.pop();
    }
    if (args.front() == BLOCK_END) {
        end_of_desc_detected = true;
        args.pop();
    }
    return command_args;
}

bool Parser::empty() {
    return args.empty();
}

bool Parser::end_of_desc() {
    return end_of_desc_detected;
}

