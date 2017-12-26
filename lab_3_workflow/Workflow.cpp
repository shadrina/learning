#include "Workflow.h"

Workflow::Workflow() {
    text = new TextEditor;
    auto *readfile = new Read(text);
    auto *writefile = new Write(text);
    auto *grep = new Grep(text);
    auto *sort = new Sort(text);
    auto *replace = new Replace(text);
    auto *dump = new Dump(text);
    commands = {
            {"readfile",    readfile},
            {"writefile",   writefile},
            {"grep",    grep},
            {"sort",    sort},
            {"replace", replace},
            {"dump",    dump}
    };
}

Workflow::~Workflow() {
    delete text;
    text = nullptr;
    for (auto command : commands) {
        delete command.second;
        command.second = nullptr;
    }
}

void Workflow::parse_config(std::ifstream &input) {
    Parser parser(&input);
    while (!parser.end_of_desc()) {
        std::string id_str = parser.get_next_essential_arg();
        auto id = static_cast<unsigned int>(atoll(id_str.c_str()));
        if (parser.empty()) throw WrongStructureException();

        std::string command_name = parser.get_next_essential_arg();
        Command *command = commands[command_name];
        if (command == nullptr) throw NoCommandException(command_name);

        blocks[id] = command_name;
        std::string command_args = parser.get_command_args();
        command->read_args(command_args);
    }
    while (!parser.empty()) {
        unsigned int id = static_cast<unsigned int>(atoll(parser.get_next_essential_arg().c_str()));
        queue.push(id);
    }
}

void Workflow::work(std::string file_name) {
    try {
        std::ifstream input(file_name);
        if (!input.is_open()) throw NoFileException(file_name);
        parse_config(input);
        input.close();
        if (blocks[queue.front()] != "readfile" || blocks[queue.back()] != "writefile") throw WrongStructureException();

        while (!queue.empty()) {
            Command *next_command = commands[blocks[queue.front()]];
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
