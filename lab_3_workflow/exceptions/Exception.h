#ifndef LAB_3_WORKFLOW_EXCEPTION_H
#define LAB_3_WORKFLOW_EXCEPTION_H


#include <iostream>
#include <utility>

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

class WrongStructureException : public Exception {
private:
    static const std::string requirements;
public:
    WrongStructureException();
    void get_message() override;
};

class NoParameterException : public Exception {
private:
    std::string function_name;
public:
    explicit NoParameterException(std::string);
    void get_message() override;
};


#endif //LAB_3_WORKFLOW_EXCEPTION_H
