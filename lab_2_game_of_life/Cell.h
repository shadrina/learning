#ifndef LAB_2_GAME_OF_LIFE_CELL_H
#define LAB_2_GAME_OF_LIFE_CELL_H


enum State { ALIVE, DEAD };

class Cell {
private:
    State state;
    int alive_neighbours;
public:
    Cell();
    Cell(State);
    void set_state(State);
    State get_state() const;
    int get_alive_neighbours() const;
    void notice_neighbour_birth();
    void notice_neighbour_death();
    Cell & operator=(const Cell &);
};


#endif //LAB_2_GAME_OF_LIFE_CELL_H
