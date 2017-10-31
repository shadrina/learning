#ifndef LAB_2_GAME_OF_LIFE_ENTITY_H
#define LAB_2_GAME_OF_LIFE_ENTITY_H

/*! Description provided */

enum State { ALIVE, DEAD };

struct Cell {
    State state;
    int alive_neighbours;
};

class Entity {
private:
    Cell playing_field[10][10];

public:
    void reset();
    void step(int);
    void clear(int, int);
    void back();

};


#endif //LAB_2_GAME_OF_LIFE_ENTITY_H
