#ifndef LAB_2_GAME_OF_LIFE_EXCEPTION_H
#define LAB_2_GAME_OF_LIFE_EXCEPTION_H


#include <iostream>
#include <utility>
#include <string>
#include "../ConsoleColor.h"

class Exception {
protected:
    std::string msg;
public:
    Exception();
    explicit Exception(std::string);
    virtual void get_message() = 0;
};

class NoCommandException : public Exception {
private:
    std::string command_name;
public:
    explicit NoCommandException(std::string);
    void get_message() override;
};

class NoFileException : public Exception {
private:
    std::string file_name;
public:
    explicit NoFileException(std::string);
    void get_message() override;
};

class FixedStateException : public Exception {
public:
    FixedStateException();
    void get_message() override;
};


#endif //LAB_2_GAME_OF_LIFE_EXCEPTION_H
