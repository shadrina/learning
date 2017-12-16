#ifndef LAB_2_GAME_OF_LIFE_ENTITY_H
#define LAB_2_GAME_OF_LIFE_ENTITY_H


/*! Description provided */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Cell.h"
#include "ConsoleColor.h"

class Entity {
private:
    unsigned int width;
    unsigned int height;
    Cell * curr_population;
    Cell * prev_population;
public:
    Entity(unsigned int, unsigned int);
    Entity();
    ~Entity();
    void random_init_state();
    Entity & load_init_state(std::ifstream*);
    void populate();
    void notify_neighbors(unsigned int, unsigned int, State);
    void notify_neighbor(int, int, State);
    void print_state();
    void reset();
    void clear(unsigned int, unsigned int);
    void back();

};


#endif //LAB_2_GAME_OF_LIFE_ENTITY_H
