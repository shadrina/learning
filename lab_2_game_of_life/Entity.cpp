#include "Entity.h"

Entity::Iterator::Iterator(const Cell *c_) : c(c_) {}

Entity::Iterator & Entity::Iterator::operator++() {
    c++;
    return *this;
}

Entity::Iterator Entity::Iterator::operator++(int) {
    Iterator temp(this->c);
    c++;
    return temp;
}

Entity::Iterator & Entity::Iterator::operator--() {
    c--;
    return *this;
}

Entity::Iterator Entity::Iterator::operator--(int) {
    Iterator temp(this->c);
    c--;
    return temp;
}

bool Entity::Iterator::operator==(const Iterator &i) {
    return c == i.c;
}

bool Entity::Iterator::operator!=(const Iterator &i) {
    return c != i.c;
}

std::ostream & operator<<(std::ostream &os, const Entity::Iterator &i) {
    os << *i.c;
    return os;
}

Entity::Entity(unsigned int height_, unsigned int width_) {
    this->height = height_;
    this->width = width_;
    this->curr_population = new Cell[height_ * width_];
    this->prev_population = new Cell[height_ * width_];
    this->step = 0;
}

Entity::Entity() : Entity(10, 10) {}

Entity::~Entity() {
    delete[] curr_population;
    delete[] prev_population;
    curr_population = nullptr;
    prev_population = nullptr;
}

void Entity::compare_populations() {
    for (int  i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (curr_population[i *  width + j] != prev_population[i * width + j]) return;
    throw FixedStateException();
}

void Entity::notify_neighbor(int i, int j, State set_state) {
    if (i == -1) i = height - 1;
    if (j == -1) j = width - 1;
    if (i == height) i = 0;
    if (j == width) j = 0;
    if (set_state == ALIVE) curr_population[i * width + j].notice_neighbour_birth();
    if (set_state == DEAD) curr_population[i * width + j].notice_neighbour_death();
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

void Entity::set(unsigned int i, unsigned int j) {
    curr_population[i * width + j].set_state(ALIVE);
    this->notify_neighbors(i, j, ALIVE);
};

void Entity::clear(unsigned int i, unsigned int j) {
    curr_population[i * width + j].set_state(DEAD);
    this->notify_neighbors(i, j, DEAD);
}

void Entity::random_init_state() {
    int alive_cells_numb = rand() % (height + width) + 1;
    for (int k = 0; k < alive_cells_numb; k++) {
        unsigned int i = rand() % height;
        unsigned int j = rand() % width;
        if (curr_population[i * width + j].get_state() == ALIVE) continue;
        set(i, j);
    }
}

Entity & Entity::load_init_state(std::ifstream *fin) {
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
            if (s[j] == '#') set(i, j);
        i++;
        if (!getline(*fin, s)) break;
    }
    return *this;
}

void Entity::save_state(std::ofstream *fout) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (curr_population[i * width + j].get_state() == ALIVE)
                *fout << "#";
            else *fout << ".";
        }
        *fout << std::endl;
    }
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
            // else if (curr_state == ALIVE && alive_neighbours >= 2 && alive_neighbours <= 3) continue;
            else if (curr_state == ALIVE && alive_neighbours > 3) new_state = DEAD;
            else if (curr_state == DEAD && alive_neighbours == 3) new_state = ALIVE;
            else continue;

            if (new_state == ALIVE) set(i, j);
            else clear(i, j);
        }
    step++;
    compare_populations();
}

void Entity::print_state() {
    std::cout << "  ";
    for (int i = 0; i < width; i++) printf("%2d", i);
    std::cout << std::endl;
    Iterator it = &curr_population[0];
    for (int i = 0; i < height; i++) {
        std::cout << i << " ";
        for (int j = 0; j < width; j++) {
            std::cout << it;
            it++;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "Step number: " << step << std::endl;
}

void Entity::reset() {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (curr_population[i * width + j].get_state() == ALIVE) {
                curr_population[i * width + j].set_state(DEAD);
                notify_neighbors(i, j, DEAD);
            }
    this->step = 0;
}

void Entity::back() {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            curr_population[i * width + j] = prev_population[i * width + j];
}