#include "Command.h"


Command::Command() = default;

Command::Command(TextEditor *text_editor) : text(text_editor) {}

void Command::read_args(std::string &s) {
    std::istringstream iss(s);
    std::string sub;
    iss >> sub;
    while (iss) {
        args.push_back(sub);
        iss >> sub;
    }
}

Read::Read(TextEditor *text_editor) : Command(text_editor) {}

void Read::execute() {
    text->read_file(args.front());
}

Write::Write(TextEditor *text_editor) : Command(text_editor) {}

void Write::execute() {
    text->write_file(args.front());
}

Grep::Grep(TextEditor *text_editor) : Command(text_editor) {}

void Grep::execute() {
    text->grep(args.front());
}

Sort::Sort(TextEditor *text_editor) : Command(text_editor) {}

void Sort::execute() {
    text->sort();
}

Replace::Replace(TextEditor *text_editor) : Command(text_editor) {}

void Replace::execute() {
    std::string arg1;
    arg1 = args.front();
    args.erase(args.begin());
    std::string arg2;
    arg2 = args.front();

    text->replace(arg1, arg2);
}

Dump::Dump(TextEditor *text_editor) : Command(text_editor) {}

void Dump::execute() {
    text->dump(args.front());
}
