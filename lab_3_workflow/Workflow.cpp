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
        // TODO if (parser.empty()) throw WrongStructureException();

        std::string command_name = parser.get_next_essential_arg();
        Command *command = commands[command_name];
        // TODO if (command == nullptr) throw NoCommandException();

        blocks[id] = command_name;
        std::string command_args = parser.get_command_args();
        command->read_args(command_args);
    }
    // TODO if (s != BLOCK_END) throw WrongStructureException();
    while (!parser.empty()) {
        unsigned int id = static_cast<unsigned int>(atoll(parser.get_next_essential_arg().c_str()));
        queue.push(id);
    }
}

void Workflow::work(std::string file_name) {
    try {
        std::ifstream input(file_name);
        // TODO if (!input.is_open) throw NoFileException();
        parse_config(input);
        input.close();
        // TODO if (blocks[queue.front()] != "read") throw WrongStructureException();
        while (!queue.empty()) {
            Command *next_command = commands[blocks[queue.front()]];
            queue.pop();
            next_command->execute();
        }
    }
    catch(Exception &e) {
        // ...
    }
}
