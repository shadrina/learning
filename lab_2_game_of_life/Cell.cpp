#include "Cell.h"

Cell::Cell() {
    this->state  = DEAD;
    this->alive_neighbours = 0;
}

Cell::Cell(State state_) {
    this->state = state_;
}

void Cell::set_state(State state_) {
    this->state = state_;
}

State Cell::get_state() const {
    return this->state;
}

int Cell::get_alive_neighbours() const {
    return this->alive_neighbours;
}

void Cell::notice_neighbour_birth() {
    this->alive_neighbours++;
}

void Cell::notice_neighbour_death() {
    this->alive_neighbours--;
}
Cell & Cell::operator=(const Cell &c) {
    this->state = c.get_state();
    this->alive_neighbours = c.get_alive_neighbours();
    return *this;
}

bool Cell::operator==(const Cell &c) {
    return state == c.get_state() && alive_neighbours == c.get_alive_neighbours();
}

bool Cell::operator!=(const Cell &c) {
    return !this->operator==(c);
}

std::ostream & operator<<(std::ostream &os, const Cell &c) {
    if (c.get_state() == ALIVE) {
        os << green;
        printf("%2c", '#');
        os << white;
    }
    if (c.get_state() == DEAD) {
        os << white << "  ";
    }
    return os;
}