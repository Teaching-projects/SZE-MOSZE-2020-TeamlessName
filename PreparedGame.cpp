#include "PreparedGame.h"
#include "Hero.h"
#include "Monster.h"
#include "JSON.h"

#include <iostream>
#include <string>

PreparedGame::PreparedGame(std::string& fname):json(JSON::parseFromFile(fname)), map((json.get<std::string>("map"))),
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
        std::string value = json.get<std::string>(key);

        //Monster newMonster(Monster::parse(value));
        auto MonsterPositions = map.getMonsterPositions(key[9]);

        for (auto& mpos : MonsterPositions)
        {
            monsters.insert(std::pair<Monster, Position>(Monster::parse(value), Position(mpos.first, mpos.second)));
        }
    }
}

void PreparedGame::run()
{

}