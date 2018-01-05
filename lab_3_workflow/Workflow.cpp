#include "Workflow.h"

Workflow::Workflow() {
    text = SharedPtr<TextEditor>(new TextEditor);
    auto readfile = SharedPtr<Command>(new Read(text));
    auto writefile = SharedPtr<Command>(new Write(text));
    auto grep = SharedPtr<Command>(new Grep(text));
    auto sort = SharedPtr<Command>(new Sort(text));
    auto replace = SharedPtr<Command>(new Replace(text));
    auto dump = SharedPtr<Command>(new Dump(text));
    commands["readfile"] = readfile;
    commands["writefile"] = writefile;
    commands["grep"] = grep;
    commands["sort"] = sort;
    commands["replace"] = replace;
    commands["dump"] = dump;
}

void Workflow::parse_config(std::ifstream &input) {
    Parser parser(&input);
    while (!parser.end_of_desc()) {
        auto id = parser.get_next_essential_int_arg();

        auto command_name = parser.get_next_essential_arg();
        auto command = commands[command_name];
        if (command == nullptr) throw NoCommandException(command_name);

        blocks[id] = command_name;
        auto command_args = parser.get_command_args();
        command->read_args(command_args);
    }
    while (!parser.empty()) queue.push(parser.get_next_essential_int_arg());
}

void Workflow::work(std::string file_name) {
    try {
        std::ifstream input(file_name);
        if (!input.is_open()) throw NoFileException(file_name);
        parse_config(input);
        input.close();
        if (blocks[queue.front()] != "readfile" || blocks[queue.back()] != "writefile") throw WrongStructureException();

        while (!queue.empty()) {
            SharedPtr<Command> next_command = commands[blocks[queue.front()]];
            queue.pop();
            next_command->execute();
        }
    }
    catch(NoCommandException &e) {
        e.get_message();
    }
    catch(NoFileException &e) {
        e.get_message();
    }
    catch(WrongStructureException &e) {
        e.get_message();
    }
    catch(NoParameterException &e) {
        e.get_message();
    }
    catch(Exception &e) {
        e.get_message();
    }
}
