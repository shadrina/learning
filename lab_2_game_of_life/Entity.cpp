#include "Entity.h"

Entity::Entity(unsigned int height_, unsigned int width_) {
    this->height = height_;
    this->width = width_;
    this->curr_population = new Cell[height_ * width_];
    this->prev_population = new Cell[height_ * width_];
}

Entity::Entity() : Entity(10, 10) {}

Entity::~Entity() {
    delete[] curr_population;
    delete[] prev_population;
    curr_population = nullptr;
    prev_population = nullptr;
}

void Entity::random_init_state() {
    int alive_cells_numb = rand() % (height + width) + 1;
    if (alive_cells_numb < (height + width) / 4) alive_cells_numb += 10;
    for (int k = 0; k < alive_cells_numb; k++) {
        unsigned int i = rand() % height;
        unsigned int j = rand() % width;
        if (curr_population[i * width + j].get_state() == ALIVE) continue;
        curr_population[i * width + j].set_state(ALIVE);
        notify_neighbors(i, j, ALIVE);
    }
}

Entity & Entity::load_init_state(std::ifstream *fin) {
    if (!fin->is_open()) std::cout << "I will create an exception..." << std::endl;
    delete[] curr_population;
    delete[] prev_population;
    std::string s;
    getline(*fin, s);
    unsigned int size = s.length();
    this->width = size;
    this->height = size;
    this->curr_population = new Cell[size * size];
    this->prev_population = new Cell[size * size];
    int i = 0;
    while(true) {
        for (int j = 0; j < size; j++)
            if (s[j] == '#') {
                curr_population[i * size + j].set_state(ALIVE);
                notify_neighbors(i, j, ALIVE);
            }
        i++;
        if (!getline(*fin, s)) break;
    }
    return *this;
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
    // Current population becomes previous
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            prev_population[i * width + j] = curr_population[i * width + j];

    for (unsigned int i = 0; i < height; i++)
        for (unsigned int j = 0; j < width; j++) {
            State new_state;
            State curr_state = prev_population[i * width + j].get_state();
            int alive_neighbours = prev_population[i * width + j].get_alive_neighbours();
            if (curr_state == ALIVE && alive_neighbours < 2) new_state = DEAD;
            else if (curr_state == ALIVE && alive_neighbours >= 2 && alive_neighbours <= 3) continue;
            else if (curr_state == ALIVE && alive_neighbours > 3) new_state = DEAD;
            else if (curr_state == DEAD && alive_neighbours == 3) new_state = ALIVE;
            else continue;

            curr_population[i * width + j].set_state(new_state);
            notify_neighbors(i, j, new_state);
        }
}

void Entity::notify_neighbors(unsigned int i, unsigned int j, State set_state) {
    notify_neighbor(i - 1, j, set_state);
    notify_neighbor(i, j - 1, set_state);
    notify_neighbor(i + 1, j, set_state);
    notify_neighbor(i, j + 1, set_state);
    notify_neighbor(i - 1, j - 1, set_state);
    notify_neighbor(i + 1, j - 1, set_state);
    notify_neighbor(i + 1, j + 1, set_state);
    notify_neighbor(i - 1, j + 1, set_state);
}

void Entity::notify_neighbor(int i, int j, State set_state) {
    if (i == -1) i = height - 1;
    if (j == -1) j = width - 1;
    if (i == height) i = 0;
    if (j == width) j = 0;
    if (set_state == ALIVE) curr_population[i * width + j].notice_neighbour_birth();
    if (set_state == DEAD) curr_population[i * width + j].notice_neighbour_death();
}

void Entity::print_state() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (curr_population[i * width + j].get_state() == ALIVE) std::cout << green << "#";
            if (curr_population[i * width + j].get_state() == DEAD) std::cout << white << "O";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

