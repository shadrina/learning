#ifndef LAB_2_GAME_OF_LIFE_ENTITY_H
#define LAB_2_GAME_OF_LIFE_ENTITY_H


#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "Cell.h"
#include "exceptions/Exception.h"

class Entity {
private:
    unsigned int width;
    unsigned int height;
    Cell * curr_population;
    Cell * prev_population;
    unsigned int step;
public:
    class Iterator {
    private:
        const Cell *c;
    public:
        Iterator(const Cell *);
        const Cell & operator*();
        Iterator & operator++();
        Iterator operator++(int);
        Iterator & operator--();
        Iterator operator--(int);
        bool operator==(const Iterator &);
        bool operator!=(const Iterator &);
        friend std::ostream & operator<<(std::ostream &, const Iterator &);
    };
    Entity(unsigned int, unsigned int);
    Entity();
    ~Entity();
    Iterator begin();
    Iterator end();
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
