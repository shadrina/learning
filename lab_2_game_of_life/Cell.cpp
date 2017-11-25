#include "Cell.h"

void Cell::Cell() {
    this->state  = DEAD;
    this->alive_neighbours = 0;
}

void Cell::Cell(State state_) {
    this->state = state_;
}

void Cell::set_state(State state_) {
    this->state = state_;
}

State Cell::get_state() {
    return this->state;
}

int Cell::get_alive_neighbours() {
    return this->alive_neighbours;
}

void Cell::notice_neighbour_birth() {
    this->alive_neighbours++;
}

void Cell::notice_neighbour_death() {
    this->alive_neighbours--;
}