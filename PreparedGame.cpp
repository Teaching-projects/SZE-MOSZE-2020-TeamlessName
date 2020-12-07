#include "PreparedGame.h"
#include "Hero.h"
#include "Monster.h"
#include "JSON.h"

#include <iostream>
#include <string>

PreparedGame::PreparedGame(std::string fname):json(JSON::parseFromFile(fname)), map((json.get<std::string>("map"))),
        hero(Hero::parse(json.get<std::string>("hero"))), 
        heroPos(map.getHeroPosition().first, map.getHeroPosition().second)
{
    initMonsters();
    print();
}

void PreparedGame::initMonsters()
{
    for(int i = 1; i < 10; ++i)
    {
        std::string key = "monster-" + std::to_string(i);
        try
        {
            std::string value = json.get<std::string>(key);
            auto MonsterPositions = map.getMonsterPositions(key[8]);
            for (auto& mpos : MonsterPositions)
            {
                monsters.insert(std::pair<Monster, Position>(Monster::parse(value), Position(mpos.first, mpos.second)));
            }
        }
        catch(std::out_of_range&)
        {
            break;
        }
    }

    
}

void PreparedGame::run()
{
    while (hero.isAlive())
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
        else
        {
            std::cout << "I don't know what to do\n";
        }
        


        //fight the monsters on that position
        for (auto& mons : monsters)
        {
            if(mons.second.x == heroPos.x && mons.second.y == heroPos.y)
            {
                hero.fightTilDeath(const_cast <Monster&>(mons.first));
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
            std::cout << hero.getName() <<" Cleared the map\n";
            return;
        }
    }

    std::cout << "The hero died";
}


void PreparedGame::print()
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