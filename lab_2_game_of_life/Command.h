#ifndef LAB_2_GAME_OF_LIFE_COMMAND_H
#define LAB_2_GAME_OF_LIFE_COMMAND_H

#include "Entity.h"

class Command {
protected:
    Entity *ent;
public:
    Command();
    explicit Command(Entity *);
    virtual void execute() = 0;
};

class Random : public Command {
public:
    explicit Random(Entity *);
    void execute() override;
};

class Auto : public Command {
public:
    explicit Auto(Entity *);
    void execute() override;
};

class Reset : public Command {
public:
    explicit Reset(Entity *);
    void execute() override;
};

class Set : public Command {
public:
    explicit Set(Entity *);
    void execute() override;
};

class Clear : public Command {
public:
    explicit Clear(Entity *);
    void execute() override;
};

class Step : public Command {
public:
    explicit Step(Entity *);
    void execute() override;
};

class Back : public Command {
public:
    explicit Back(Entity *);
    void execute() override;
};

class Load : public Command {
public:
    explicit Load(Entity *);
    void execute() override;
};

class Save : public Command {
public:
    explicit Save(Entity *);
    void execute() override;
};

class Help : public Command {
public:
    void execute() override;
};



#endif //LAB_2_GAME_OF_LIFE_COMMAND_H
