#ifndef LAB_3_WORKFLOW_COMMAND_H
#define LAB_3_WORKFLOW_COMMAND_H


#include <sstream>
#include <list>
#include "TextEditor.h"
#include "SharedPtr.h"

class Command {
protected:
    std::list<std::string> args;
    SharedPtr<TextEditor> text;
public:
    Command();
    explicit Command(SharedPtr<TextEditor>);
    void read_args(std::string &);
    virtual void execute() = 0;
};

class Read : public Command {
public:
    explicit Read(SharedPtr<TextEditor>);
    void execute() override;
};

class Write : public Command {
public:
    explicit Write(SharedPtr<TextEditor>);
    void execute() override;
};

class Grep : public Command {
public:
    explicit Grep(SharedPtr<TextEditor>);
    void execute() override;
};

class Sort : public Command {
public:
    explicit Sort(SharedPtr<TextEditor>);
    void execute() override;
};

class Replace : public Command {
public:
    explicit Replace(SharedPtr<TextEditor>);
    void execute() override;
};

class Dump : public Command {
public:
    explicit Dump(SharedPtr<TextEditor>);
    void execute() override;
};



#endif //LAB_3_WORKFLOW_COMMAND_H
