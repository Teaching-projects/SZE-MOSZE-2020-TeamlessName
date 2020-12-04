#include "MarkedMap.h"


MarkedMap::MarkedMap(std::string fname)
{
    std::ifstream stream(fname);
    if(stream.good()==false) throw std::runtime_error("The map file can't be load: " + fname);
    std::string cline;
    while(std::getline(stream, cline)){
        vmap.push_back(cline);
    }
    stream.close();
}

std::pair<int,int> MarkedMap::getHeroPosition() const
{
    std::pair<int,int> hero_c; //Hero coord
    for(int i = 0;i < (int) vmap.size();i++)
    {
        for(int k = 0; k < (int) vmap[i].length();k++)
        {
            if(vmap[i][k] == 'H')
                hero_c = std::make_pair(i,k);
        }
    }
    return hero_c;
}

std::vector<std::pair<int,int>> MarkedMap::getMonsterPositions(char c) const
{
    std::vector<std::pair<int,int>> monsters_coord;
    //std::pair<int,int> coordinates;
    for(int i = 0;i < (int) vmap.size();i++)
    {
        for(int k = 0; k < (int) vmap[i].length();k++)
        {
            if(vmap[i][k] == c)
                monsters_coord.push_back(std::make_pair(i,k));
        }
    }
    return monsters_coord;
}
