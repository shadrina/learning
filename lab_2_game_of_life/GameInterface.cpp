#include "GameInterface.h"

GameInterface::GameInterface() {
    this->playing_field = new Entity();
    auto *random = new Random(playing_field);
    auto *auto_play = new Auto(playing_field);
    auto *reset = new Reset(playing_field);
    auto *set = new Set(playing_field);
    auto *clear = new Clear(playing_field);
    auto *step = new Step(playing_field);
    auto *back = new Back(playing_field);
    auto *load = new Load(playing_field);
    auto *save = new Save(playing_field);
    auto *help = new Help();
    this->commands = {
            {"random", random},
            {"auto", auto_play},
            {"reset", reset},
            {"set", set},
            {"clear", clear},
            {"step", step},
            {"back", back},
            {"load", load},
            {"save", save},
            {"help", help}
    };
}

GameInterface::~GameInterface() {
    delete playing_field;
    playing_field = nullptr;
    for (auto command : commands) {
        delete command.second;
        command.second = nullptr;
    }
}

void GameInterface::play() {
    std::cout << "Enter the next command: ";
    std::string command_name;
    std::cin >> command_name;
    Command *command_executor = commands[command_name];
    try {
        if (command_executor == nullptr) throw NoCommandException(command_name);
        command_executor->execute();
    }
    catch(NoCommandException &e) {
        e.get_message();
    }
    catch(NoFileException &e) {
        e.get_message();
    }
    catch(FixedStateException &e) {
        e.get_message();
    }
    catch(Exception &e) {
        e.get_message();
    }

    play();
}