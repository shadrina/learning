#include "Entity.h"

int main() {
    std::ifstream input("input.txt");

    Entity ent;
    ent.load_init_state(&input);
    ent.print_state();
    ent.populate();
    ent.print_state();

    input.close();
    return 0;
}