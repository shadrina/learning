#include "Command.h"

Command::Command() : ent(nullptr) {}

Command::Command(Entity *ent_) : ent(ent_) {}

Random::Random(Entity *ent_) : Command(ent_) {}

Auto::Auto(Entity *ent_) : Command(ent_) {}

Reset::Reset(Entity *ent_) : Command(ent_) {}

Set::Set(Entity *ent_) : Command(ent_) {}

Clear::Clear(Entity *ent_) : Command(ent_) {}

Step::Step(Entity *ent_) : Command(ent_) {}

Back::Back(Entity *ent_) : Command(ent_) {}

Load::Load(Entity *ent_) : Command(ent_) {}

Save::Save(Entity *ent_) : Command(ent_) {}

void Random::execute() {
    ent->random_init_state();

    system("cls");
    ent->print_state();
}

void Auto::execute() {
    int iterations, delay;
    std::cin >> iterations;
    std::cin >> delay;
    for (int i = 0; i < iterations; i++) {
        ent->populate();
        system("cls");
        ent->print_state();
        Sleep(delay);
    }
}

void Reset::execute() {
    ent->reset();

    system("cls");
    ent->print_state();
}

void Set::execute() {
    unsigned int i, j;
    std::cin >> i >> j;
    ent->set(i, j);

    system("cls");
    ent->print_state();
}

void Clear::execute() {
    unsigned int i, j;
    std::cin >> i >> j;
    ent->clear(i, j);

    system("cls");
    ent->print_state();
}

void Step::execute() {
    int N;
    std::cin >> N;
    for (int i = 0; i < N; i++) ent->populate();

    system("cls");
    ent->print_state();
}

void Back::execute() {
    ent->back();

    system("cls");
    ent->print_state();
}

void Load::execute() {
    std::string file_name;
    std::cin >> file_name;
    std::ifstream input(file_name);
    if (input.is_open()) ent->load_init_state(&input);
    else throw NoFileException(file_name);
    input.close();

    system("cls");
    ent->print_state();
}

void Save::execute() {
    std::string file_name;
    std::cin >> file_name;
    std::ofstream output(file_name);
    if (output.is_open()) ent->save_state(&output);
    else throw NoFileException(file_name);
    output.close();
    std::cout << "Saved! ";
}

void Help::execute() {
    system("cls");
    std::cout << "The following commands are supported: " << std::endl;
    std::cout << "* \'random\' sets random initial state" << std::endl;
    std::cout << "* \'auto [iterations] [delay]\' reproduces the process of birth of the next [iterations] generations"
            " with a delay of [delay] milliseconds" << std::endl;
    std::cout << "* \'reset\' clears the playing field and steps counter" << std::endl;
    std::cout << "* \'set [i] [j]\' revives the cell with coordinates ([i], [j])" << std::endl;
    std::cout << "* \'clear [i] [j]\' kills the cell with coordinates ([i], [j])" << std::endl;
    std::cout << "* \'step [n]\' skips [n] stages of division" << std::endl;
    std::cout << "* \'back\' returns previous state" << std::endl;
    std::cout << "* \'load [file_name]\' loads initial state from the file [file_name]" << std::endl;
    std::cout << "* \'save [file_name]\' stores current state in the file [file_name]" << std::endl;
    std::cout << "* \'help\' helps" << std::endl << std::endl;
}
