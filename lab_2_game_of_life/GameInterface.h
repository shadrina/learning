#ifndef LAB_2_GAME_OF_LIFE_GAMEINTERFACE_H
#define LAB_2_GAME_OF_LIFE_GAMEINTERFACE_H

/*! The program implements Conway's Game of Life - cellular automaton with a small set of rules. */

#include "Entity.h"
#include "Command.h"
#include <map>

class GameInterface {
private:
    Entity * playing_field;
    std::map<std::string, Command *> commands;
public:
    GameInterface();
    ~GameInterface();
    void play();
};


#endif //LAB_2_GAME_OF_LIFE_GAMEINTERFACE_H
