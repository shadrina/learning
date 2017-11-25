#ifndef LAB_2_GAME_OF_LIFE_ENTITY_H
#define LAB_2_GAME_OF_LIFE_ENTITY_H


/*! Description provided */

#include "Cell.h"
#include <fstream>

class Entity {
private:
    unsigned int weight;
    unsigned int height;
    Cell * curr_population;
    Cell * prev_population;
public:
    Entity(unsigned int, unsigned int);
    ~Entity();
    void random_init_state();
    void load_init_state(std::ifstream*);
    void populate();
    void notify_neighbors(unsigned int, unsigned int, State);
    void notify_neighbor(unsigned int, unsigned int, State);
    void reset();
    void clear(unsigned int, unsigned int);
    void back();

};


#endif //LAB_2_GAME_OF_LIFE_ENTITY_H
