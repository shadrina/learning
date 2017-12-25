#ifndef LAB_3_WORKFLOW_COMMAND_H
#define LAB_3_WORKFLOW_COMMAND_H


#include "TextEditor.h"
#include <sstream>
#include <list>

class Command {
protected:
    std::list<std::string> args;
    TextEditor *text;
public:
    Command();
    explicit Command(TextEditor *);
    void read_args(std::string &s);
    virtual void execute() = 0;
};

class Read : public Command {
public:
    explicit Read(TextEditor *);
    void execute() override;
};

class Write : public Command {
public:
    explicit Write(TextEditor *);
    void execute() override;
};

class Grep : public Command {
public:
    explicit Grep(TextEditor *);
    void execute() override;
};

class Sort : public Command {
public:
    explicit Sort(TextEditor *);
    void execute() override;
};

class Replace : public Command {
public:
    explicit Replace(TextEditor *);
    void execute() override;
};

class Dump : public Command {
public:
    explicit Dump(TextEditor *);
    void execute() override;
};



#endif //LAB_3_WORKFLOW_COMMAND_H
