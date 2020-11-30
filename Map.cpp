#include "Map.h"
#include <string>
#include <fstream>

Map::Map(std::string fname) {
    std::ifstream stream(fname);
    if(!stream.good()) throw std::runtime_error("The map file can't be load: " + fname);
    std::string cRow;
    while(std::getline(stream, cRow)){
        vmap.push_back(cRow);
    }
    stream.close();
}

Map::type Map::get(unsigned int x, unsigned int y) const {
    if(x >= vmap[y].length() || x < 0)
        throw Map::WrongIndexException("coord X is out of range");
    if(y >= vmap.size() || y < 0)
        throw Map::WrongIndexException("coord X is out of range");
    if(vmap[y][x] == '#')
        {
            return Map::type::Wall;
        }
    else
        {
            return Map::type::Free;
        }
}
