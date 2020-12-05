#include "Game.h"
#include <iostream>
#include <fstream>

Game::Game() : map(Map()), hero(nullptr), hasMap(false), hasHero(false), hasMonsters(false), isRunning(false)
{

}

Game::Game(std::string mapfile) : map(Map(mapfile)), hero(nullptr), hasMap(true),
        hasHero(false), hasMonsters(false), isRunning(false)
{

}

void Game::setMap(Map map)
{
    if(isRunning)
    {
        throw GameAlreadyStartedException();
    }

    if(hasMonsters || hasHero)
    {
        throw AlreadyHasUnitsException();
    }

    this->map = map;

    hasMap = true;
}

void Game::putHero(Hero& hero, int x, int y)
{
    if(isRunning)
    {
        throw GameAlreadyStartedException();
    }

    if(!hasMap)
    {
        throw Map::WrongIndexException();
    }
    if(hasHero)
    {
        throw AlreadyHasHeroException();
    }

    try
    {
        if (map.get(y,x) == Map::Free)
        {
            this->hero = &hero;
            heroPos.x = x;
            heroPos.y = y;


            hasHero = true;
        }
        

    }
    catch(const Map::WrongIndexException&)
    {

    }
    
}
void Game::putMonster(Monster& monster, int x, int y)
{

    if(!hasMap)
    {
        throw Map::WrongIndexException();
    }


    try
    {
        if (map.get(y,x) != Map::Wall)
        {
            Position pos;
            pos.x = x;
            pos.y = y;

            monsters.insert(std::pair<Monster, Position>(monster, pos));
        }
        else
        {
            throw OccupiedException();
        }
        
        
    }
    catch(const Map::WrongIndexException&)
    {
        std::cout << "Wrong index!\n";
    }
    
}


void Game::print() const
{
    std::cout << "╔";

    for (int i = 0; i < map.getWidth(); ++i)
    {
        std::cout << "══";
    }
    std::cout << "╗\n";

    for(int i = 0; i < map.getHeight(); ++i)
    {
        std::cout << "║";
        for(int j = 0; j < map.getWidth(); ++j)
        {
            try
            {
                if(i == heroPos.x && j == heroPos.y)
                {
                    std::cout << "┣┫";
                }
                else if(map.get(j,i) == Map::Free)
                {
                    int monsterCount = 0;
                    for(auto& mons : monsters)
                    {
                        
                        if (mons.second.x == i && mons.second.y == j)
                        {
                            ++monsterCount;
                        }

                    }
                    if(monsterCount == 1)
                    {
                        std::cout << "M░";
                    }
                    else if (monsterCount > 1)
                    {
                        std::cout << "MM";
                    }
                    else
                    {
                        std::cout << "░░";
                    }
                }
                else if(map.get(j,i) == Map::Wall)
                {
                    std::cout << "██";
                }
            }
            catch(const Map::WrongIndexException&)
            {
                std::cout << "██";
            }
            
        }
        std::cout << "║" << std::endl;
    }

    std::cout << "╚";

    for (int i = 0; i < map.getWidth(); ++i)
    {
        std::cout << "══";
    }
    std::cout << "╝\n";
}



void Game::run()
{
    if(!hasMap || !hasHero)
    {
        NotInitializedException();
    }

    isRunning = true;

    //The gameloop
    while (hero->isAlive())
    {

        print();

        std::cout << "\nAction: \n";

        std::string userinput;
        std::cin >> userinput;

        if(userinput == "north")
        {
            try
            {
                if(map.get(heroPos.y, heroPos.x-1) == Map::Free)
                {
                    heroPos.x--;
                }
                else
                {
                    std::cout << "Can't go that way\n";
                }
                
            }
            catch(const Map::WrongIndexException&)
            {
                std::cout << "Can't go that way\n";
            }
            
        }
        else if (userinput == "south")
        {
            try
            {
                if(map.get(heroPos.y, heroPos.x + 1) == Map::Free)
                {
                    heroPos.x++;
                }
                else
                {
                    std::cout << "Can't go that way\n";
                }
                
            }
            catch(const Map::WrongIndexException&)
            {
                std::cout << "Can't go that way\n";
            }

        }
        else if (userinput == "east")
        {
            try
            {
                if(map.get(heroPos.y + 1, heroPos.x) == Map::Free)
                {
                    heroPos.y++;
                }
                else
                {
                    std::cout << "Can't go that way\n";
                }
                
            }
            catch(const Map::WrongIndexException&)
            {
                std::cout << "Can't go that way\n";
            }

        }
        else if (userinput == "west")
        {
            try
            {
                if(map.get(heroPos.y - 1, heroPos.x) == Map::Free)
                {
                    heroPos.y--;
                }
                else
                {
                    std::cout << "Can't go that way\n";
                }
                
            }
            catch(const Map::WrongIndexException&)
            {
                std::cout << "Can't go that way\n";
            }

        }
        else if (userinput == "breakout")
        {
            break;
        }


        //fight the monsters on that position
        for (auto& mons : monsters)
        {
            if(mons.second.x == heroPos.x && mons.second.y == heroPos.y)
            {
                hero->fightTilDeath(const_cast <Monster&>(mons.first));
            }
        }

        //deleting dead monsters
        for (auto it = monsters.begin(); it != monsters.end();)
        {
            if (!it->first.isAlive())
            {
                it = monsters.erase(it);
            }
            else
            {
                ++it;
            }
            
        }
        //decide if the map is cleared
        if (monsters.size() == 0)
        {
            print();
            std::cout << hero->getName() <<" Cleared the map\n";
            return;
        }
    }

    std::cout << "The hero died";
    hero = nullptr;
    hasHero = false;
}