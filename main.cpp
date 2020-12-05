#include <iostream>
#include "JSON.h"
#include "Monster.h"
#include "Exceptions.h"
#include "Hero.h"


#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>

#include "JSON.h"
#include "Hero.h"
#include "Monster.h"
#include "Game.h"




const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided." },
    { 2 , "The provided scenario file is not accessible." },
    { 3 , "The provided scenario file is invalid." },
    { 4 , "JSON parsing error." }
};

void bad_exit(int exitcode){
    std::cerr 
        << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error")
        << std::endl;
    exit(exitcode);
}

int main(int argc, char** argv){
    Game game("map.txt");
    
    Hero hero{Hero::parse("Dark_Wanderer.json")};
    
    
    game.putHero(hero, 5, 2);
    Monster monster1{Monster::parse("Zombie.json")};
    Monster monster2{Monster::parse("Zombie.json")};
    Monster monster3{Monster::parse("Zombie.json")};
    game.putMonster(monster1, 3, 3);
    game.putMonster(monster2, 3, 3);
    game.putMonster(monster3, 3, 2);
    game.run();

    return 0;
}