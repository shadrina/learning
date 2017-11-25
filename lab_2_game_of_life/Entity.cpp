#include "Entity.h"
#include <cstdlib>


Entity::Entity(unsigned int height_, unsigned int weight_) {
    this->curr_population = new Cell[weight_ * height_];
    this->prev_population = new Cell[weight_ * height_];
    this->weight = weight_;
    this->height = height_;
}

Entity::~Entity() {
    delete[] curr_population;
    delete[] prev_population;
    curr_population = nullptr;
    prev_population = nullptr;
}

void Entity::random_init_state() {
    int alive_cells_numb = rand() % (height + weight) + 1;
    for (int k = 0; k < alive_cells_numb; k++) {
        unsigned int i = rand() % weight;
        unsigned int j = rand() % height;
        curr_population[i * weight + j].set_state(ALIVE);
        notify_neighbors(i, j, ALIVE);
    }
}

void Entity::load_init_state(std::ifstream *fin) {
    // ...
}

/*
 * Rules:
 *
 * (1) Any live cell with fewer than two live neighbours dies.
 * (2) Any live cell with two or three live neighbours lives on to the next generation.
 * (3) Any live cell with more than three live neighbours dies.
 * (4) Any dead cell with exactly three live neighbours becomes a live cell.
 *
 */
void Entity::populate() {
    delete[] prev_population;
    prev_population = curr_population;

    for (unsigned int i = 0; i < weight; i++)
        for (unsigned int j = 0; j < height; j++) {
            State new_state;
            State curr_state = prev_population[i * weight + j].get_state();
            int alive_neighbours = prev_population[i * weight + j].get_alive_neighbours();
            if (curr_state == ALIVE && alive_neighbours < 2) new_state = DEAD;
            if (curr_state == ALIVE && alive_neighbours >= 2 && alive_neighbours <= 3) continue;
            if (curr_state == ALIVE && alive_neighbours > 3) new_state = DEAD;
            if (curr_state == DEAD && alive_neighbours == 3) new_state = ALIVE;

            curr_population[i * weight + j].set_state(new_state);
            notify_neighbors(i, j, new_state);
        }
}

void Entity::notify_neighbors(unsigned int i, unsigned int j, State set_state) {
    notify_neighbor((i - 1) % weight, j, set_state);
    notify_neighbor(i, (j - 1) % height, set_state);
    notify_neighbor((i + 1) % weight, j, set_state);
    notify_neighbor(i, (j + 1) % height, set_state);
    notify_neighbor((i - 1) % weight, (j - 1) % height, set_state);
    notify_neighbor((i + 1) % weight, (j - 1) % height, set_state);
    notify_neighbor((i + 1) % weight, (j + 1) % height, set_state);
    notify_neighbor((i - 1) % weight, (j + 1) % height, set_state);
}

void Entity::notify_neighbor(unsigned int i, unsigned int j, State set_state) {
    if (set_state == ALIVE) curr_population[i * weight + j].notice_neighbour_birth();
    if (set_state == DEAD) curr_population[i * weight + j].notice_neighbour_death();
}

