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

void PreparedGame::print() const
{
    std::vector<std::vector<std::string>> level;
    std::vector<std::string> mapElement;

    for(unsigned int i = 0; i < map.getHeight(); ++i)
    {
        std::string line = "";
        for(unsigned int j = 0; j < map.getWidth(); ++j)
        {
            try
            {
                if(i == heroPos.x && j == heroPos.y)
                {
                    line = "┣┫";
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
                        line = "M░";
                    }
                    else
                    {
                        line = "░░";
                    }
                }
                else if(map.get(j,i) == Map::Wall)
                {
                    line = "██";
                }
            }
            catch(const Map::WrongIndexException&)
            {
                line = "██";
            }
            mapElement.push_back(line);
            
        }
        level.push_back(mapElement);
        mapElement.clear();
    }

    unsigned int printlength;

    if(heroPos.y <= hero.getLightRadius())
    {
        printlength = heroPos.y;

        if(heroPos.y + hero.getLightRadius() >= level[0].size())
        {
            printlength += level[0].size() - heroPos.y; 
        }
        else
        {
            printlength += hero.getLightRadius() + 1;
        }
        
    }
    else
    {
        printlength = hero.getLightRadius();

        if(heroPos.y + hero.getLightRadius() >= level[0].size())
        {
            printlength += level[0].size() - heroPos.y; 
        }
        else
        {
            printlength += hero.getLightRadius() + 1;
        }
    }

    std::cout << "╔";
    for(unsigned int i = 0; i < printlength; ++i)
    {
        std::cout << "══";
    }
    std::cout << "╗\n";

    for(unsigned int i = 0; i < level.size(); ++i)
    {
        bool printed_first_character = false;
        for(unsigned int j = 0; j < level[i].size(); ++j)
        {
            if(heroPos.x <= hero.getLightRadius() && i <= heroPos.x)
            {
                if(heroPos.y <= hero.getLightRadius() && j <= heroPos.y)
                {
                    if(!printed_first_character)
                    {
                        printed_first_character = true;
                        std::cout << "║";
                    }
                    std::cout << level[i][j];
                }
                else if((j >= heroPos.y && heroPos.y + hero.getLightRadius() >= j) || (j <= heroPos.y && heroPos.y - hero.getLightRadius() <= j))
                {
                    if(!printed_first_character)
                    {
                        printed_first_character = true;
                        std::cout << "║";
                    }
                    std::cout << level[i][j];
                }
            }
            else if((i >= heroPos.x && heroPos.x + hero.getLightRadius() >= i) ||( i<= heroPos.x && heroPos.x - hero.getLightRadius() <= i))
            {
                if(heroPos.y <= hero.getLightRadius() && j <= heroPos.y)
                {
                    if(!printed_first_character)
                    {
                        printed_first_character = true;
                        std::cout << "║";
                    }
                    std::cout << level[i][j];
                }
                else if((j >= heroPos.y && heroPos.y + hero.getLightRadius() >= j) || (j <= heroPos.y && heroPos.y - hero.getLightRadius() <= j))
                {
                    if(!printed_first_character)
                    {
                        printed_first_character = true;
                        std::cout << "║";
                    }
                    std::cout << level[i][j];
                }
            }
        }
        if(printed_first_character)
        std::cout << "║\n";
    }


    std::cout << "╚";
    for(unsigned int i = 0; i < printlength; ++i)
    {
        std::cout << "══";
    }
    std::cout << "╝\n";
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
