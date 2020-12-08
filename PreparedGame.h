#pragma once

#include "Game.h"
#include "MarkedMap.h"
#include "JSON.h"

class PreparedGame : virtual protected Game
{
    JSON json; ///< A JSON object to store the values form the given file in the constructor
    MarkedMap map; ///< Representation of the level
    Hero hero; ///< The only hero on the level
    Position heroPos; ///< The position of the hero
    std::map<Monster, Position> monsters; ///< Map of monsters and their positions on the level


    void initMonsters(); ///< Places the monsters on the level, based on the MarkedMap
    void print() const; ///< Print out the current state of the game

public:
    /**
     * \brief Constructor of PreparedGame
     * \param Mapfile name of a marked map file
    */
    explicit PreparedGame(std::string Mapfile);
    void run() override; ///< Handles the game loop

};