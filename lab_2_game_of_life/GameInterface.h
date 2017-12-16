#ifndef LAB_2_GAME_OF_LIFE_GAMEINTERFACE_H
#define LAB_2_GAME_OF_LIFE_GAMEINTERFACE_H

#include "Entity.h"

class GameInterface {
private:
    Entity playing_field;
public:
    GameInterface();
    ~GameInterface();
};


#endif //LAB_2_GAME_OF_LIFE_GAMEINTERFACE_H
