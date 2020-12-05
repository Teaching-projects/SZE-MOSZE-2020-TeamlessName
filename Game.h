#pragma once
#include "Map.h"
#include "Hero.h"
#include "Monster.h"

#include <string>
#include <exception>
#include <map>

class Game
{
    struct Position
    {
        int x, y;

        Position(){}

        Position(int x, int y): x(x), y(y)
        {

        }

        Game::Position operator=(const Position& other)
        {
            x = other.x;
            y = other.y;
            return *this;
        }
    };

    Map map;
    Hero* hero;
    Position heroPos;
    std::map<Monster, Position> monsters;

    bool hasMap;
    bool hasHero;
    bool hasMonsters;
    bool isRunning;



public:
    void print() const;
    Game();
    Game(std::string mapfile);
    void setMap(Map map);
    void putHero(Hero& hero, int x, int y);
    void putMonster(Monster& monster, int x, int y);
    void run();

    class OccupiedException : public std::exception
    {
    public:
        OccupiedException(){}

    };

    class AlreadyHasHeroException : public std::exception
    {
    public:
        AlreadyHasHeroException(){}

    };

    class AlreadyHasUnitsException : public std::exception
    {
    public:
        AlreadyHasUnitsException(){}

    };

    class NotInitializedException : public std::exception
    {
    public:
        NotInitializedException(){}

    };

    class GameAlreadyStartedException : public std::exception
    {
    public:
        GameAlreadyStartedException(){}

    };

};