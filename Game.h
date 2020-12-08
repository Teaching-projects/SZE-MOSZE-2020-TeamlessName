#pragma once
#include "Map.h"
#include "Hero.h"
#include "Monster.h"

#include <string>
#include <exception>
#include <map>
/**
 * \class Game
 * 
 * \brief A class that controls the game
 * 
 */
class Game
{
    Map map; ///< Storing the level

protected:
    /**
    * \struct Position
    * 
    * \brief A struct that represents a place in the map
    * 
    */
    struct Position
    {
        unsigned int x, y;

        Position() ///< Default constructor of Position
        {}

        Position(unsigned int x, unsigned int y): x(x), y(y)
        {

        }

        /**
         * \brief copy-assignment operator
         * 
         * \param other const Position& to be equal with
         */
        Position& operator=(const Position& other)
        {
            x = other.x;
            y = other.y;
            return *this;
        }
    };

private:
    Hero* hero; ///< Pointer to the only hero
    Position heroPos; ///< Position of the hero
    std::map<Monster, Position> monsters; ///< Instances and postions of Monsters on the level

    bool hasMap;
    bool hasHero;
    bool hasMonsters;
    bool isRunning;



public:
    void print() const; ///< Prints the current state of the game
    Game(); ///< Default empty constructor of Game
    explicit Game(const std::string& mapfile); ///< Constructor of Game with the Map initialized
    void setMap(const Map& map); ///< Set the map
    void putHero(Hero& hero, int x, int y);
    void putMonster(Monster& monster, int x, int y);
    virtual void run(); ///< Handles the game loop

    /**
     * \class OccupiedException
    */
    class OccupiedException : public std::exception
    {
    public:
        OccupiedException(){}

    };
    /**
     * \class AlreadyHasHeroException
    */
    class AlreadyHasHeroException : public std::exception
    {
    public:
        AlreadyHasHeroException(){}

    };
    /**
     * \class AlreadyHasUnitsException
    */
    class AlreadyHasUnitsException : public std::exception
    {
    public:
        AlreadyHasUnitsException(){}

    };
    /**
     * \class NotInitializedException
    */
    class NotInitializedException : public std::exception
    {
    public:
        NotInitializedException(){}

    };
    /**
     * \class GameAlreadyStartedException
    */
    class GameAlreadyStartedException : public std::exception
    {
    public:
        GameAlreadyStartedException(){}

    };

};