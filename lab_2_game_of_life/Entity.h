#ifndef LAB_2_GAME_OF_LIFE_ENTITY_H
#define LAB_2_GAME_OF_LIFE_ENTITY_H


/*! Description provided */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include "Cell.h"
#include "ConsoleColor.h"
#include "exceptions/Exception.h"

class Entity {
private:
    unsigned int width;
    unsigned int height;
    Cell * curr_population;
    Cell * prev_population;
    unsigned int step;
public:
    Entity(unsigned int, unsigned int);
    Entity();
    ~Entity();
    void compare_populations();
    void notify_neighbor(int, int, State);
    void notify_neighbors(unsigned int, unsigned int, State);
    void set(unsigned int, unsigned int);
    void clear(unsigned int, unsigned int);
    void random_init_state();
    Entity & load_init_state(std::ifstream *);
    void save_state(std::ofstream *);
    void populate();
    void print_state();
    void reset();
    void back();
};


#endif //LAB_2_GAME_OF_LIFE_ENTITY_H
