#include "Exception.h"

const std::string WrongStructureException::requirements =
        "The configuration file should consist of 2 parts: \n"
                "description of the scheme blocks and description of the structure of the scheme. \n \n"
                "Reference format: \n"
                "desc # description of the scheme blocks \n"
                "id1 = block1 \n"
                "id2 = block2 \n"
                "... \n"
                "idN = blockN \n"
                "csed \n"
                "idA -> idB -> idC -> ... -> idZ # description of the structure of the scheme \n \n"
                "Where: \n"
                "desc, csed - keywords that limit the section of the description of workflow blocks \n"
                "id1 ... idN - integers, nonnegative, nonrepeating numbers \n"
                "block1 ... blockN - blocks from the list with required parameters \n"
                "idA, idB ... idZ - the numbers belonging to the set { id1, ..., idN }. Can be repeated, \n"
                "\t \t the length of the pipeline is unlimited. \n"
                "\"->\" - a keyword that denotes the connection of computing nodes. \n";

Exception::Exception() = default;

Exception::Exception(std::string msg_) : msg(std::move(msg_)) {}

NoCommandException::NoCommandException(std::string command_name_) : command_name(std::move(command_name_)) {
    msg = "The following command doesn't exist: ";
}

void NoCommandException::get_message() {
    std::cout << msg << command_name << std::endl;
}

NoFileException::NoFileException(std::string file_name_) : file_name(std::move(file_name_)) {
    msg = "The following file doesn't exist: ";
}

void NoFileException::get_message() {
    std::cout << msg << file_name << std::endl;
}

WrongStructureException::WrongStructureException() {
    msg = "The configuration file has an incorrect structure. Please make sure that it meets the requirements.";
}

void WrongStructureException::get_message() {
    std::cout << msg << std::endl << std::endl << requirements << std::endl;
}

NoParameterException::NoParameterException(std::string function_name_) : function_name(std::move(function_name_)) {
    msg = "The following function requires more params: ";
}

void NoParameterException::get_message() {
    std::cout << msg << function_name << std::endl;
}
