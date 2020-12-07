#pragma once

#include "Game.h"
#include "MarkedMap.h"
#include "JSON.h"

class PreparedGame : virtual protected Game
{
    JSON json;
    MarkedMap map;
    Hero hero;
    Position heroPos;
    std::map<Monster, Position> monsters;


    void initMonsters();
    void print();

public:
    PreparedGame(std::string);
    void run() override;

};