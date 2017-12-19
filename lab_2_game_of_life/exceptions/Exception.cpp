#include "Exception.h"

Exception::Exception() : msg("") {}

Exception::Exception(std::string s) : msg(std::move(s)) {}

NoCommandException::NoCommandException(std::string command_name_) : command_name(std::move(command_name_)) {
    msg = "The following command doesn't exist: ";
}

void NoCommandException::get_message() {
    std::cout << red << msg << white << command_name << std::endl;
}

NoFileException::NoFileException(std::string file_name_) : file_name(std::move(file_name_)) {
    msg = "The following file doesn't exist: ";
}

void NoFileException::get_message() {
    std::cout << red << msg << white << file_name << std::endl;
}

FixedStateException::FixedStateException() {
    msg = "State won't change. You can try to choose another initial state.";
}

void FixedStateException::get_message() {
    std::cout << red << msg << white << std::endl;
}

